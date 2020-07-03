//
// Created by 81406 on 2020/6/11.
//

#include "Sphere.h"
#include <cmath>
#include <algorithm>

bool Sphere::intersect(Ray ray, Hit &hit) {
    hit.material_ = this->material_;
    hit.t_ = std::numeric_limits<double>::infinity();

    Vector3d O = ray.origin_;                       //光源位置
    Vector3d V = ray.directionVector_;              //光线方向
    Vector3d C = center_;                           //圆心位置
    Vector3d OC = O - C;

    double a = V.mag() * V.mag();
    double b = 2 * (V.dot(OC));
    double c = OC.mag() * OC.mag() - radius_ * radius_;

    double discr = b * b - 4.0f * a * c;
    if (discr < 0.0) {
        return false;
    } else {
        double t0 = (-b + sqrt(discr)) / (2 * a);
        double t1 = (-b - sqrt(discr)) / (2 * a);

        if (t0 >= 5E-4 && t1 >= 5E-4) {
            hit.t_ = std::min(t0, t1);
        } else if (t0 >= 5E-4 || t1 >= 5E-4) {
            hit.t_ = std::max(t0, t1);
        }

        if (hit.t_ != std::numeric_limits<double>::infinity()) {
            Vector3d tmp_direction = ray.directionVector_ * hit.t_;
            hit.P_ = OC + tmp_direction;
            hit.N_ = hit.P_;
        }
    }

    hit.P_ = hit.P_ + center_;
    hit.N_.normalize();
    hit.obj_ = this;
    return true;
}