//
// Created by 81406 on 2020/6/9.
//

#ifndef CG_LIGHT_H
#define CG_LIGHT_H
#include "Color.h"
#include "Vector3d.h"

class Light { public:  Color color_;  Vector3d P_;

    Light() = default;;

    Light(const Color& color,const Vector3d& v) : color_{ color }, P_{ v } {}; };

#endif //CG_LIGHT_H
