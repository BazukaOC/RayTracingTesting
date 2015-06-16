#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "algebra3.h"

class Ray {
public:
	Ray() : m_Origin(vec3(0, 0, 0)), m_Direction(vec3(0, 0, 0)) {};
	Ray(vec3& a_Origin, vec3& a_Dir);
private:
	vec3 m_Origin;
	vec3 m_Direction;
};

#endif // RAY_H_INCLUDED
