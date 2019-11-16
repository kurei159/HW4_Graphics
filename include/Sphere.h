#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {
public:
    Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d &color, bool mir) : c(center), r(radius), Objectcolor(color), mirror(mir) {}

    virtual HitRecord intersect(const Ray &ray);

private:
    Eigen::Vector3d c;
	Eigen::Vector3d Objectcolor;
	bool mirror = false;
    double r;
};
}

#endif
