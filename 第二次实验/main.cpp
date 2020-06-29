#include <iostream>
#include <algorithm>
#include <vector>
#include <GL/glut.h>
#include <cmath>
#include "Light.h"
#include "Sphere.h"
#include "Cube.h"


const int MAX_RECURSION_DEPTH =1;
const double VIEWPORT_X =16;
const double VIEWPORT_Y = 12;
const double FOCAL_LENGTH = 0;
const int WINDOW_W = 800;
const int WINDOW_H = 600;

const Ray camera (Vector3d (-3.0f, 4.0f, 10.0f), Vector3d (0.0f, 0.0f, 0.0f));
const Vector3d upperRightCorner (VIEWPORT_X / 2, VIEWPORT_Y / 2, FOCAL_LENGTH);
const Vector3d bottomLeftCorner (-1 * VIEWPORT_X / 2, -1 * VIEWPORT_Y / 2, FOCAL_LENGTH);

Light light;
Color ambientLight;
Sphere *sphere = new Sphere;

Cube *cube = new Cube;
GLdouble specular_a = 0.6f;

std::vector<Object *> objects;
GLubyte pixelData[WINDOW_H][WINDOW_W][3];

void ConstructScene() {

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // clear the screen

    light = Light (Color (1.0f, 1.0f, 1.0f), Vector3d (2.0f, 4.0f, 5.5f));
    ambientLight = Color (0.5f, 0.5f, 0.4f);


    sphere->center_ = Vector3d (-3.0f, 0.0f, 0.0f);
    sphere->radius_ = 1.0;
    sphere->material_.diffuseColor_ = Color (0.76f, 0.02f, 0.08f);
    sphere->material_.ambientColor_ = Color (0.76f, 0.02f, 0.08f);
    sphere->material_.specularColor_ = Color (specular_a, specular_a, specular_a);
    sphere->material_.alpha_ = 0.8;
    sphere->material_.refractIndex_ = 1.5;
    sphere->material_.specExponent_ = 10.0;



    objects.push_back (sphere);

    cube->material_.diffuseColor_ = Color (0.76f, 0.02f, 0.08f);
    cube->material_.ambientColor_ = Color (0.76f, 0.02f, 0.08f);
    cube->material_.specularColor_ = Color (0.8f, 0.8f, 0.8f);
    cube->material_.alpha_ = 0.8;
    cube->material_.refractIndex_ = 1.5;
    cube->material_.specExponent_ = 10.0;
    objects.push_back (cube);

}

Hit DetectSceneHit(Ray &ray) {
    Hit ret, hit;
    ret.material_.color_ = Color (25.0f, 25.0f, 25.0f);
    ret.t_ = std::numeric_limits<double>::infinity ();

    for (std::vector<Object *>::iterator iter = objects.begin (); iter != objects.end (); iter++) {
        Object *object =  (*iter);
        object->intersect (ray, hit);

        if (hit.t_ < ret.t_) {
            ret.material_ = hit.material_;
            ret.N_ = hit.N_;
            ret.P_ = hit.P_;
            ret.t_ = hit.t_;
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

void MouseFunc(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_RIGHT_BUTTON:
//            if () exit (-1);
        if(state == GLUT_DOWN && specular_a < 1){
            specular_a = specular_a + 0.1f;
        }
            break;
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN && specular_a > 0.1){
                specular_a = specular_a - 0.1f;
            }
            break;
        default:
            break;
    }

    glutPostRedisplay ();
}



int main(int argc, char *argv[]) {
    std::cout << "Ray Casting" << std::endl;

    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize (WINDOW_W, WINDOW_H);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Ray Casting - 3D scene");


    glutDisplayFunc (DisplayFunc);
    glutMouseFunc (MouseFunc);
    // register myMouse function
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
