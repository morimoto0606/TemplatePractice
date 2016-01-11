#include <iostream>
#include "PayOff.h"
#include "Dual.h"
#include "Functions.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/io.hpp>   

#include <boost/make_shared.hpp>
#include "Test.h"

int main()
{
	cva::pathTest();
	cva::europeanTest();
	cva::payoffTest();
	cva::dualTest();
	cva::dualVectorTest();
	cva::dualCompositionTest();
	cva::lsmFunctionTest();
	cva::regressionTest();
	int i = 0;
	std::cin >> i;
	return i;
}