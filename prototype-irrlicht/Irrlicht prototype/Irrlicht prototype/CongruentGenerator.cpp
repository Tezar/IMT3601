#include "CongruentGenerator.hpp"


CongruentGenerator::CongruentGenerator(void)
{
}


CongruentGenerator::~CongruentGenerator(void)
{
}



void CongruentGenerator::seed(irr::u32 newValue)
{
	currentSeed = newValue;
}

irr::u32 CongruentGenerator::random(int maxNumber)
{
	currentSeed = currentSeed * 1103515245 + 12345;
	irr::f32 f = irr::f32((currentSeed/65536) % 32768);
	f = irr::f32(f/32768.0*maxNumber);
    return irr::u32(f) ;
}
