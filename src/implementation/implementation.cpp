//#include "pong.cpp"
#include <implementation/system/auramain.h>

#ifdef TESTING
#include "test.cpp"
#endif

void implementation() {
#ifdef TESTING
	test();
#else
	auraMain();
	//pong();
#endif
}
