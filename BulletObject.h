#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

class BulletObject: public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BulletType
    {
         FIRE_BULLET=0,
        SPHERE_BULLET =1
    };
    enum BulletDir
    {
        DIR_RIGHT =3,
        DIR_LEFT =4,
    };

    void set_x_val(const int& xVal) {x_val_=xVal;}
    void set_y_val(const int& yVal) {y_val_=yVal;}
    int get_x_val()const{return x_val_;}
    int get_y_val()const {return y_val_; }
     void set_is_move(const bool& isMove){is_move_= isMove;}
     bool get_is_move() const {return is_move_;}

     void set_bullet_dir(const unsigned int& bulletdir ){bullet_dir_=bulletdir;}
     unsigned int get_bullet_dir()const{return bullet_dir_;}

     void set_bullet_type(const unsigned int& bulletType){bullet_type_=bulletType;}
     unsigned int get_bullet_type()const{return bullet_type_;}
     void HandleMove(const int& x_border,const int& y_border);
     bool LoadImgBullet(SDL_Renderer* des);


private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir_;
    unsigned int bullet_type_;
};







#endif // BULLET_OBJECT_H_
