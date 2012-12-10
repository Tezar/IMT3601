#include "ObjectReader.hpp"
#include <assert.h>

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

	if(cached != 0 ) return cached->getValue();

	
	return readObject(name);
}

ObjectRecord* ObjectReader::readObject(const char * name)
{
	std::string path = baseDir+"/"+name+".xml";
	const char * cstr = path.c_str();
	IrrXMLReader* xml = createIrrXMLReader( cstr );

	ObjectRecord* object = 0;

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
	
	cache.insert(name, object );
	return object;
}

//todo: unify parseVehicle/SEmgnet


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
					child->parse(xml, device); //device is needed to load mesh for shapeDimension...
					obj->children.push_back(child);
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
						child->parse(xml, device); //device is needed to load mesh for shapeDimension...
						obj->children.push_back(child);
					} // end case
			break;

			case EXN_ELEMENT_END:
				return obj;
            break;
        }
    }

	return obj;

}



