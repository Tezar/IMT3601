#include <irrlicht.h>
#include "EventManager.h"
#include "Controller.hpp"

using namespace irr;



// !Add a event receiver for for listening for events 
void CIrrDeviceStubclass::addEventReceiver(IEventReceiver *receiver)
{
   if (receiver != NULL)
      ReceiverList.push_back(receiver);
}
      
// !Remove a event receiver for for listening for events 
void CIrrDeviceStubclass::removeEventReceiver(IEventReceiver *receiver)
{
   s32 pos = ReceiverList.binary_search(receiver);

   if (pos != -1)
   {
      ReceiverList.erase(pos);
   }
}


bool CIrrDeviceStubclass::OnEvent(const SEvent& event)
{
   for (u32 s = 0; s < ReceiverList.size(); ++s)
   {
      if (ReceiverList[s]->OnEvent(event))
        return true; // only let one receiver handle message
   }

   return false;
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