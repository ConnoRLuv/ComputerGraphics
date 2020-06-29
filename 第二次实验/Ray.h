//
// Created by 81406 on 2020/6/11.
//

#ifndef CG_RAY_H
#define CG_RAY_H


#include <utility>
#include "Vector3d.h"

class Ray {
public:
    Vector3d origin_, directionVector_;

    Ray() = default;

    Ray(Vector3d  origin_, Vector3d  directionVector_) : origin_{origin_ }, directionVector_{directionVector_ } {};
};

#endif //CG_RAY_H
