#include <iostream>
#include <algorithm>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include "Light.h"
#include "Sphere.h"
#include "Cube.h"
#include "Flat.h"


const int MAX_RECURSION_DEPTH = 3;
const double VIEWPORT_X = 16;
const double VIEWPORT_Y = 12;
const double FOCAL_LENGTH = 0;
const int WINDOW_W = 800;
const int WINDOW_H = 600;

//const Ray camera (Vector3d (5.0f, 5.0f, 25.0f), Vector3d (0.0f, -40.0f, 2.0f));
const Ray camera (Vector3d (10.0f, 5.0f, 35.0f), Vector3d (0.0f, 5.0f, -5.0f));

const Vector3d upperRightCorner (VIEWPORT_X / 2, VIEWPORT_Y / 2, FOCAL_LENGTH);
const Vector3d bottomLeftCorner (-1 * VIEWPORT_X / 2, -1 * VIEWPORT_Y / 2, FOCAL_LENGTH);

Light light;
Color ambientLight;
Sphere *sphere;
Sphere *sphere1;
Sphere *sphere2;
Flat *flat_bottom;
Flat *flat_back;
Flat *flat_left;
Cube *cube;
GLdouble specular_a = 0.6f;

std::vector<Object *> objects;
GLubyte pixelData[WINDOW_H][WINDOW_W][3];

