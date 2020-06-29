//
// Created by 81406 on 2020/6/20.
//

#include "Cube.h"
#include <cmath>
#include <algorithm>
#include <vector>

bool Cube::intersect(Ray ray, Hit &hit) {

    hit.t_ = std::numeric_limits<double>::infinity ();

    Vector3d Rd = ray.directionVector_;
    std::vector<Hit> hitArray;
    for (int *tmp:tri) {
        Vector3d E1 = dot[tmp[0]] - dot[tmp[1]];
        Vector3d E2 = dot[tmp[0]] - dot[tmp[2]];
        Vector3d S = dot[tmp[0]] - ray.origin_;

        double a = 1 / (Rd.x_ * E1.y_ * E2.z_ + Rd.y_ * E1.z_ * E2.x_ + Rd.z_ * E1.x_ * E2.y_ -
                        (Rd.z_ * E1.y_ * E2.x_ + Rd.y_ * E1.x_ * E2.z_ + Rd.x_ * E1.z_ * E2.y_));
        double b = a * (S.x_ * E1.y_ * E2.z_ + S.y_ * E1.z_ * E2.x_ + S.z_ * E1.x_ * E2.y_ -
                        (S.z_ * E1.y_ * E2.x_ + S.y_ * E1.x_ * E2.z_ + S.x_ * E1.z_ * E2.y_));
        double c = a * (Rd.x_ * S.y_ * E2.z_ + Rd.y_ * S.z_ * E2.x_ + Rd.z_ * S.x_ * E2.y_ -
                        (Rd.z_ * S.y_ * E2.x_ + Rd.y_ * S.x_ * E2.z_ + Rd.x_ * S.z_ * E2.y_));
        double d = a * (Rd.x_ * E1.y_ * S.z_ + Rd.y_ * E1.z_ * S.x_ + Rd.z_ * E1.x_ * S.y_ -
                        (Rd.z_ * E1.y_ * S.x_ + Rd.y_ * E1.x_ * S.z_ + Rd.x_ * E1.z_ * S.y_));

        if (b > 0 && c >= 0 && d >= 0 && c <= 1 && d <= 1 && c + d <= 1) {
            Hit hitTmp;
            hitTmp.t_ = b;
            hitTmp.P_ = ray.directionVector_ + hitTmp.t_;
            hitTmp.N_ = E2.cross (E1);
            hitTmp.N_.normalize ();
            hitArray.push_back(hitTmp);
        }
    }

    if(!hitArray.empty()){
        for(Hit tmp:hitArray){
            if(hit.t_ > tmp.t_){
                hit = tmp;
            }
        }
        hit.material_ = this->material_;
        return true;
    }

    return false;
}