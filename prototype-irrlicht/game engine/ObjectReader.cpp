#include "ObjectReader.hpp"


ObjectReader::ObjectReader(const char * dir, IrrlichtDevice* d)
{
	setBaseDir(dir);
	device = d;
}


ObjectReader::~ObjectReader(void)
{
	//todo: clear all cached objects
}


void ObjectReader::setBaseDir(const char * dir)
{
	baseDir = dir;
}

ObjectRecord* ObjectReader::getObject(const char * name)
{
	ObjectCacheMap::Node* cached = cache.find(name);

	if(cached != 0 ) return &(cached->getValue());

	
	return readObjects(name);
}

ObjectRecord* ObjectReader::readObject(const char * name)
{
	std::string path = baseDir+"/"+name+".xml";
	const char * cstr = path.c_str();
	IrrXMLReader* xml = createIrrXMLReader( cstr );

	ObjectRecord* object = 0

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
            {
				//we allow only one root element
				assert(object == 0);

                if (!strcmp("vehicle", xml->getNodeName()))
                {
					object = parseVehicle(xml);
					continue;
                }
                if (!strcmp("segment", xml->getNodeName()))
                {
					object = parseSegment(xml);
					continue;
                }
            }
            break;
        }
    }
    delete xml;
	
	cache.insert(name, (*object) );
	return objects;
}


ObjectRecord* ObjectReader::parseVehicle(IrrXMLReader* xml)
{
	ObjectRecord* obj = new ObjectRecord();
	obj->type = EOT_VEHICLE;

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
					{
					ObjectRecord* child = new ObjectRecord();
					obj->children.push_back(child);

					if (!strcmp("chassis", xml->getNodeName()))
					{
						child->type = EOT_CHASSIS;
					}else if (!strcmp("wheel", xml->getNodeName()))
					{
						child->type = EOT_WHEEL;
					}
				
					child->model = xml->getAttributeValue("model");
					child->texture = xml->getAttributeValue("texture");
					
					readVec3d(xml->getAttributeValue("position"), child->position);
					readVec3d(xml->getAttributeValue("rotation"), child->rotation);
					readVec3d(xml->getAttributeValue("extra"), child->extra);
					readShape(xml->getAttributeValue("shape"), child->shape);

					if(child->shape != ES_NONE)
					{
						const char * dimension = xml->getAttributeValue("shapeDimensions");
						if(dimension == 0)
						{
							//dimension from AABB
							//!important - for now it works only if mesh is centered!
							ISceneManager* smgr = device->getSceneManager();
							IMesh* model = smgr->getMesh(child->model);
							core::aabbox3df box = model->getBoundingBox();
							vector3df extens = box.getExtent();
							child->shapeDimensions.setX( extens.X * 0.5);
							child->shapeDimensions.setY( extens.Y * 0.5);
							child->shapeDimensions.setZ( extens.Z * 0.5);
						}else
						{
							//dimension defined
							readVec3d(dimension, child->shapeDimensions);
						}
					} //end if loading shape dimension
				} // end case
			break;

			case EXN_ELEMENT_END:
				return obj;
            break;
        }
    }

	return obj;

}



ObjectRecord* ObjectReader::parseSegment(IrrXMLReader* xml)
{
	ObjectRecord* obj = new ObjectRecord();
	obj->type = EOT_SEGMENT;

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
					{
					ObjectRecord* child = new ObjectRecord();
					obj->children.push_back(child);

					if (!strcmp("chassis", xml->getNodeName()))
					{
						child->type = EOT_CHASSIS;
					}else if (!strcmp("wheel", xml->getNodeName()))
					{
						child->type = EOT_WHEEL;
					}
				
					child->model = xml->getAttributeValue("model");
					child->texture = xml->getAttributeValue("texture");
					
					readVec3d(xml->getAttributeValue("position"), child->position);
					readVec3d(xml->getAttributeValue("rotation"), child->rotation);
					readVec3d(xml->getAttributeValue("extra"), child->extra);
					readShape(xml->getAttributeValue("shape"), child->shape);

					if(child->shape != ES_NONE)
					{
						const char * dimension = xml->getAttributeValue("shapeDimensions");
						if(dimension == 0)
						{
							//dimension from AABB
							//!important - for now it works only if mesh is centered!
							ISceneManager* smgr = device->getSceneManager();
							IMesh* model = smgr->getMesh(child->model);
							core::aabbox3df box = model->getBoundingBox();
							vector3df extens = box.getExtent();
							child->shapeDimensions.setX( extens.X * 0.5);
							child->shapeDimensions.setY( extens.Y * 0.5);
							child->shapeDimensions.setZ( extens.Z * 0.5);
						}else
						{
							//dimension defined
							readVec3d(dimension, child->shapeDimensions);
						}
					} //end if loading shape dimension
				} // end case
			break;

			case EXN_ELEMENT_END:
				return obj;
            break;
        }
    }

	return obj;

}



void ObjectReader::readVec3d(const char * data,  btVector3& target)
{
	if(data == 0) return; //the attribute isn't present
	int success;

	float x,y,z;
	success = sscanf(data, "%f,%f,%f", &x,&y,&z);

	target.setValue(x,y,z);
}

void ObjectReader::readShape(const char * data,  E_SHAPE& shape)
{
	if(data == 0) return; //the attribute isn't present
	
	if(strcmp(data, "box") == 0){
		shape = ES_BOX;
		return;
	}

	if(strcmp(data, "sphere") == 0){
		shape = ES_SPHERE;
		return;
	}

	if(strcmp(data, "cylinder") == 0){
		shape = ES_CYLINDER;
		return;
	}

	//unknown
	return;

}

