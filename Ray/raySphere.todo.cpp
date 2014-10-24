#include <math.h>
// #include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

const float EP = 1e-4;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RaySphere::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){
  
  // ray from position to sphere center  
  Point3D L = center - ray.position;
  float LdL = sqrt(L.dot(L));

  float t_ca = L.dot(ray.direction); 

  float dSq = pow(LdL, 2) - pow(t_ca, 2);
  float rSq = pow(radius, 2);

  if (dSq > rSq){
    return -1;
  }
  else{
    float t_hc = sqrt(rSq - dSq);    
    float dist = t_ca - t_hc;
    if(mx < 0 || dist < mx){

      Point3D coord = ray(dist);

      iInfo.material = material;
      iInfo.normal = (coord - center).unit();        
      iInfo.iCoordinate = coord;
    }
    return dist;
  }
}
BoundingBox3D RaySphere::setBoundingBox(void){
  Point3D p1 = Point3D(center[0] - radius, center[1] - radius, center[2] - radius);
  Point3D p2 = Point3D(center[0] + radius, center[1] + radius, center[2] + radius);
  return bBox = BoundingBox3D(p1, p2);
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	return -1;
}

