#include "ConfigReader.hpp"


ObjectReader::ObjectReader(const char * dir)
{
	baseDir = dir;
}


ObjectReader::~ObjectReader(void)
{
	//todo: clear all cached objects
}

list<ObjectRecord*> ObjectReader::getObjects(const char * name)
{
	for(core::list<configCachePair>::ConstIterator it = cache.begin(); it != cache.end(); it++)
	{
		if(strcmp((*it).first, name) == 0) return ((*it).second);
	}

	return readObjects(name);
}

list<ObjectRecord*> ObjectReader::readObjects(const char * name)
{
	std::string path = baseDir+name;
	const char * cstr = path.c_str();
	IrrXMLReader* xml = createIrrXMLReader( cstr );
	delete[] cstr;  
	 

	list<ObjectRecord*> * objects = new list<ObjectRecord*>();

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
            {
                if (!strcmp("vehicle", xml->getNodeName()))
                {
					objects->push_back( parseVehicle(xml) ); 
                }
            }
            break;
        }
    }
    delete xml;

	cache.push_back( configCachePair(name, objects) );
}


ObjectRecord* ObjectReader::parseVehicle(IrrXMLReader* xml)
{
	ObjectRecord* obj = new ObjectRecord;
	obj->type = EOT_VEHICLE;

    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
            case EXN_ELEMENT:
                if (!strcmp("chassis", xml->getNodeName()))
                {
					ObjectRecord* child = new ObjectRecord;

					child->type = EOT_CHASSIS;
					child->model = xml->getAttributeValue("model");
					child->texture = xml->getAttributeValue("texture");

					obj->children.push_back(child);
					break;
                }
                
				if (!strcmp("wheel", xml->getNodeName()))
                {
					ObjectRecord* child = new ObjectRecord;

					child->type = EOT_WHEEL;
					child->model = xml->getAttributeValue("model");
					child->texture = xml->getAttributeValue("texture");
					
					readVec3d(xml->getAttributeValue("position"), child->position);
					readVec3d(xml->getAttributeValue("rotation"), child->rotation);
					readVec3d(xml->getAttributeValue("extra"), child->extra);
					

					obj->children.push_back(child);
					break;
                }

				break;

			case EXN_ELEMENT_END:
				return obj;
            break;
        }
    }

	return obj;

}





void ObjectReader::readVec3d(const char * data, vector3df target)
{
	if(data == 0) return; //the attribute isn't present
	int success;

	success = sscanf(data, "%f,%f,%f", &target.X,&target.Y,&target.Z);
}