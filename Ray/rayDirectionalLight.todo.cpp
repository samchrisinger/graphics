#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RayDirectionalLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
  Point3D L = (Point3D(0,0,0) - direction).unit();

  float NdL = iInfo.normal.dot(L);
  if (NdL < 0){
    return Point3D(0,0,0);
  }
  Point3D I_l = color * NdL;
  return iInfo.material->diffuse.mult(I_l);

}
Point3D RayDirectionalLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
  Point3D L = (Point3D(0,0,0) - direction).unit();
  float NdL = iInfo.normal.dot(L);
  if (NdL < 0){
    return Point3D(0,0,0);
  }

  Point3D V = (cameraPosition - iInfo.iCoordinate).unit();  
  Point3D R = iInfo.normal * (L.dot(iInfo.normal) * 2) - L;  
  float alpha = V.dot(R);
  
  return  iInfo.material->specular * pow(alpha, iInfo.material->specularFallOff) * color;
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
  Point3D L = (Point3D(0,0,0) - direction).unit();
  Ray3D ray = Ray3D(iInfo.iCoordinate, L);
  RayIntersectionInfo info = RayIntersectionInfo();  

  if(shape->intersect(ray, info, -1.0f) > 0){
    return 1;
  }
  return 0;
}
Point3D RayDirectionalLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RayDirectionalLight::drawOpenGL(int index){
}