void ConstructScene() {

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // clear the screen

    light = Light (Color (1.0f, 1.0f, 1.0f), Vector3d (1.0f, 8.0f, 8.0f));
    ambientLight = Color (0.5f, 0.5f, 0.4f);


    sphere = new Sphere;
    sphere->center_ = Vector3d (3.0f, 0.25f, 1.0f);         //设置圆心位置
    sphere->radius_ = 1.25;             //设置圆半径
    sphere->material_.diffuseColor_ = Color (0.3f, 0.3f, 0.3f);     //漫反射系数
    sphere->material_.ambientColor_ = Color (0.3f, 0.3f, 0.3f);     //环境光反射系数
    sphere->material_.specularColor_ = Color (specular_a, specular_a, specular_a);  //镜面反射系数
    sphere->material_.alpha_ = 1.0;
    sphere->material_.refractIndex_ = 0.5;
    sphere->material_.reflectionCoeff_ = 0.2;
    sphere->material_.specExponent_ = 80.0;     //反射指数，此值越大，则高光区域越集中
    objects.push_back (sphere);

//    sphere = new Sphere;
//    sphere->center_ = Vector3d (0.0f, 2.0f, 0.0f);
//    sphere->radius_ = 1.0;
//    sphere->material_.diffuseColor_ = Color (0.3f, 0.3f, 0.8f);
//    sphere->material_.ambientColor_ = Color (0.3f, 0.3f, 0.8f);
//    sphere->material_.specularColor_ = Color (specular_a, specular_a, specular_a);
//    sphere->material_.alpha_ = 0.2;
//    sphere->material_.refractIndex_ = 0.5;
////    sphere->material_.reflectionCoeff_ = 0.8;
//    sphere->material_.specExponent_ = 60.0;
//    objects.push_back (sphere);

//    sphere1 = new Sphere;
//    sphere1->center_ = Vector3d (-0.5f, 1.2f, 0.0f);
//    sphere1->radius_ = 1.0;
//    sphere1->material_.diffuseColor_ = Color (0.8f, 0.3f, 0.3f);
//    sphere1->material_.ambientColor_ = Color (0.8f, 0.3f, 0.3f);
//    sphere1->material_.specularColor_ = Color (specular_a, specular_a, specular_a);
//    sphere1->material_.alpha_ = 1.0;
//    sphere1->material_.refractIndex_ = 0.5;
////    sphere1->material_.reflectionCoeff_ = 0.8;
//    sphere1->material_.specExponent_ = 60.0;
//    objects.push_back (sphere1);

//    sphere2 = new Sphere;
//    sphere2->center_ = Vector3d (0.5f, 1.2f, 0.0f);
//    sphere2->radius_ = 1.0;
//    sphere2->material_.diffuseColor_ = Color (0.3f, 0.8f, 0.3f);
//    sphere2->material_.ambientColor_ = Color (0.3f, 0.8f, 0.3f);
//    sphere2->material_.specularColor_ = Color (specular_a, specular_a, specular_a);
//    sphere2->material_.alpha_ = 0.8;
//    sphere2->material_.refractIndex_ = 0.5;
////    sphere2->material_.reflectionCoeff_ = 0.8;
//    sphere2->material_.specExponent_ = 60.0;
//    objects.push_back (sphere2);

    cube = new Cube;
    cube->dot = new Vector3d[8]{Vector3d (-2.0f, -1.0f, -1.0f),
                                Vector3d (-2.0f, 1.0f, -1.0f),
                                Vector3d (-2.0f, 1.0f, 1.0f),
                                Vector3d (-2.0f, -1.0f, 1.0f),
                                Vector3d (0.0f, -1.0f, 1.0f),
                                Vector3d (0.0f, 1.0f, 1.0f),
                                Vector3d (0.0f, 1.0f, -1.0f),
                                Vector3d (0.0f, -1.0f, -1.0f)};
    int cube_tmp[12][3] = {{0, 2, 1},
                           {0, 3, 2},
                           {3, 5, 2},
                           {3, 4, 5},
                           {4, 6, 5},
                           {4, 7, 6},
                           {7, 1, 6},
                           {7, 0, 1},
                           {2, 6, 1},
                           {2, 5, 6},
                           {0, 4, 3},
                           {0, 7, 4}};
    cube->initTri (cube_tmp);
    cube->material_.diffuseColor_ = Color (0.3f, 0.3f, 0.9f);
    cube->material_.ambientColor_ = Color (0.3f, 0.3f, 0.9f);
    cube->material_.specularColor_ = Color (0.6f, 0.6f, 0.6f);
    cube->material_.alpha_ = 1.0;
    cube->material_.refractIndex_ = 0.5;
    cube->material_.specExponent_ = 10.0;
    objects.push_back (cube);

    flat_bottom = new Flat;
    flat_bottom->dot = new Vector3d[4]{
            Vector3d (5.0f, -1.0f, 8.0f),
            Vector3d (5.0f, -1.0f, -5.0f),
            Vector3d (-5.0f, -1.0f, -5.0f),
            Vector3d (-5.0f, -1.00f, 8.0f)
    };
    int flat_tmp[2][3] = {{0, 2, 1},
                          {0, 3, 2}
    };
    flat_bottom->initTri (flat_tmp);
    flat_bottom->material_.diffuseColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_bottom->material_.ambientColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_bottom->material_.specularColor_ = Color (0.2f, 0.2f, 0.2f);
    flat_bottom->material_.alpha_ = 1.0;
    flat_bottom->material_.refractIndex_ = 0.5;
    flat_bottom->material_.reflectionCoeff_ = 0.8;
    flat_bottom->material_.specExponent_ = 10.0;
    objects.push_back (flat_bottom);

    flat_left = new Flat;
    flat_left->dot = new Vector3d[4]{
            Vector3d (-3.0f, -1.0f, 8.0f),
            Vector3d (-3.0f, -1.00f, -5.0f),
            Vector3d (-3.0f, 5.0f, -5.0f),
            Vector3d (-3.0f, 5.0f, 8.0f)
    };
    int flat_tmp1[2][3] = {{0, 2, 1},
                          {0, 3, 2}
    };
    flat_left->initTri (flat_tmp1);
    flat_left->material_.diffuseColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_left->material_.ambientColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_left->material_.specularColor_ = Color (0.2f, 0.2f, 0.2f);
    flat_left->material_.alpha_ = 1.0;
    flat_left->material_.refractIndex_ = 0.5;
    flat_left->material_.reflectionCoeff_ =  0.8;
    flat_left->material_.specExponent_ = 10.0;
    objects.push_back (flat_left);

    flat_back = new Flat;
    flat_back->dot = new Vector3d[4]{
            Vector3d (5.0f, 5.0f, -5.0f),
            Vector3d (5.0f, -1.0f, -5.0f),
            Vector3d (-3.0f, -1.0f, -5.0f),
            Vector3d (-3.0f, 5.00f, -5.0f)
    };
    int flat_tmp2[2][3] = {{0, 2, 1},
                          {0, 3, 2}
    };
    flat_back->initTri (flat_tmp2);
    flat_back->material_.diffuseColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_back->material_.ambientColor_ = Color (0.1f, 0.1f, 0.1f);
    flat_back->material_.specularColor_ = Color (0.2f, 0.2f, 0.2f);
    flat_back->material_.alpha_ = 1.0;
    flat_back->material_.refractIndex_ = 0.5;
    flat_back->material_.reflectionCoeff_ =  0.8;
    flat_back->material_.specExponent_ = 10.0;
    objects.push_back (flat_back);
}

Hit DetectSceneHit(Ray &ray) {
    Hit hit;
    Hit ret;
    ret.material_.color_ = Color (25.0f, 25.0f, 25.0f);
    ret.t_ = std::numeric_limits<double>::infinity ();

    for (auto object : objects) {
        object->intersect (ray, hit);

        if (hit.t_ < ret.t_) {
            ret.material_ = hit.material_;
            ret.N_ = hit.N_;
            ret.P_ = hit.P_;
            ret.t_ = hit.t_;
            ret.obj_ = hit.obj_;
        }
    }
    return ret;
}

