#include "ToolBox.hpp"
#include "EditorEnvironment.hpp"
#include "VectorEditElement.hpp"

ToolBox::ToolBox(ISceneNode* node):node(node)
{
	populate();
}


ToolBox::~ToolBox(void)
{
	IGUIEnvironment* env = EditorEnvironment::getInstance()->getGUI();
	IGUIElement* root = env->getRootGUIElement();

	// remove tool box if we found itthere
	IGUIElement* e = root->getElementFromId(GUI_TOOLBOX_WINDOWS_ID, true);
	if (e) e->remove();
}

void ToolBox::populate()
{
	
	IGUIEnvironment* env = EditorEnvironment::getInstance()->getGUI();
	IGUIElement* root = env->getRootGUIElement();

	// remove tool box if already there
	IGUIElement* e = root->getElementFromId(GUI_TOOLBOX_WINDOWS_ID, true);
	if (e) e->remove();

	// create the toolbox window
	IGUIWindow* wnd = env->addWindow(core::rect<s32>(450,25,640,480),
		false, L"Toolset", 0, GUI_TOOLBOX_WINDOWS_ID);

	// create tab control and tabs
	IGUITabControl* tab = env->addTabControl(
		core::rect<s32>(2,20,640-452,480-7), wnd, true, true);
	IGUITab* t1 = tab->addTab(L"Scale");
	IGUITab* t2 = tab->addTab(L"Empty Tab");

	new VectorEditElement(t1,5,5, node->getPosition());

	// add some edit boxes and a button to tab one
	//env->addEditBox(L"1.0", core::rect<s32>(40,50,130,70), true, t1, GUI_TOOLBOX_ITEMS+1);
	//env->addSpinBox(L"1", core::rect<s32>(40,50,130,70),true, t1);
//		EditBox(L"1.0", core::rect<s32>(40,50,130,70), true, t1, GUI_TOOLBOX_ITEMS+1);
//	env->addEditBox(L"1.0", core::rect<s32>(40,80,130,100), true, t1, GUI_TOOLBOX_ITEMS+2);
	//env->addEditBox(L"1.0", core::rect<s32>(40,110,130,130), true, t1, GUI_TOOLBOX_ITEMS+3);
	env->addButton(core::rect<s32>(10,150,100,190), t1, GUI_TOOLBOX_SET, L"set");
}


/*void ToolBox::refresh()
{
	position->reresh();

}
*/
void ToolBox::apply()
{

	return; 
}
