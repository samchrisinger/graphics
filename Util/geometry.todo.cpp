#include <stdlib.h>
#include <math.h>

#include <SVD/SVDFit.h>
#include <SVD/MatrixMNTC.h>

#include "geometry.h"

///////////////////////
// Ray-tracing stuff //
///////////////////////
double BoundingBox3D::intersect(const Ray3D& ray) const {
  float x_1 = p[0].p[0]; 
  float x_2 = p[1].p[0];
      
  float y_1 = p[0].p[1];
  float y_2 = p[1].p[1];

  float z_1 = p[0].p[2];
  float z_2 = p[1].p[2];

  float bounds[3][2] = {{x_1, x_2}, {y_1, y_2}, {z_1, z_2}};
  int dims[3][2] = {{0,1}, {2,0}, {2, 1}};

  float tNear = -1e10;
  float tFar = 1e10;
  
  for(int i = 0; i < 3; i++){
    int d1 = dims[i][0];
    int d2 = dims[i][1];
    Point2D Odim = Point2D(ray.position.p[d1], ray.position.p[d2]);
    Point2D Ddim = Point2D(ray.direction.p[d1], ray.direction.p[d2]);
	
    float d1L = bounds[d1][0];
    float d1U = bounds[d1][1];       
    float d2L = bounds[d2][0];
    float d2U = bounds[d2][1];

    if(Ddim[d1] == 0){
      if(Odim[d1] < d1L || Odim[d1] > d1U){
	return -1;
      }
    }
    float t1 = (d1L - Odim[0]) / Ddim[0];
    float t2 = (d1U - Odim[0]) / Ddim[0];
    if(t1 > t2) {
      float swp = t1;
      t1 = t2;
      t2 = swp;
    }
    if (t1 > tNear){
      tNear = t1;
    }
    if (t2 < tFar){
      tFar = t2;
    }
    if (tNear > tFar){
      return -1;
    }
    if(tFar < 0){
      return -1;
    }
  }
  return tNear;
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
