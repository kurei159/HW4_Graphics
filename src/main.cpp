#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "NewShape.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

    Vector3d center;
	Vector3d SphereColor; //Added Sphere Color
	
	SphereColor = { 0.635, 0.27, 1};
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2, SphereColor, false));

	SphereColor = { 0.13, 1, 0 };
    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, SphereColor, false));
	
	SphereColor = { 0.13, 1, 0 };
    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, .5, SphereColor, false));
	
	
	//Problem 1: Triangle
	
	Vector3d v0;
	Vector3d v1;
	Vector3d v2;
	Vector3d TriangleColor;

	v0[0] = 0;
	v0[1] = -5;
	v0[2] = 6;
	
	v1[0] = -4;
	v1[1] = 2;
	v1[2] = 4;

	v2[0] = 8;
	v2[1] = 4;
	v2[2] = 8;

	TriangleColor[0] = 0.55;
	TriangleColor[1] = 0.55;
	TriangleColor[2] = 0.55;

	scene.addShape(new NewShape(v0, v1, v2, TriangleColor, false));

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
