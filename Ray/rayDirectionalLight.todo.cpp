#include <math.h>
#include <GL/glut.h>
#include "rayDirectionalLight.h"
#include "rayScene.h"

const float EP  = 1e-4;

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
  Point3D L = direction.negate().unit();
  float NdL = iInfo.normal.unit().dot(L);
  if (NdL < 0){
    return Point3D(0,0,0);
  }

  Point3D V = (cameraPosition - iInfo.iCoordinate).unit();  
  Point3D R = iInfo.normal.unit() * (L.dot(iInfo.normal.unit()) * 2) - L;  
  float alpha = V.dot(R);
  if (alpha < 0){
    return Point3D(0,0,0);
  }
  
  return  iInfo.material->specular * pow(alpha, iInfo.material->specularFallOff) * color;
}
int RayDirectionalLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
  Point3D L = (Point3D(0,0,0) - direction).unit();
  Ray3D ray = Ray3D((iInfo.iCoordinate + L * EP), L);
  RayIntersectionInfo info = RayIntersectionInfo();  

  float inter = shape->intersect(ray, info, -1.0f);
  if(inter > 0 && inter > EP){
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
