#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

#include <limits>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){    
  // transform ray into modelling coordinates
  Matrix4D inverse = this->getInverseMatrix();
  Ray3D t_ray = inverse * ray;

  for(int i = 0; i < sNum; i++){    
    RayShape* s = shapes[i];    
    // distance along transformed ray of h
    float t_hit = s->intersect(t_ray, iInfo, mx);
    if (t_hit < 0){
      continue;
    }
    
    Matrix4D trans = this->getMatrix();
    Point3D r_cood = trans * iInfo.iCoordinate;
    Point3D d = (r_cood - ray.position);
    float dist = d.length();
    // if minD is negative or 
    // there is a hit, and the hit is closer than mind
    if ((mx < 0 && dist > 0) || (dist > 0 && dist < mx)){    
      mx = dist;
      // fix iInfo
      iInfo.iCoordinate = r_cood;
      // convert the normal
      iInfo.normal = this->getNormalMatrix() * iInfo.normal;
    } 
  }
  return mx;
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
