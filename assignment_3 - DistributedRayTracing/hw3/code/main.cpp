#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

#include "algebra3.h"
#include "imageIO.h"
#include "RayTracer.h"

#define PI 3.1415926535898
#define Tan(th) tan(PI/180*(th))
#define Cos(th) cos(PI/180*(th))

using namespace std;

vec3 eye, direct, vertical = vec3(0, 1, 0);
float angle;
int resolusionW, resolusionH;

float SOx, SOy, SOz, Sr;
float Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz;
//float Lx, Ly, Lz;

cTriangle triangle;
cSphere   sphere;
cLight    light;

vector<cSphere>   vSphere;
vector<cTriangle> vTriangle;
vector<cLight>    vLight;

vec3 Ka = vec3(0.700, 0.600, 0.300);
vec3 Kd = vec3(1.000, 1.000, 1.000);
vec3 Ks = vec3(1.000, 1.000, 1.000);
float r, g, b, kaa, kdd, kss, reflect, refract;
float Ia, Id, Is, Ii, Ke, Nr;

void readFile() {
    ifstream ifile("input.txt");
    string test;
    while( ifile >> test ) {
        switch (test[0]) {
            case 'E':
                ifile >> eye[0] >> eye[1] >> eye[2];
                break;
            case 'V':
                ifile >> direct[0] >> direct[1] >> direct[2];
                break;
            case 'F':
                ifile >> angle;
                break;
            case 'R':
                ifile >> resolusionW >> resolusionH;
                break;
            case 'S':
                ifile >> sphere.x >> sphere.y >> sphere.z >> sphere.r;
                vSphere.push_back(sphere);
                break;
            case 'T':
                ifile >> triangle.x1 >> triangle.y1 >> triangle.z1 >>
                         triangle.x2 >> triangle.y2 >> triangle.z2 >>
                         triangle.x3 >> triangle.y3 >> triangle.z3 >>
                         triangle.r  >> triangle.g  >> triangle.b;
                vTriangle.push_back(triangle);
                break;
            case 'L':
                ifile >> light.x >> light.y >> light.z;
                vLight.push_back(light);
                break;
            case 'M':
                ifile >> r >> g >> b >> kaa >> kdd >> kss >> Ke >> Nr;
                break;
            case 'X':
                break;
        }
    }
}

int main()
{
    readFile();
    ColorImage image;
    image.init(resolusionW, resolusionH);
    Ke = 200.0;

/// generate distributed ray camera
    vector<vec3> start, dir;
    float focal = 15, apertureN = 2.2, len = focal / apertureN / 2, focalPlane = 600.0;

    start.push_back(eye);                              dir.push_back(direct);
    start.push_back(vec3(eye[0]+len, eye[1], eye[2])); dir.push_back(vec3(direct[0]-len/focalPlane, direct[1], direct[2]));
    start.push_back(vec3(eye[0]-len, eye[1], eye[2])); dir.push_back(vec3(direct[0]+len/focalPlane, direct[1], direct[2]));
    start.push_back(vec3(eye[0], eye[1]+len, eye[2])); dir.push_back(vec3(direct[0], direct[1]-len/focalPlane, direct[2]));
    start.push_back(vec3(eye[0], eye[1]-len, eye[2])); dir.push_back(vec3(direct[0], direct[1]+len/focalPlane, direct[2]));

    vector<RayTracer> dRayTracer;
    for(int i = 0; i < 5; i += 1) {
        RayTracer raytracer(start[i], dir[i], vertical, angle, resolusionW, resolusionH, vTriangle, vSphere, vLight, Ke);
        dRayTracer.push_back(raytracer);
    }

/// ray tracing
    for(int x = 0; x < resolusionW; x += 1) {
        for(int y = 0; y < resolusionH; y += 1) {

            Pixel color = {255, 255, 255};
            vector<Ray>  dRay;
            vector<Data> dData;
            int r = 0, g = 0, b = 0;
            for(int i = 0; i < 5; i += 1) {
                Ray ray(start[i], dRayTracer[i].firstRayGenerator(x, y));
                Data data = dRayTracer[i].isIntersected(ray);
                dRay.push_back(ray);
                dData.push_back(data);
                if(dData[i].isIntersected) {
                    r += 0.2 * dData[i].color.R;
                    g += 0.2 * dData[i].color.G;
                    b += 0.2 * dData[i].color.B;
                }
            }
            color.R = r;
            color.G = g;
            color.B = b;
            for(int i = 0; i < 5; i += 1) {
                if(dData[i].isIntersected) {
                    image.writePixel(x, y, color);
                }
            }
        }
    }
    char outputname[15] = "output600.ppm";
    image.outputPPM(outputname);
    return 0;
}
