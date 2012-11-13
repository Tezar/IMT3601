#include <irrlicht.h>
#include "EventManager.h"
#include "Controller.hpp"

using namespace irr;



// !Add a event receiver for for listening for events 
void CIrrDeviceStub::addEventReceiver(IEventReceiver *receiver)
{
   if (receiver != NULL)
      ReceiverList.push_back(receiver);
}
      
// !Remove a event receiver for for listening for events 
void CIrrDeviceStub::removeEventReceiver(IEventReceiver *receiver)
{
   s32 pos = ReceiverList.binary_search(receiver);

   if (pos != -1)
   {
      ReceiverList.erase(pos);
   }
}

//void CIrrDeviceStub::postEventFromUser(SEvent event)
//{
//   bool absorbed = false;
//
//   if (UserReceiver)
//      absorbed = UserReceiver->OnEvent(event);
//
//   for(u32 i=0; i<ReceiverList.size(); i++)
//      ReceiverList[i]->OnEvent(event);
//   
//   if (!absorbed && GUIEnvironment)
//      absorbed = GUIEnvironment->postEventFromUser(event);
//
//   if (!absorbed && SceneManager)
//      absorbed = SceneManager->postEventFromUser(event);
//}