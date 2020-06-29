//
// Created by 81406 on 2020/6/15.
//

#include "Vector3d.h"
#include <cmath>

Vector3d::Vector3d(double a, double b, double c) : x_{a}, y_{b}, z_{c} {}

double Vector3d::modul2() { return (x_ * x_ + y_ * y_ + z_ * z_); }

double Vector3d::modul() { return sqrtf (modul2 ()); }

Vector3d Vector3d::cross(Vector3d &v) {
    Vector3d rev (y_ * v.z_ - z_ * v.y_, z_ * v.x_ - x_ * v.z_, x_ * v.y_ - y_ * v.x_);
    return rev;
}

double Vector3d::dot(Vector3d &v) { return (x_ * v.x_ + y_ * v.y_ + z_ * v.z_); }

Vector3d Vector3d::operator-(const Vector3d &v)  { return {x_ - v.x_, y_ - v.y_, z_ - v.z_}; }

Vector3d Vector3d::operator+(const Vector3d &v)  { return {x_ + v.x_, y_ + v.y_, z_ + v.z_}; }

Vector3d Vector3d::operator*(const double x)  { return {x_ * x, y_ * x, z_ * x}; }

Vector3d Vector3d::operator/(const double x)  { return {x_ / x, y_ / x, z_ / x}; }


double Vector3d::mag() { return sqrtf (x_ * x_ + y_ * y_ + z_ * z_); }

void Vector3d::normalize() {
    float m = mag();
    x_ = x_ / m;
    y_ = y_ / m;
    z_ = z_ / m;
};
