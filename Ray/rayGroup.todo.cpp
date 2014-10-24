#include <stdlib.h>
#include <GL/glut.h>
#include "rayGroup.h"

#include <limits>

////////////////////////
//  Ray-tracing stuff //
////////////////////////
double RayGroup::intersect(Ray3D ray,RayIntersectionInfo& iInfo,double mx){    
  // transform ray into modelling coordinates
  Matrix4D M = getMatrix();
  Matrix4D Mp = getInverseMatrix();
  Ray3D t_ray = Mp * ray;
  t_ray.direction = t_ray.direction.unit();

  for(int i = 0; i < sNum; i++){    
    RayShape* s = shapes[i];    
    // distance along transformed ray
    float t_hit = s->intersect(t_ray, iInfo, mx);    
    if(t_hit < 0){
      continue;
    }     
    Point3D t_coord = t_ray(t_hit);//iInfo.iCoordinate;
    Point3D r_coord = M * t_coord;
    float dist = (r_coord - ray.position).length();
    // if minD is negative or 
    // there is a hit, and the hit is closer than mind
    if ((mx < 0 && dist > 0) || (dist > 0 && dist < mx)){    
      mx = dist;
      // fix iInfo
      iInfo.iCoordinate = r_coord;
      // convert the normal
      iInfo.normal = getNormalMatrix() * iInfo.normal;
    } 
  }
  return mx;
}

BoundingBox3D RayGroup::setBoundingBox(void){
  Point3D plist[sNum * 2];
  for(int i = 0; i < sNum; i = i + 2){
    int idx = i / 2;
    plist[i] = shapes[idx]->bBox.p[0];
    plist[i + 1] = shapes[idx]->bBox.p[1];
  }
  return bBox = BoundingBox3D(plist, sNum * 2);
}

int StaticRayGroup::set(void){  
  inverseTransform = localTransform.invert();
  normalTransform = Matrix4D();
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      normalTransform.m[i][j] = localTransform(i, j);
    }
  }
  normalTransform = normalTransform.transpose().invert();
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
