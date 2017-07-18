#ifndef		TPSANIMATOR_HPP_
# define	TPSANIMATOR_HPP_

#include	"irrlicht.h"
#include	<math.h>
#include	<iostream>
#include	<cassert>

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

  namespace scene {
    class TPSController;
    class TPSAnimator : public ISceneNodeAnimator
    {
      TPSController *controller_;
      u32 lastMS;
    public:
      TPSAnimator(TPSController *controller)
        : lastMS(0), controller_(controller)
      {}

      virtual ~TPSAnimator() {}
      virtual void animateNode(ISceneNode* node, u32 timeMs){
        u32 interval=timeMs-lastMS;
        lastMS=timeMs;
        controller_->update(interval);
      }
      virtual ISceneNodeAnimator* createClone(
          ISceneNode* node, ISceneManager* newManager=0){
        return 0;
      }
      virtual bool isEventReceiverEnabled() const
      {
        return false;
      }
      virtual bool OnEvent(const SEvent& event)
      {
        return true;
      }
      virtual ESCENE_NODE_ANIMATOR_TYPE getType() const
      {
        return ESNAT_UNKNOWN;
      }
    };
    
  }
  
}

#endif
