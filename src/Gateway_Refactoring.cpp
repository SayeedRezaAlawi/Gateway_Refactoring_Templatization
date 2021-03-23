//============================================================================
// Name        : Gateway_Refactoring.cpp
// Author      : Sayeed Reza Alawi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CPort.h"
#include "CUartPort.h"
#include "CCanPort.h"
#include "CGateway.h"
using namespace std;

int main() {

	CCanPort<8>::getDriverPackageSize();
	CGateway<CCanPort<8>,CUartPort<1>> g1;
	CGateway<CUartPort<1>,CCanPort<8>> g2;
	CGateway<CCanPort<8>,CCanPort<8>> g3;
//	g1.transmitFromAToB();
//	g2.transmitFromAToB();
	g3.transmitFromAToB();
	return 0;
}
