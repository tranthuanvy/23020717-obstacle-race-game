#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_=0;
    y_val_=0;
    is_move_=false;
    bullet_type_=FIRE_BULLET;

}
BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret=false;
    if(bullet_type_==SPHERE_BULLET)
    {

       ret= LoadImg("Pics/spherebullet.PNG ",des);

    }
    else
    {
        ret=LoadImg("Pics/fire.png",des);

    }
   return ret;

}
void BulletObject:: HandleMove(const int& x_border, const int& y_border)
{


   if(bullet_dir_==DIR_RIGHT)
   {
    rect_.x+= x_val_;
    if(rect_.x > x_border)
    {
        is_move_=false;
    }
   }
   else if(bullet_dir_==DIR_LEFT)
   {
       rect_.x-=x_val_;
       if(rect_.x<0)
       {
           is_move_=false;
       }
   }

}
