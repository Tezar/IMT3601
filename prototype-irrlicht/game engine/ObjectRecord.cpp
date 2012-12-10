#include "ObjectRecord.hpp"
#include <assert.h>


ObjectRecord::ObjectRecord():
	  	shape(ES_NONE),
		mass(0)
{
		shapeDimensions.setValue(1,1,1);
		position.setZero();
		rotation.setZero();

}

ObjectRecord::~ObjectRecord()
{
		//todo: iterate and delete children
		
	};


void ObjectRecord::parse(IrrXMLReader* xml, IrrlichtDevice* device = 0)
{
#define loadIfMatch(attr, code) if(strcmp(name, attr) == 0){ code; continue; }
	
	assert(xml->getNodeType() == EXN_ELEMENT);

	readType(xml->getNodeName(), this->type);

	int attrCount = xml->getAttributeCount();

	//load all attributes
	for(int i=0; i < attrCount; i++){
		const char * name = xml->getAttributeName(i);
		const char * val  = xml->getAttributeValue(i);

		loadIfMatch("position", readVec3d(val, position) );
		loadIfMatch("rotation", readVec3d(val, rotation) );
		loadIfMatch("shapeDimensions", readVec3d(val, shapeDimensions) );

		loadIfMatch("shape",    readShape(val, shape) );
		loadIfMatch("mass",    mass = xml->getAttributeValueAsFloat(i) );

		//everything failed, add it to extra
		extra.set(name, val);
	}

	//default box type
	if(shape == ES_NONE)
	{
		if(type == EOT_BOX) shape = ES_BOX;
	}

	const char * model = getExtra("model");

	if(model)
	{
		//if mesh is set, load dimension from it;

		//dimension from AABB
		//!important - for now it works only if mesh is centered!
		ISceneManager* smgr = device->getSceneManager();
		IMesh* mesh = smgr->getMesh( io::path(model) );
		core::aabbox3df box = mesh->getBoundingBox();
		vector3df extens = box.getExtent();
		shapeDimensions.setX( extens.X * 0.5);
		shapeDimensions.setY( extens.Y * 0.5);
		shapeDimensions.setZ( extens.Z * 0.5);
	} //end if loading shape dimension

}


const char * ObjectRecord::getExtra(const char * name)
{
	map<std::string, std::string>::Node* node =  extra.find(name);
	if(node == 0) return 0;
	return node->getValue().c_str();
}


btCollisionShape* ObjectRecord::createShape()
{
		switch(shape)
		{
		case ES_BOX:
			return new btBoxShape( shapeDimensions *0.5 );
		case ES_CYLINDER:
			return new btCylinderShapeX( shapeDimensions  );
		default:
		case ES_NONE:
			return 0;
		}
		
}

	


void ObjectRecord::readVec3d(const char * data,  btVector3& target)
{
	if(data == 0) return; //the attribute isn't present
	int success;

	float x,y,z;
	success = sscanf(data, "%f,%f,%f", &x,&y,&z);

	target.setValue(x,y,z);
}

void ObjectRecord::readShape(const char * data,  E_SHAPE& shape)
{
	if(data == 0) return; //the attribute isn't present

	#define setShapeIfMatch(x,y) if(strcmp(data, x) == 0){ shape = y; return; }

	setShapeIfMatch("box", ES_BOX);
	setShapeIfMatch("sphere", ES_SPHERE);
	setShapeIfMatch("cylinder", ES_CYLINDER);

	//unknown
	return;
}



void ObjectRecord::readType(const char * data,  E_OBJECT_TYPE& type)
{
	if(data == 0) return; //the attribute isn't present

	#define setTypeIfMatch(x,y) if(strcmp(data, x) == 0){ type = y; return; }
	
	setTypeIfMatch("vehicle",EOT_VEHICLE);
	setTypeIfMatch("segment",EOT_SEGMENT);
	setTypeIfMatch("chassis",EOT_CHASSIS);
	setTypeIfMatch("wheel",EOT_WHEEL);
	setTypeIfMatch("body",EOT_BODY);
	setTypeIfMatch("box",EOT_BOX);

	//unknown
	return;
}
