#include "VectorEditElement.hpp"


VectorEditElement::VectorEditElement(gui::IGUIElement* parent, int x, int y, const vector3df& vector): target(vector)
{
	
	IGUIEnvironment* env = EditorEnvironment::getInstance()->getGUI();
	
	int editBoxWidth = 70;
	
	int pos = x;
	env->addSpinBox( core::stringw(vector.X).c_str() , core::rect<s32>(pos,y,pos+editBoxWidth,y+getHeight()),true, parent);
	pos += editBoxWidth+5;
	env->addSpinBox( core::stringw(vector.Y).c_str() , core::rect<s32>(pos,y,pos+editBoxWidth,y+getHeight()),true, parent);
	pos += editBoxWidth+5;
	env->addSpinBox( core::stringw(vector.Z).c_str() , core::rect<s32>(pos,y,pos+editBoxWidth,y+getHeight()),true, parent);

}

void VectorEditElement::refresh()
{

}


VectorEditElement::~VectorEditElement(void)
{
}
