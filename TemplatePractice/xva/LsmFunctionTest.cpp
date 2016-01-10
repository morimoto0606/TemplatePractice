#include "Test.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "LsmFunction.h"

namespace cva {
	namespace ublas = boost::numeric::ublas;
	
	double f0(const double& x) {
		return 1.0;
	}

	double f1(const double& x) {
		return x;
	}

	double f2(const double& x) {
		return x * x;
	}

	void LsmFunctionTest()
	{
		ublas::vector<double> a(3, 0.0);
		a(0) = 1;
		a(1) = 2;
		a(2) = 3;
		ublas::vector<boost::function<double (double)> >  functions(3);
		boost::function<double(const double&)> function0 = &f0;
		boost::function<double(double)> function1 = &f1;
		boost::function<double(double)> function2 = &f2;
		functions[0] = function0;
		functions[1] = function1;
		functions[2] = function2;
		LsmFunction<double, double> lsm(a, functions);
	}
}