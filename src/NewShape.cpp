#include "NewShape.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

namespace Raytracer148 {
	HitRecord NewShape::intersect(const Ray &ray) {
		HitRecord result;
		result.t = -1; //Assume object is projected


		//Ray-Triangle
		/*
		Condition I: Point is on Ray by the ray parametric equation: r(t) = p+tD
		Condition II: Point is on Plane if: (x-a) dot n = 0
		Condition III: Point is on inside of all 3 edges
		*/


		//Get Plane Normal
		Eigen::Vector3d v0v1 = v1 - v0;
		Eigen::Vector3d v0v2 = v2 - v0;
		Eigen::Vector3d PlaneNormal = v0v1.cross(v0v2);
	


		//To find r(t), we must find t
		//If the denominator is close to 0, the plane and the ray are parallel. Which means no hit!
		double denom = PlaneNormal.dot(ray.direction);

		if (abs(denom) < numeric_limits<double>::epsilon()) //No Hit!
		{
			return result; 
		}

		//If hit on plane:
		double d = PlaneNormal.dot(v0); //Get Distance between v0 and the normal
		
		double t = ((PlaneNormal.dot(ray.origin) + d) / denom); //Get t, defined by t = N * ray.origin + D / N * ray.direction
		if (t < 0) //Triangle is behind if the magnitude is negative, no hit;
		{
			return result; 
		}
		
		//Ray Parametric Equation satisfied
		Eigen::Vector3d rt = ray.origin + t * ray.direction;




		//double area = PlaneNormal.norm(); //Length of the Plane's Normal is the area of the triange (v0,v1,v2) = (A, B, C), for Barycentric Coordinates
		//For the purpose of Barycentric Coordinates, we don't normalize the plane normal.
		

		//Inside-Outside
		//Test if the dot of the edge vector and vertex vector is > 0, if it is, then rt is inside the triangle
		Eigen::Vector3d c;


		//Take AxB, A = edge, B = rt - v (vector from head of rt to v)
		//Edge 0
		Eigen::Vector3d e0 = v1 - v0; //Get A
		Eigen::Vector3d C0 = rt - v0; //Get C, since C points from rt toward v0, we must get its cross product with e0 so that it points inside the triangle
		c = e0.cross(C0); //We call it C', which is the vector pointing at the same direction as the Z-axis and Plane Normal
		if (PlaneNormal.dot(c) < 0) //N dot C' should return > 0 because they should point inside the triangle, if negative, C' is pointing outside the triangle
		{
			return result;
		}

		//Do the above test for the other two edges

		//Edge 1;
		Eigen::Vector3d e1 = v2 - v1;
		Eigen::Vector3d C1 = rt - v1;

		c = e1.cross(C1);
		if (PlaneNormal.dot(c) < 0)
		{
			return result;
		}

		//Edge 2
		Eigen::Vector3d e2 = v0 - v2;
		Eigen::Vector3d C2 = rt - v2;
		c = e2.cross(C2);
		if (PlaneNormal.dot(c) < 0)
		{
			return result;
		}


		//Get u, v and w
		u /= denom;
		v /= denom;
		w = 1 - u - v;

		result.t = t;
		result.position = rt;
		result.normal = PlaneNormal;
		result.mirror = mirror;
		result.color = Objectcolor;


		return result;
	}

}
