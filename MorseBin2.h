#ifndef MorseBin2_h
#define MorseBin2_h
#include "Arduino.h"
	extern void MB2SendByte(String input,int sendpin);
	extern String MB2Receive(int respin);
	extern void MB2Send1(int sendpin);
	extern void MB2Send0(int sendpin);
#endif
