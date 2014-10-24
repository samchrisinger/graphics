#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rayTriangle.h"

const float EP = 1e-4;

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
  Point3D q = ray(t);

  Point3D e_1 = q - v[0]->position;
  Point3D e_2 = q - v[1]->position;
  Point3D e_3 = q - v[2]->position;
  Point3D s_1 = v[2]->position - v[0]->position;
  Point3D s_2 = v[0]->position - v[1]->position;
  Point3D s_3 = v[1]->position - v[2]->position;
  
  float A1 = s_1.crossProduct(e_1).dot(plane.normal);
  float A2 = s_2.crossProduct(e_2).dot(plane.normal);
  float A3 = s_3.crossProduct(e_3).dot(plane.normal);
  float area = A1 + A2 + A3;

  float alpha = A1 / area;
  float beta = A2 / area;
  float gamma = A3 / area;
  
  if((alpha >= 0 && beta >= 0 && gamma >= 0) &&
     (abs(1.0f - (alpha + beta + gamma)) < EP)){
    if(mx < 0 || t < mx){
      iInfo.iCoordinate = ray(t);
      iInfo.material = material;
      iInfo.normal = plane.normal;
    }
    return t;
  }
  return -1;
}
BoundingBox3D RayTriangle::setBoundingBox(void){
  Point3D p1, p2;
  for(int i = 0; i < 3; i++){
    p1[0] = fmin(p1[0], v[i]->position[0]);
    p1[1] = fmin(p1[1], v[i]->position[1]);
    p1[1] = fmin(p1[2], v[i]->position[2]);
    p2[0] = fmax(p2[0], v[i]->position[0]);
    p2[1] = fmax(p2[1], v[i]->position[1]);
    p2[2] = fmax(p2[2], v[i]->position[2]);
  }
  return bBox = BoundingBox3D(p1, p2);
}

//////////////////
// OpenGL stuff //
//////////////////
int RayTriangle::drawOpenGL(int materialIndex){
	return -1;
}
