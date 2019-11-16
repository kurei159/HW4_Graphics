#ifndef NEWSHAPE_H
#define NEWSHAPE_H
#include "Shape.h"
/*
To create a triangle, we need vertex 1, 2, & 3 of the triangle
*/

namespace Raytracer148 {
	class NewShape : public Shape {

	public:
		NewShape(Eigen::Vector3d &V0, Eigen::Vector3d &V1, Eigen::Vector3d &V2, Eigen::Vector3d &color, bool mir) : v0(V0), v1(V1), v2(V2), Objectcolor(color), mirror(mir){}

		virtual HitRecord intersect(const Ray &ray);

	private:
		Eigen::Vector3d Objectcolor;
		Eigen::Vector3d v0;
		Eigen::Vector3d v1;
		Eigen::Vector3d v2;

		bool mirror = false;

		//Barycentric Coordinates
		double u;
		double v;
		double w;

	};
}
#endif

