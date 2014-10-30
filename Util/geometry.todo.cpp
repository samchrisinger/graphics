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

  float w = x_2 - x_1;
  float h = y_2 - y_1;
  float d = z_2 - z_1;

  float bounds[3][2] = {{x_1, x_2}, {y_1, y_2}, {z_1, z_2}};
  int dims[3][2] = {{0,1}, {0,2}, {1,2}};
  float acc[3];
  for(int i = 0; i < 3; i++){
    int d1 = dims[i][0];
    int d2 = dims[i][1];
    Point2D Odim = Point2D(ray.position.p[d1], ray.position.p[d2]);
    Point2D Ddim = Point2D(ray.direction.p[d1], ray.direction.p[d2]);

    float d1L = bounds[d1][0];
    float d1U = bounds[d1][1];
    float d2L = bounds[d2][0];
    float d2U = bounds[d2][1];
    // check for parallel
    if (Ddim[1] == 0){
      // parallel and outside
      if(Odim[1] > d2U || Odim[1] < d2L){
	return -1;
      }
      // origin inside box
      else if(Odim[0] < d1U && Odim[0] > d1L){
	return 0;
      }
      else{
	acc[d1] = Odim[0];
	continue;
      }
    }
    else if (Ddim[0] == 0){
      // parallel and outside
      if(Odim[0] > d1U || Odim[0] < d1L){
	return -1;
      }
      // origin inside box
      else if(Odim[1] < d2U && Odim[1] > d2L){
	return 0;
      }
      else{
	// TODO
	acc[d2] = Odim[1];
	continue;
      }
    }
    
    // calcuate distance to intersection (t) 
    float d1_t1 = (d1L - Odim[0]) / Ddim[0];
    float d1_t2 = (d1U - Odim[0]) / Ddim[0];
    // find points of intersection
    Point2D d1_i1 = Point2D(d1L, Odim[1] + d1_t1 * Ddim[1]);
    Point2D d1_i2 = Point2D(d1U, Odim[1] + d1_t2 * Ddim[1]);

    // line misses box
    if(d1_i1[1] < d2L && d1_i2[1] < d2L) {
      return -1;
    }
    else if(d1_i1[1] > d2U && d1_i2[1] > d2U) {
      return -1;
    }
    else{
      // guarenteed a hit
      float d2_t1 = (d2L - Odim[1]) / Ddim[1];
      float d2_t2 = (d2U - Odim[1]) / Ddim[1];
      
      Point2D d2_i1 = Point2D(Odim[0] + d2_t1 * Ddim[0], d2L);
      Point2D d2_i2 = Point2D(Odim[0] + d2_t2 * Ddim[0], d2U);

      acc[d1] = fmin(d1_i1[0], fmin(d1_i2[0], fmin(d2_i1[0], d2_i2[0])));
    }
  }
  return (Point3D(acc[0], acc[1], acc[2]) - ray.position).length();
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
