#include "ToolBox.hpp"


ToolBox::ToolBox(ISceneNode* node):node(node)
{
	
void createToolBox()
{
	// remove tool box if already there
	IGUIEnvironment* env = EditorEnvironment::getInstance()->getGUI();
	IGUIElement* root = env->getRootGUIElement();
	IGUIElement* e = root->getElementFromId(5000, true);
	if (e) e->remove();

	// create the toolbox window
	IGUIWindow* wnd = env->addWindow(core::rect<s32>(450,25,640,480),
		false, L"Toolset", 0, 5000);

	// create tab control and tabs
	IGUITabControl* tab = env->addTabControl(
		core::rect<s32>(2,20,640-452,480-7), wnd, true, true);
	IGUITab* t1 = tab->addTab(L"Scale");
	IGUITab* t2 = tab->addTab(L"Empty Tab");

	// add some edit boxes and a button to tab one
	env->addEditBox(L"1.0", core::rect<s32>(40,50,130,70), true, t1, 901);
	env->addEditBox(L"1.0", core::rect<s32>(40,80,130,100), true, t1, 902);
	env->addEditBox(L"1.0", core::rect<s32>(40,110,130,130), true, t1, 903);
	env->addButton(core::rect<s32>(10,150,100,190), t1, 1101, L"set");

}
}


ToolBox::~ToolBox(void)
{
}
