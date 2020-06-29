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
    Vector3d dot[8] = {Vector3d(-1.0f,-1.0f,-1.0f),
                     Vector3d(-1.0f,1.0f,-1.0f),
                     Vector3d(-1.0f,1.0f,1.0f),
                     Vector3d(-1.0f,-1.0f,1.0f),
                     Vector3d(1.0f,-1.0f,1.0f),
                     Vector3d(1.0f,1.0f,1.0f),
                     Vector3d(1.0f,1.0f,-1.0f),
                     Vector3d(1.0f,-1.0f,-1.0f)};

    int tri[12][3] = {{0,2,1},
                      {0,3,2},
                      {3,5,2},
                      {3,4,5},
                      {4,6,5},
                      {4,7,6},
                      {7,1,6},
                      {7,0,1},
                      {2,1,6},
                      {2,6,5},
                      {0,4,3},
                      {0,7,4}};

    Cube() = default;
    bool intersect(Ray ray, Hit &hit) override;


};
#endif //CG_CUBE_H
