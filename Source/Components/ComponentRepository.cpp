// ComponentRepository.cpp

#include "Components/Repository/ComponentRepository.h"

unsigned int ComponentRepository::id = 0; 

//-----------------------------------------------------------
// Name:
// Desc: 
//-----------------------------------------------------------
unsigned int ComponentRepository::GenerateId() 
{ 
	return id++; 
}