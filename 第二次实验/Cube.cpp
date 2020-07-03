//
// Created by 81406 on 2020/6/20.
//

#include "Cube.h"
#include <cmath>
#include <algorithm>
#include <vector>

bool Cube::intersect(Ray ray, Hit &hit) {
    hit.material_ = this->material_;
    hit.t_ = std::numeric_limits<double>::infinity ();

    Vector3d Rd = ray.directionVector_;
//    std::vector<Hit> hitArray;
    for (int *tmp:tri) {
        Vector3d E1 = dot[tmp[0]] - dot[tmp[1]];
        Vector3d E2 = dot[tmp[0]] - dot[tmp[2]];
        Vector3d S = dot[tmp[0]] - ray.origin_;

        double a = 1/(Rd.x_ * E1.y_ * E2.z_ +  E1.x_ * E2.y_ * Rd.z_ +  E2.x_ * Rd.y_ * E1.z_ - (E2.x_ * E1.y_ * Rd.z_ + +  E1.x_ * Rd.y_ * E2.z_ +  Rd.x_ * E2.y_ * E1.z_));
        double b = a * (S.x_ * E1.y_ * E2.z_ +  E1.x_ * E2.y_ * S.z_ +  E2.x_ * S.y_ * E1.z_ - (E2.x_ * E1.y_ * S.z_ + +  E1.x_ * S.y_ * E2.z_ +  S.x_ * E2.y_ * E1.z_));
        double c = a * (Rd.x_ * S.y_ * E2.z_ +  S.x_ * E2.y_ * Rd.z_ +  E2.x_ * Rd.y_ * S.z_ - (E2.x_ * S.y_ * Rd.z_ + +  S.x_ * Rd.y_ * E2.z_ +  Rd.x_ * E2.y_ * S.z_));
        double d = a * (Rd.x_ * E1.y_ * S.z_ +  E1.x_ * S.y_ * Rd.z_ +  S.x_ * Rd.y_ * E1.z_ - (S.x_ * E1.y_ * Rd.z_ + +  E1.x_ * Rd.y_ * S.z_ +  Rd.x_ * S.y_ * E1.z_));

        if (b >= 5E-10 && c >= 5E-10 && d >= 5E-10 && c <= 1 && d <= 1 && c + d <= 1) {
            if(hit.t_ >= b){
                hit.t_ = b;
                hit.P_ = ray.origin_ + ray.directionVector_ * hit.t_;
                hit.N_ = E1.cross (E2);
                hit.N_.normalize ();
            }

        }


    }
    hit.obj_ = this;
    return true;
}

void Cube::initTri(int (init[12][3])) {
        for (int i = 0 ; i < 12; i++) {
            for (int j = 0; j < 3; ++j) {
                tri[i][j] = init[i][j];
            }
        }
}
