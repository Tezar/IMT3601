#include "GameObjectManager.hpp"


GameObjectManagerClass::GameObjectManagerClass(IrrlichtDevice * d):
		device(d),
		counter(1)
{


}


void GameObjectManagerClass::clear()
{
	//todo:fix this
	ISceneManager* smgr = device->getSceneManager();
	smgr->clear();

	for(int i=1; i < counter; i++){
		ISceneNode * node = smgr->getSceneNodeFromId(i);
		if(node != 0) node->remove();
	}

	//reset our counter id
	counter = 1;
}
		
//load object itself
void GameObjectManagerClass::load(ObjectRecord* object)
{
	ISceneManager* smgr = device->getSceneManager();
	video::IVideoDriver* driver = device->getVideoDriver();
	ISceneNode * node = 0;
	
	switch(object->type)
	{
		case EOT_SEGMENT:
			//segment got no representation...
			break;
		case EOT_BOX:
			node = smgr->addCubeSceneNode(1.f);
			node->setScale(vector3df(object->shapeDimensions.x(),object->shapeDimensions.y(),object->shapeDimensions.z()));
			break;	//end case EOT_BOX

		default:
			IMesh* model = smgr->getMesh(object->getModel());
			node = smgr->addMeshSceneNode( model );
	
	}
	
	if(node != 0) //oh my we created the node! time to play with it
	{
			node->setID( nextId() );

			const char * texturePath = object->getTexture();
			if(texturePath){
				video::ITexture* texture =  driver->getTexture(texturePath);

				node->setMaterialTexture( 0, texture);
	
				node->getMaterial(0).AmbientColor.set(255,255,255,255);
				node->getMaterial(0).DiffuseColor.set(255,255,255,255);
				node->getMaterial(0).SpecularColor.set(255,255,255,255);
			
				node->setMaterialType(video::EMT_SOLID);
			}

		
			btVector3 position = object->position; 
			node->setPosition(vector3df(position.x(),position.y(),position.y()));
			
			btVector3 rotation = object->rotation; 
			node->setRotation(vector3df(rotation.x(),rotation.y(),rotation.y()));
	}

	int size = object->children.size();
	if(size > 0){
		for(core::list<ObjectRecord*>::ConstIterator it = object->children.begin(); it != object->children.end();it++)
		{
			ObjectRecord* child = (*it);
			load(child);
		}
	}
}


GameObjectManagerClass::~GameObjectManagerClass(void)
{
}
