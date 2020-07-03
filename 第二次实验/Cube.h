//
// Created by 81406 on 2020/6/20.
//

#ifndef CG_CUBE_H
#define CG_CUBE_H

#include "Color.h"
#include "Ray.h"
#include "Object.h"

class Cube: public Object{
public:
    Vector3d *dot{};
    int tri[12][3]{};


    Cube() = default;
    bool intersect(Ray ray, Hit &hit) override;
    void initTri(int init[12][3]);

};
#endif //CG_CUBE_H
