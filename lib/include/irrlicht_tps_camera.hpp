//
// irrlicht_tps_camera.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Mon Jun 12 22:47:07 2017 jurczy_l
// Last update Sat Jun 17 17:47:56 2017 augustin marmus
//

#include "irrlicht.h"
# define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cassert>

#ifndef			IRRLICHT_TPS_CAMERA_HPP
# define		IRRLICHT_TPS_CAMERA_HPP

using namespace irr;

const static f32 MAX_PITCH=88.0f;

inline f64 toRadian(f64 deglee)
{
  return M_PI * deglee / 180.0;
}

inline f64 toDeglee(f64 radian)
{
  return 180.0 * radian / M_PI;
}

enum ID_PICK_TYPE
{
  ID_IsNotPickable = 0,
  IDFlag_IsPickable = 1 << 0,
  IDFlag_IsHighlightable = 1 << 1
};

namespace irr {
  class TPSController : public IReferenceCounted
  {
    scene::ISceneNode *person_;
    core::vector3df centerOffset_;
    scene::IAnimatedMeshSceneNode *animation_;
    f32 velocity_;
    core::vector3df move_;
    f32 personHead_;
    f32 personRotationSpeed_;
    f32 baseAngle_;
    f32 joystickMoveSpeed_;

    enum STATUS
      {
	STATUS_STOP,
	STATUS_WALK,
	STATUS_JUMP,
	STATUS_FALL,
	STATUS_DASH,
      };
    
    STATUS currentStatus_;
    STATUS lastStatus_;

    f32 jumpMove_;
    f32 jumpPower_;
    f32 jumpGravity_;
    f32 lastPersonY_;

    scene::ICameraSceneNode *camera_;
    f32 head_;
    f32 pitch_;
    f32 distance_;
    f32 mouseRotatinSpeed_;

    s16 joystickDeadzone_;
    f32 joystickRotationSpeed_;

  public:
    TPSController()
      : person_(0), animation_(0), velocity_(0.1f), baseAngle_(0),
      personHead_(0), personRotationSpeed_(8.0f), joystickMoveSpeed_(0.5f),
      currentStatus_(STATUS_STOP), lastStatus_(STATUS_STOP),
      jumpMove_(0), jumpPower_(10.0f), jumpGravity_(-0.4f), lastPersonY_(0),
      camera_(0), head_(0), pitch_(-30.0f), distance_(10.0f), 
      mouseRotatinSpeed_(0.5f), joystickDeadzone_(3200), 
      joystickRotationSpeed_(2.0f)
      {
        //grab();
      }

    ~TPSController()
    {
      if(person_)
        person_->drop();
      if(animation_)
        animation_->drop();
      if(camera_)
        camera_->drop();
    }

    void setPerson(scene::ISceneNode *node, const core::vector3df &offset){ 
      person_=node; 
      person_->grab();
      centerOffset_=offset;
    }
    void setAnimationNode(scene::IAnimatedMeshSceneNode *animation)
    {
      animation_=animation;
      animation_->grab();
    }
    void setCamera(scene::ICameraSceneNode *camera){ 
      camera_=camera; 
      camera_->setFarValue(500000.0f);

      camera_->grab();

    }
    void setVelocity(f32 velocity)
    {
      velocity_=velocity;
    }
    void setDistance(f32 distance)
    {
      distance_=distance;
    }
    // キャラクタがこちら向きになる角度
    void setBaseAngle(f32 angle)
    {
      baseAngle_=angle;
    }

    void jump()
    {
      if(currentStatus_==STATUS_JUMP){
        return;
      }
      if(currentStatus_==STATUS_FALL){
        return;
      }
      currentStatus_=STATUS_JUMP;
      jumpMove_=jumpPower_;
    }

    void move(f32 xMove, f32 zMove)
    {
      if(!person_){
        return;
      }
      if(!camera_){
        return;
      }
      if(xMove==0 && zMove==0){
        if(currentStatus_!=STATUS_JUMP && currentStatus_!=STATUS_FALL){
          currentStatus_=STATUS_STOP;
        }
        return;
      }
      if(currentStatus_!=STATUS_JUMP && currentStatus_!=STATUS_FALL){
        currentStatus_=STATUS_WALK;
      }

      core::vector3df cameraPosition=camera_->getPosition();
      core::vector3df cameraTarget=camera_->getTarget();

      // カメラの向きに垂直な左方向を計算する
      core::vector3df zAxis=cameraTarget-cameraPosition;
      zAxis.Y=0;
      zAxis.normalize();
      core::vector3df xAxis=core::vector3df(0, 1, 0).crossProduct(zAxis);

      // 移動ベクトル
      move_=zAxis*zMove+xAxis*xMove;
      //move_.normalize();

      // 向き
      f32 angle=static_cast<f32>(toDeglee(atan2(move_.X, move_.Z)));
      f32 rotation=angle-personHead_;
      if(rotation!=0){
        while(rotation<-180.0f){
          rotation+=360.0f;
        }
        while(rotation>180.0f){
          rotation-=360.0f;
        }
        if(rotation>0){
          if(rotation<=personRotationSpeed_){
            personHead_=angle;
          }
          else{
            personHead_+=personRotationSpeed_;
          }
        }
        else if(rotation<0){
          if(rotation>=-personRotationSpeed_){
            personHead_=angle;
          }
          else{
            personHead_-=personRotationSpeed_;
          }
        }
      }
    }

