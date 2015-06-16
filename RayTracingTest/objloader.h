#ifndef OBJLOADER_H_INCLUDED
#define OBJLOADER_H_INCLUDED

#include <vector>
#include "algebra3.h"

class GROUP {
public:
    std::vector<vec3>     vertices_;
    unsigned int          numVertices_ = 0;
    std::vector<int>      faces_;
    unsigned int          numFaces_ = 0;
    void clear();
//    std::string group_id_, mtl_id_;
//    float Ns_, Ni_, illum_;
//    vec3  Ka_, Kd_, Ks_, Ke_;
};

class OBJLOADER {
public:
    std::vector<vec3>     vertices_;
    unsigned int          numVertices_ = 0;
    std::vector<int>      faces_;

    std::vector<GROUP>    groups_;
    unsigned int          numGroups_;
};

#endif // OBJLOADER_H_INCLUDED
