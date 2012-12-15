#include "Vehicle.hpp"




Vehicle::Vehicle(void)
{
	force = force_none;
	turning = turning_none;

	maxForce= 1;

	nextWaypoint = 0;

	steering = 0;
	steeringIncrement = 0.04f;
	steeringClamp = 0.3f;

	breaking = false;
	position.set(0,0,0);

}


Vehicle::~Vehicle(void)
{
	//todo:delete all shapes
}


void Vehicle::addShape(btCollisionShape* shape)
{
	shapes.push_back(shape);
}

void Vehicle::updatePhysics()
{
	int engineForce = 0;

	switch(force)
	{
		case force_forward:  engineForce = maxForce; break;
		case force_backward:  engineForce = -maxForce; break;
	}
		
	int breakForce = breaking ?  maxForce : 0;

	int wheelIndex = 0;
	pointer->applyEngineForce(engineForce, 0);
	pointer->applyEngineForce(engineForce, 1);


	pointer->setBrake(breakForce,2);
	pointer->setBrake(breakForce,3);




	switch(turning)
	{
		case turning_right:
			steering += steeringIncrement;
			if(steering > steeringClamp) steering = steeringClamp;
		break;
		case turning_left:
			steering -= steeringIncrement;
			if(steering < -steeringClamp) steering = -steeringClamp;
		break;
		case turning_none: //relaxation
			if(abs(steering) < (steeringIncrement*0.5)  ) break;	//skip if it's too small
			//go for zero
			steering += ((steering < 0) ? steeringIncrement : -steeringIncrement) *0.5;
	}

	wheelIndex = 0;
	pointer->setSteeringValue(steering,wheelIndex);
	wheelIndex = 1;
	pointer->setSteeringValue(steering,wheelIndex);


}


//
//scene::IMeshSceneNode* Vehicle::injectNode(IrrlichtDevice* device)
//{
//	ISceneManager* smgr = device->getSceneManager();
//	IVideoDriver* driver = device->getVideoDriver();
//
//	IrrXMLReader* xml = createIrrXMLReader("../config/vehicle.xml");
//
//	 
//    while(xml && xml->read())
//    {
//        switch(xml->getNodeType())
//        {
//            case EXN_ELEMENT:
//            {
//                if (!strcmp("chassis", xml->getNodeName()))
//                {
//					IAnimatedMesh* model = smgr->getMesh(xml->getAttributeValue("model"));
//					vehicleNode = smgr->addMeshSceneNode( model );
//					vehicleNode->setMaterialFlag(EMF_LIGHTING, false);
//
//					vehicleNode->setMaterialTexture( 0, driver->getTexture(xml->getAttributeValue("texture")) );
//
//                }
//                else
//                if (!strcmp("wheel", xml->getNodeName()))
//                {
//					IAnimatedMesh* model = smgr->getMesh(xml->getAttributeValue("model"));
//					ISceneNode* wheelNode = smgr->addMeshSceneNode( model,vehicleNode );
//
//					vector3df pos;
//					pos.X = xml->getAttributeValueAsFloat("posX");
//					pos.Y = xml->getAttributeValueAsFloat("posY");
//					pos.Z = xml->getAttributeValueAsFloat("posZ");
//
//					wheelNode->setPosition(pos);
//					wheelNode->setMaterialFlag(EMF_LIGHTING, false);
//                }
//            }
//            break;
//        }
//    }
//    delete xml;
//
//	return vehicleNode;
//}