Hit RayCast(Ray &ray, int depth) {
    Hit hit;

    //Returns background color if maximum recursion depth was hit
    if (depth == 0) {
        hit.material_.color_ = Color (0.1f, 0.1f, 0.1f);
        hit.t_ = std::numeric_limits<double>::infinity ();
        return hit;
    }

    //Find object intersection
    Hit rayHit = DetectSceneHit (ray);
    if (rayHit.t_ != std::numeric_limits<double>::infinity ()) {   //Ambient lighting
        rayHit.material_.color_ = rayHit.material_.ambientColor_ * ambientLight;

        //Direct Lighting
        Ray lightRay;
        lightRay.origin_ = rayHit.P_;
        lightRay.directionVector_ = light.P_ - rayHit.P_;
        Hit lightRayHit = DetectSceneHit (lightRay);

        if (lightRayHit.t_ == std::numeric_limits<double>::infinity ()) {
            lightRay.directionVector_.normalize ();
            ray.directionVector_.normalize ();
            Vector3d h = lightRay.directionVector_ - ray.directionVector_;
            h.normalize ();

            //Diffuse Lighting
            double dot1 = lightRay.directionVector_.dot (rayHit.N_);
            rayHit.material_.color_ =
                    rayHit.material_.color_ + light.color_ * rayHit.material_.diffuseColor_ * std::max (0.0, dot1);

            //Specular Lighting
            double dot2 = h.dot (rayHit.N_);
            double hnorm = powf (dot2, rayHit.material_.specExponent_);
            rayHit.material_.color_ = rayHit.material_.color_ + light.color_ * rayHit.material_.specularColor_ * hnorm;


        }


        if (rayHit.material_.reflectionCoeff_ != 0.0) {
            Ray reflected_ray;
            reflected_ray.origin_ = rayHit.P_;
            reflected_ray.directionVector_ = ray.directionVector_;
            reflected_ray.directionVector_.normalize ();
            reflected_ray.directionVector_ =
                    reflected_ray.directionVector_ -
                    ((rayHit.N_ * reflected_ray.directionVector_.dot (rayHit.N_)) * 2.0);
            reflected_ray.directionVector_.normalize();
            Hit tmp = RayCast (reflected_ray, depth - 1);
            rayHit.material_.color_ += tmp.material_.color_ * rayHit.material_.reflectionCoeff_;
        }
//        else if(rayHit.material_.alpha_ != 1.0){
//            double ni = 1.0;
//            double nT = rayHit.material_.refractIndex_;
//
//            double cosT = sqrt(1-ni*ni*(1-pow(ray.directionVector_.dot(rayHit.N_),2))/(nT*nT));
//            Ray refracted_ray1;
//            refracted_ray1.origin_ = rayHit.P_;
//            refracted_ray1.directionVector_ = -ray.directionVector_ * (-ni/nT) + rayHit.N_*(ni/nT * (-ray.directionVector_).dot(rayHit.N_) - cosT)  ;
//            refracted_ray1.directionVector_.normalize();
//            Hit tmp = RayCast (refracted_ray1, depth - 1);
//            rayHit.material_.color_ += tmp.material_.color_ * rayHit.material_.alpha_;
//        }

        return rayHit;
    } else {
        rayHit.material_.color_ = Color (0.1f, 0.1f, 0.1f);
        return rayHit;
    }
}

void RenderScene() {
    //Iterate through all screen pixels
    for (int i = 0; i < WINDOW_W; i++) {
        for (int j = 0; j < WINDOW_H; j++) {
            //Set background color
            pixelData[j][i][0] = 25;
            pixelData[j][i][1] = 25;
            pixelData[j][i][2] = 25;

            //Construct viewing ray
            double x = bottomLeftCorner.x_ + (upperRightCorner.x_ - bottomLeftCorner.x_) * ((i + 0.5) / WINDOW_W);
            double y = bottomLeftCorner.y_ + (upperRightCorner.y_ - bottomLeftCorner.y_) * ((j + 0.5) / WINDOW_H);
            Vector3d point (x, y, upperRightCorner.z_);

            Ray cameraRay;
            cameraRay.origin_ = camera.origin_;
            cameraRay.directionVector_ = point - (Vector3d) camera.origin_;
            cameraRay.directionVector_.normalize ();

            Hit hit = RayCast (cameraRay, MAX_RECURSION_DEPTH);

            //If an object was hit, set the color for that pixel appropriately
            pixelData[j][i][0] = std::min ((int) (hit.material_.color_.r_ * 255), 255);
            pixelData[j][i][1] = std::min ((int) (hit.material_.color_.g_ * 255), 255);
            pixelData[j][i][2] = std::min ((int) (hit.material_.color_.b_ * 255), 255);
        }
    }

    glDrawPixels (WINDOW_W, WINDOW_H, GL_RGB, GL_UNSIGNED_BYTE, pixelData);
}

void DisplayFunc() {
    ConstructScene ();

    RenderScene ();

    glFlush ();
}



int main(int argc, char *argv[]) {
    std::cout << "Ray Casting" << std::endl;

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize (WINDOW_W, WINDOW_H);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Ray Casting - 3D scene");


    glutDisplayFunc (DisplayFunc);

    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
    glShadeModel (GL_SMOOTH);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_NORMALIZE);
    glClearColor (0.1f, 0.1f, 0.1f, 0.0f);  // background is light gray
    glutMainLoop ();

    for (auto &object : objects) { delete object; }

    return 0;
}
