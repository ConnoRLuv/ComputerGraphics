//
// Created by 81406 on 2020/6/11.
//

#ifndef CG_OBJECT_H
#define CG_OBJECT_H

#include "Color.h"
#include "Ray.h"

class Hit;

class Material {
public:
    Color color_;
    Color ambientColor_;
    Color specularColor_;
    Color diffuseColor_;

    double alpha_;
    double refractIndex_;
    double specExponent_;
    double reflectionCoeff_;

    Material() =default;
};

class Object {
public:
    Material material_;

    Object() = default;;

    virtual bool intersect(Ray ray, Hit& hit) = 0;
};

class Hit {
public:
    Vector3d P_;
    Vector3d N_;
    Object* obj_;

    double t_;
    Material material_;

    Hit() =default;
};

#endif //CG_OBJECT_H
