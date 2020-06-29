//
// Created by 81406 on 2020/6/15.
//

#ifndef CG_VECTOR3D_H
#define CG_VECTOR3D_H
class Vector3d { public:  double x_, y_, z_;

    Vector3d(double x=0, double y=0, double z=0);

    double modul2();

    double modul();

    Vector3d cross(Vector3d& v);

    double dot(Vector3d& v);

    Vector3d operator-(const Vector3d& v);

    Vector3d operator+(const Vector3d& v);

    Vector3d operator*(const double x);

    Vector3d operator/(const double x);

    double mag();

    void normalize(); };
#endif //CG_VECTOR3D_H
