#include <irrlicht.h>
using namespace irr;

class UserInput : public IEventReceiver
{
private:
	bool KeyIsDown[KEY_KEY_CODES_COUNT];

public:
	virtual bool OnEvent(const SEvent& event);
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;
	UserInput();
};
