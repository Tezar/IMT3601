#include "CongruentGenerator.hpp"


CongruentGenerator::CongruentGenerator(void)
{
}


CongruentGenerator::~CongruentGenerator(void)
{
}



void CongruentGenerator::reseed(irr::u32 newValue)
{
	currentSeed = newValue;
}

int CongruentGenerator::random()
{
	  currentSeed = currentSeed * 1103515245 + 12345;
      return (irr::u32)(currentSeed/65536) % 32768;
}
