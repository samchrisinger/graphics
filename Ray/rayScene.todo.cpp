#include "rayScene.h"
#include <GL/glut.h>
#include <math.h>

const float EP = 1e-4;

///////////////////////
// Ray-tracing stuff //
///////////////////////

Point3D RayScene::Reflect(Point3D v,Point3D n){
  Point3D L = v.negate().unit();  
  Point3D R = n.unit() * (L.dot(n.unit()) * 2) - L;  
  return R.unit();
}

int RayScene::Refract(Point3D v,Point3D n,double ir,Point3D& refract){
	return 0;
}

Ray3D RayScene::GetRay(RayCamera* camera,int i,int j,int width,int height){  
  float id = ((float) i + 0.5f) - ((float) width / 2.0f);
  float iRat = id / (float) width;
  float jd = (((float) height / 2.0f) - ((float) j + 0.5f));
  float jRat = -1.0f * jd / (float) height;

  float realHeight = (2.0f * tan((float) camera->heightAngle / 2.0f));
  float realWidth = (camera->aspectRatio * realHeight);

  Point3D c1 = camera->direction.unit();
  Point3D c2 = camera->right.unit() * (iRat * realWidth);
  Point3D c3 = camera->up.unit() * (jRat * realHeight);

  Point3D direction = (c1 + c2 + c3).unit();

  return Ray3D(camera->position, direction);
}

Point3D RayScene::GetColor(Ray3D ray,int rDepth,Point3D cLimit){
  if (rDepth == 0){// || (cLimit[0] < EP || cLimit[1] < EP || cLimit[2] < EP)){
    return Point3D(0,0,0);
  }

  RayIntersectionInfo info = RayIntersectionInfo();
  
  float intersection = group->intersect(ray, info, -1.0f); 
  if (intersection > 0){
    Point3D ret = info.material->emissive + info.material->ambient.mult(ambient); 
    int iSectCount = 0;
    for (int i = 0; i < lightNum; i++){      
      RayLight* l = lights[i];
      if(!l->isInShadow(info, group, iSectCount)){
	Point3D d = l->getDiffuse(camera->position, info);
	Point3D s = l->getSpecular(camera->position, info);      
	ret += d + s;
      }
      Point3D K_s = info.material->specular;
      Ray3D refl = Ray3D(info.iCoordinate + info.normal * EP, Reflect(ray.direction, info.normal));
      ret += K_s * GetColor(refl, rDepth - 1, cLimit);
    }    
    return ret;
  }
  else{
    return background;
  }
}

//////////////////
// OpenGL stuff //
//////////////////
void RayMaterial::drawOpenGL(void){
}
void RayTexture::setUpOpenGL(void){
}
