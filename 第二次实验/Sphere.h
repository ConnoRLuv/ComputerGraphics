//
// Created by 81406 on 2020/6/11.
//

#ifndef CG_SPHERE_H
#define CG_SPHERE_H

#include "Color.h"
#include "Ray.h"
#include "Object.h"

class Sphere : public Object{
public:
Vector3d center_;
double radius_;

Sphere() = default;

bool intersect(Ray ray, Hit &hit) override;

};




#endif //CG_SPHERE_H
