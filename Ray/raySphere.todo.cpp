#include <math.h>
// #include <GL/glut.h>
#include "rayScene.h"
#include "raySphere.h"

inline float eud(Point3D p2, Point3D p1){
  return sqrt(pow(p2[0] - p1[0], 2) + 
	      pow(p2[1] - p1[1], 2) + 
	      pow(p2[2] - p1[2], 2));
}

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
      iInfo.iCoordinate = coord;
      iInfo.normal = (coord - center).unit();        
    }

    return dist;      
  }
}
BoundingBox3D RaySphere::setBoundingBox(void){
	return bBox;
}

//////////////////
// OpenGL stuff //
//////////////////
int RaySphere::drawOpenGL(int materialIndex){
	return -1;
}
