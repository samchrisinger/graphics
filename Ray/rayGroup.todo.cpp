#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

#include <limits>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){  
  float minD = -1;
  for(int i = 0; i < sNum; i++){    
    RayShape* s = shapes[i];    
    float hit = s->intersect(ray, iInfo, mx);
    // if minD is negative or 
    // there is a hit, and the hit is closer than mind
    if ((minD < 0 && hit > 0) || (hit > 0 && hit < minD)){
      mx = hit;
      minD = hit;
    }
  }
  return minD;
}

BoundingBox3D RayGroup::setBoundingBox(void){
  return bBox;
}

int StaticRayGroup::set(void){
	return 1;
}
//////////////////
// OpenGL stuff //
//////////////////
int RayGroup::getOpenGLCallList(void){
	return 0;
}

int RayGroup::drawOpenGL(int materialIndex){
	return -1;
}

/////////////////////
// Animation Stuff //
/////////////////////
Matrix4D ParametrizedEulerAnglesAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedClosestRotationAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedRotationLogarithmAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
Matrix4D ParametrizedQuaternionAndTranslation::getMatrix(void){
	return Matrix4D::IdentityMatrix();
}
