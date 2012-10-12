#include "TrackGenerator.hpp"


TrackGenerator::TrackGenerator(irr::u32 seed)
{
}


TrackGenerator::~TrackGenerator(void)
{
}


void TrackGenerator::reseed(irr::u32 newValue)
{
	currentSeed = newValue;
}

int TrackGenerator::random()
{
	  currentSeed = currentSeed * 1103515245 + 12345;
      return (irr::u32)(currentSeed/65536) % 32768;
}


