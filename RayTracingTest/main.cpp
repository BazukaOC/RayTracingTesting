#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "algebra3.h"
#include "imageIO.h"
#include "objloader.h"

#define PI 3.1415926535898
#define Tan(th) tan(PI/180*(th))

using namespace std;

vec3 eye, dir, vert, hori;
float Fangle;
int Rw, Rh;

float SOx, SOy, SOz, Sr;
float Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz;

vector<vec4> Sphere;
vector<vec3> Triangle;
OBJLOADER model;

bool readFile(string name) {

    ifstream ifile(name.c_str()), iifile(name.c_str());
        if(!ifile || !iifile) { return false; }

    string test;

    GROUP tempgroup;
    bool  isNextGroup = false;

    while(ifile >> test) {
        if(test == "v") {
            if(isNextGroup) {
                isNextGroup = false;
                model.groups_.push_back(tempgroup);
                model.numGroups_++;
                tempgroup.clear();
            }
            float x, y, z;
            ifile >> x >> y >> z;
            tempgroup.vertices_.push_back(vec3(x, y, z));
            tempgroup.numVertices_++;
        }
        else if (test == "f") {
            isNextGroup = true;
            int a, b, c, d;
            ifile >> a >> b >> c >> d;
            tempgroup.faces_.push_back(a);
            tempgroup.faces_.push_back(b);
            tempgroup.faces_.push_back(c);
            tempgroup.faces_.push_back(d);
        }
    }
    model.groups_.push_back(tempgroup);
    model.numGroups_++;

    for(int i = 0; i < model.numGroups_; i += 1) {
        for(int j = 0; j < model.groups_[i].numVertices_; j += 1) {
            for(int k = 0; k < 3; k += 1) {
                cout << model.groups_[i].vertices_[j][k] << " ";
            }
            cout << endl;
        }
        for(int k = 0; k < 4; k += 1) {
            cout << model.groups_[i].faces_[k] << " ";
        }
        cout << endl << endl;
    }

    ifile.close();
    iifile.close();

    return true;
}

void setRay() {
    vert = vec3(0, 1, 0);
    hori = vert ^ dir;

    dir  =  dir.normalize();
    vert = vert.normalize();
    hori = hori.normalize();

    hori = hori * ( dir.length() * Tan(Fangle/2) / (Rw/2) );
    vert = vert * ( dir.length() * Tan(Fangle/2) / (Rh/2) );
    dir  =  dir - Rw/2 * hori + Rh/2 * vert;
    ///cout << dir[0] << ", " << dir[1] << ", " << dir[2] << endl;
}

bool isIntersectedSph(vec3 &ray, vec4 &sph) {

    ///  AT^2 + BT + C = 0
    float A = ray[0]*ray[0]+ray[1]*ray[1]+ray[2]*ray[2];
    float B = 2*(ray[0]*(eye[0]-sph[0])+ray[1]*(eye[1]-sph[1])+ray[2]*(eye[2]-sph[2]));
    float C = (eye[0]-sph[0])*(eye[0]-sph[0])+(eye[1]-sph[1])*(eye[1]-sph[1])+(eye[2]-sph[2])*(eye[2]-sph[2])-sph[3]*sph[3];

    if ( ( B*B - 4*A*C ) >= 0 ) { return true; }

    return false;
}

bool isIntersectedTri(vec3 &ray, vec3 &a, vec3 &b, vec3 &c) {

    vec3 S1 = b - a;
    vec3 S2 = c - a;
    vec3  n = S1 ^ S2;

    /// there is no triangle
    if( n == vec3(0, 0, 0) ) { return false; }

    /// ray is not in the triangle plane
    if( ray * n == 0 ) { return false; }

    /// ray is away from the triangle, ax + by + cz = d
    float d = n[0]*a[0] + n[1]*a[1] + n[2]*a[2];
    float t = ( d - ( n[0]*eye[0] + n[1]*eye[1] + n[2]*eye[2] ) ) / ( n[0]*ray[0] + n[1]*ray[1] + n[2]*ray[2] );
    if ( t < 0.0 ) { return false; }

    /// inside test
    float inaccuracy = 0.0001;
    vec3 point(eye[0] + t*ray[0], eye[1] + t*ray[1], eye[2] + t*ray[2]);

    vec3 S3 = point - a;
    vec3 S4 = b - point;
    vec3 S5 = c - point;

    vec3 v31 = S1 ^ S3; float tri31 = v31.length() / 2;
    vec3 v32 = S2 ^ S3; float tri32 = v32.length() / 2;
    vec3 v12 = S1 ^ S2; float tri12 = v12.length() / 2;
    vec3 v45 = S4 ^ S5; float tri45 = v45.length() / 2;

    if ( (tri31 + tri32) > tri12 ) { return false; }
    if ( (tri31 + tri32 + tri45) > tri12 + inaccuracy ) { return false; }

    return true;
}

int main()
{
    string Filename("CornellBox-Original.obj");

    if(!readFile(Filename)) {
        cout << "Fail to open OBJ File." << endl;
        return 0;
    }

    setRay();

    ColorImage image;
    image.init(Rw, Rh);
    //Pixel W = {255,255,255};


//    for (int i = 0; i < Rw; ++i) {
//        for (int j = 0; j < Rh; ++j) {
//            /// generate the ray.
//            vec3 ray = dir + i*hori - j*vert;
//            ray = ray.normalize();
//            /// test if it intersected with all triangles.
//            for (unsigned int t = 0; t < Triangle.size(); t+=3) {
//                if( isIntersectedTri(ray, Triangle[t], Triangle[t+1], Triangle[t+2]) ) {
//                    image.writePixel(i, j, W);
//                }
//            }
//            /// test if it intersected with all spheres.
//            for (unsigned int s = 0; s < Sphere.size(); ++s) {
//                if( isIntersectedSph(ray, Sphere[s]) ) {
//                    image.writePixel(i, j, W);
//                }
//            }
//        }
//    }
//    char outputname[15] = "hw1_output.ppm";
//    image.outputPPM(outputname);
    return 0;
}