    // 視点の回転(マウス)
    void rotateMouse(s32 head, s32 pitch)
    {
      rotate(head*mouseRotatinSpeed_, pitch*mouseRotatinSpeed_);
    }

    // 視点の回転
    void rotate(f32 head, f32 pitch)
    {
      if(!person_){
        return;
      }
      if(!camera_){
        return;
      }

      head_+=head;
      while(head_<-180.0f){
        head_+=360.0f;
      }
      while(head_>180.0f){
        head_-=360.0f;
      }
      pitch_+=pitch;
      if(pitch_<-MAX_PITCH){
        pitch_=-MAX_PITCH;
      }
      else if(pitch_>MAX_PITCH){
        pitch_=MAX_PITCH;
      }
    }

    void setPosition(f32 x, f32 z)
    {
      core::vector3df pos = person_->getPosition();
      pos.X += x;
      pos.Z += z;
      person_->setPosition(pos);
    }
    
    // 移動を反映する
    void update(u32 milisec)
    {
      if(!person_){
        return;
      }
      core::vector3df personPosition=person_->getPosition();
      // person jump
      if(currentStatus_==STATUS_JUMP){
        jumpMove_+=jumpGravity_;
        if(jumpMove_<0){
          currentStatus_=STATUS_FALL;
        }
      }
      else if(currentStatus_==STATUS_FALL){
        jumpMove_+=jumpGravity_;
        // 接地判定?
        if(personPosition.Y>=lastPersonY_){
          jumpMove_=0;
          currentStatus_=STATUS_STOP;
        }
        lastPersonY_=personPosition.Y;
      }
      // person move
      person_->setPosition(personPosition+
          core::vector3df(0, jumpMove_, 0)+
          move_*static_cast<f32>(milisec)*velocity_);
      move_=core::vector3df(0, 0, 0);
      // person rotation
      person_->setRotation(
          core::vector3df(0, personHead_+baseAngle_, 0));

      if(!animation_){
        return;
      }
      if(currentStatus_==lastStatus_){
        return;
      }
      switch(currentStatus_)
      {
      case STATUS_STOP:
        animation_->setMD2Animation(scene::EMAT_STAND);
        break;

      case STATUS_WALK:
        animation_->setMD2Animation(scene::EMAT_RUN);
        break;
      }
      lastStatus_=currentStatus_;
    }

    void updateCamera()
    {
      if(!camera_){
        return;
      }

      f32 ch=static_cast<f32>(cos(toRadian(head_)));
      f32 sh=static_cast<f32>(sin(toRadian(head_)));
      f32 cp=static_cast<f32>(cos(toRadian(pitch_)));
      f32 sp=static_cast<f32>(sin(toRadian(pitch_)));
      core::vector3df cameraDirection(-sh*cp, -sp, -ch*cp);
      core::vector3df target=person_->getPosition()+centerOffset_;
      camera_->setPosition(target+cameraDirection*distance_);
      camera_->setTarget(target);
    }

    scene::ICameraSceneNode *getCamera()
    {return camera_;}
  };








  
  class MyEventReceiver : public IEventReceiver
  {
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    SEvent::SJoystickEvent JoystickState;

  public:
    MyEventReceiver()
    {
      for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i){
        KeyIsDown[i] = false;
      }
    }

    virtual bool OnEvent(const SEvent& event)
    {
      if (event.EventType == EET_KEY_INPUT_EVENT){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
      }
      if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT
          && event.JoystickEvent.Joystick == 0) {
        JoystickState = event.JoystickEvent;
      }

      return false;
    }

    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
      return KeyIsDown[keyCode];
    }

    s16 getJoystickAxis(u32 joystick, u32 axis)const
    {
      if(joystick!=0){
        return 0;
      }
      return JoystickState.Axis[axis];
    }

    bool IsButtonPressed(u32 joystick, u32 button)const
    {
      if(joystick!=0){
        return false;
      }
      return JoystickState.IsButtonPressed(button);
    }
  };









  namespace scene {
    class TPSAnimator : public ISceneNodeAnimator
    {
      TPSController *controller_;
      u32 lastMS;
    public:
      TPSAnimator(TPSController *controller)
        : lastMS(0), controller_(controller)
      {}

      //! Destructor
      virtual ~TPSAnimator() {}

      //! Animates a scene node.
      virtual void animateNode(ISceneNode* node, u32 timeMs){
        u32 interval=timeMs-lastMS;
        lastMS=timeMs;
        controller_->update(interval);
      }

      //! Creates a clone of this animator.
      virtual ISceneNodeAnimator* createClone(
          ISceneNode* node, ISceneManager* newManager=0){
        return 0;
      }

      //! Returns true if this animator receives events.
      virtual bool isEventReceiverEnabled() const
      {
        return false;
      }

      //! Event receiver,
      //! override this function for camera controlling animators
      virtual bool OnEvent(const SEvent& event)
      {
        return true;
      }

      //! Returns type of the scene node animator
      virtual ESCENE_NODE_ANIMATOR_TYPE getType() const
      {
        return ESNAT_UNKNOWN;
      }
    };
    
  }
  
}

#endif			/* !IRRLICHT_TPS_CAMERA_HPP */
