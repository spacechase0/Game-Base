#include "SceneChangeEvent.hpp"

SceneChangeEvent::SceneChangeEvent()
   : reason( Unspecified )
{
}

SceneChangeEvent::SceneChangeEvent( Reason theReason )
   : reason( theReason )
{
}
