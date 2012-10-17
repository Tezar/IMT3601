#pragma once
#include <list>
#include <irrlicht.h>

using namespace std;
using namespace irr;
using namespace core;


class TrackPoint
{
public:
	core::vector3df position;
	//we use only rotation along Y axis so no need for evctor here
	irr::f32 direction;

	TrackPoint(void){};
	
	//constructor for creating point on position pos of curve defined by points p_1,p0,p1 and p2 
	TrackPoint(irr::f32 pos, vector3df p_1, vector3df p0, vector3df p1, vector3df p2 )
	{
		irr::f32 c1 = pos*((2-pos)*pos - 1);
		irr::f32 c2 = (pos*pos*(3*pos - 5) + 2);
		irr::f32 c3 = pos*((4 - 3*pos)*pos + 1);
		irr::f32 c4 = (pos-1)*pos*pos;
		
		vector3df a = c1*p_1;
		vector3df b = c2*p0;
		vector3df c = c3*p1;
		vector3df d = c4*p2;

		position.set(a+b+c+d);

		position /= 2;
	}
    




	
};



