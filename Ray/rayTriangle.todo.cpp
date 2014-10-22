#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

const float EP = 0.000001;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
void RayTriangle::initialize(void){
  v1 = v[1]->position - v[0]->position;
  v2 = v[2]->position - v[0]->position;
  
  plane.normal = v1.crossProduct(v2).unit();

  float d = plane.normal.dot(v1);// * -1.0f);
  float t = d / plane.normal.dot(plane.normal);

  Point3D PoP = plane.normal * t;
  plane.distance = sqrt(PoP.dot(PoP));
}

double RayTriangle::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){

  float t = -1.0f * (ray.position.dot(plane.normal) + plane.distance) / (ray.direction.dot(plane.normal));
  // get a point on ray that sits on the plane spanned by the triangle
  Point3D P = ray(t);
  
  Point3D solution = P - v[0]->position;
  Point3D matrix[3] = {Point3D(v1.p[0], v2.p[0], solution[0]), 
		       Point3D(v1.p[1], v2.p[1], solution[1]), 
		       Point3D(v1.p[2], v2.p[2], solution[2])};

  float alpha = -1;
  float beta = -1;

  float EPS = 0.00001f;
  // at most one zero row for the plane to span R2
  // row 0 is 0
  if((matrix[0].p[0] - EPS) <= 0 && (matrix[0].p[1] - EPS) <= 0 && (matrix[0].p[2] - EPS) <= 0){
    float z = matrix[2].p[0] / matrix[1].p[0];
    Point3D diff = (matrix[1] * z);    
    Point3D p1 = (matrix[2] - diff);
    beta = p1.p[2] / p1.p[1];
    alpha = (matrix[1].p[2] - (matrix[1].p[1] * beta)) / matrix[1].p[0];
  }
  // row 1 is 0
  else if((matrix[1].p[0] - EPS) <= 0 && (matrix[1].p[1] - EPS) <= 0 && (matrix[1].p[2] - EPS) <= 0){
    float z = matrix[2].p[0] / matrix[0].p[0];
    Point3D diff = (matrix[0] * z);
    Point3D p1 = matrix[2] - diff;
    beta = p1.p[2] / p1.p[1];
    alpha = (matrix[0].p[2] - (matrix[0].p[1] * beta)) / matrix[0].p[0];
  }
  // row 2 is 0
  else{
    float z = matrix[1].p[0] / matrix[0].p[0];
    Point3D diff = (matrix[0] * z);
    Point3D p1 = matrix[1] - diff;
    beta = p1.p[2] / p1.p[1];
    alpha = (matrix[0].p[2] - (matrix[0].p[1] * beta)) / matrix[0].p[0];
  }
  if(alpha >= 0 && beta >= 0 && alpha + beta <= 1){
    Point3D coord = ray(t);
    
    if(mx < 0 || t < mx){
      iInfo.material = material;
      iInfo.iCoordinate = coord + (plane.normal * EP);
      iInfo.normal = plane.normal;
    }

    return t;
  }
  else{
    return -1;
  }
  return -1;
}
BoundingBox3D RayTriangle::setBoundingBox(void){
  return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
