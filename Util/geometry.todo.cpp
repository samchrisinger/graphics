#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"


///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {
  float w = p[1][0] - p[0][1];
  float h = p[1][1] - p[0][1];
  float d = p[1][2] - p[0][2];

  float d_1 = (ray.position - p[0]).length();
  float d_2 = (ray.position - p[1]).length();

  Point3D e1, e2, e3;
  if(d_1 < d_2) {
    e_1 = (p[0] + Point3D(w,0,0)) - p[0];
    e_2 = (p[0] + Point3D(0,h,0)) - p[0];
    e_3 = (p[0] + Point3D(0,0,d)) - p[0];
  }
  else {    
    e_1 = (p[1] - Point3D(w,0,0)) - p[1];
    e_2 = (p[1] - Point3D(0,h,0)) - p[1];
    e_3 = (p[1] - Point3D(0,0,d)) - p[1];
  }

  Point3D n = e_1.crossProduct(e_2).unit();
  float d = n.dot(e_1);
  float t = d / n.dot(n);
  Point3D PoP = n * t;
  float dist = sqrt(PoP.dot(PoP));
  
  float t = -1.0f * (ray.position.dot(n) + dist) / (ray.direction.dot(plane.n));
  Point3D q = ray(t);
  
  return -1;
}

/////////////////////
// Animation stuff //
/////////////////////
Matrix3D::Matrix3D(const Point3D& e){
	(*this)=Matrix3D();
}

Matrix3D::Matrix3D(const Quaternion& q){
	(*this)=Matrix3D();
}
Matrix3D Matrix3D::closestRotation(void) const {
	return (*this);
}
/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/
Matrix3D Matrix3D::Exp(const Matrix3D& m,int iter){
	return m;
}
