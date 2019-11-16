#ifndef SHAPE_H
#define SHAPE_H

#include <Eigen/Dense>

namespace Raytracer148 {
struct Ray {
  Eigen::Vector3d origin, direction;
  int depth = 0;;
};

class Shape;

struct HitRecord {
  Eigen::Vector3d position, normal;
  double t;
  Eigen::Vector3d color; //Color vector
  bool mirror = false; //Determines if the surface reflects
  
};

class Shape {
public:
  virtual ~Shape(){}
  virtual HitRecord intersect(const Ray &ray) = 0;


};

}

#endif
