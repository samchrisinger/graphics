#include <math.h>
#include <GL/glut.h>
#include "rayScene.h"
#include "raySpotLight.h"


////////////////////////
//  Ray-tracing stuff //
////////////////////////
Point3D RaySpotLight::getDiffuse(Point3D cameraPosition,RayIntersectionInfo& iInfo){
  Point3D diff = (iInfo.iCoordinate - direction);
  
  float DdL = direction.dot(diff.unit());
  if(DdL < cos(cutOffAngle)){
    return Point3D();
  } 
  else{
    float d = diff.length();
    float numer = pow(DdL, dropOffRate);
    float denom = (constAtten + linearAtten * d + quadAtten * pow(d, 2));
    Point3D I_l = color * (numer / denom);
    
    return iInfo.material->diffuse.mult(I_l);
  }
}
Point3D RaySpotLight::getSpecular(Point3D cameraPosition,RayIntersectionInfo& iInfo){
	return Point3D();
}
int RaySpotLight::isInShadow(RayIntersectionInfo& iInfo,RayShape* shape,int& isectCount){
	return 0;
}
Point3D RaySpotLight::transparency(RayIntersectionInfo& iInfo,RayShape* shape,Point3D cLimit){
	return Point3D(1,1,1);
}

//////////////////
// OpenGL stuff //
//////////////////
void RaySpotLight::drawOpenGL(int index){
}
