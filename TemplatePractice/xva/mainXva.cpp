#include <iostream>
#include "PayOff.h"
#include "Dual.h"
#include "Functions.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/io.hpp>   
#include <boost/numeric/ublas/expression_types.hpp>
#include <boost/make_shared.hpp>
#include "Test.h"

//namespace ublas = boost::numeric::ublas;
//template <typename T>
//typename ublas::vector_unary_traits<T, T>::result_type
//foo(const ublas::vector_expression<T>& x)
//{
//	std::cout << x()(1) << std::endl;
//	return x()(1) + x()(0);
//}

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
	cva::optionByLsmTest();
	cva::greeksByLsmTest();
	//ublas::vector<double> a(2);
	//a(0) = 3;
	//a(1) = 4;
	//ublas::vector<double> x = foo(a);
	int i = 0;
	std::cin >> i;
	return i;
}