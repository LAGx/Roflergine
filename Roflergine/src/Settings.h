#pragma once


#define STACK_STRING_LENGTH 1024 

// Select NVidia card by default
extern "C" {
	_declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001;
}
