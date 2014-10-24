#include <math.h>
#include <GL/glut.h>
#include "rayPointLight.h"
#include "rayScene.h"

const float EP = 1e-4;

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayPointLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
  
  float d = (location - iInfo.iCoordinate).length();
  float denom = (constAtten + linearAtten * d + quadAtten * pow(d, 2));
  
  return color * (1.0f / denom);
}
Point3D RayPointLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	return Point3D();
}
int RayPointLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
  Point3D L = (location  - iInfo.iCoordinate).unit();
  Ray3D ray = Ray3D((iInfo.iCoordinate + L * EP), L);
  RayIntersectionInfo info = RayIntersectionInfo();  

  float inter = shape->intersect(ray, info, -1.0f);
  if(inter > 0 && inter > EP){
    return 1;
  }
  return 0;
}
Point3D RayPointLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}


//////////////////
// OpenGL stuff //
//////////////////
void RayPointLight::drawOpenGL(int index){
}
