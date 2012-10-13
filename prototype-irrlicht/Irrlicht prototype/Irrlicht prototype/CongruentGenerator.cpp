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
      return (irr::u32)  (((currentSeed/65536) % 32768)/32768.0*maxNumber) ;
}
