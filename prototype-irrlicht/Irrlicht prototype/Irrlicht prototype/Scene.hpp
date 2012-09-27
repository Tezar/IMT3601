#pragma once

class Scene
{

public:
	Scene(void){
	};
	~Scene(void){
	};

	virtual void onEnter() = 0;

	/** @param int number of ms to render
		@return int numer of unused ms **/
	virtual int onFrame(int) = 0;

	/** @return bool shouldDelete object on exit? Ie false for menu scene, true for game*/
	virtual bool onExit() = 0;
};

