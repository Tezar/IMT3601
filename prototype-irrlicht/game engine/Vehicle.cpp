#include "Vehicle.hpp"


Vehicle::Vehicle(void)
{
	force = force_forward;
	turning = turning_none;
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

