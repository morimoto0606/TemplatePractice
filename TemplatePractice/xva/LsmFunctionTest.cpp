#include "Test.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/function.hpp>
#include "LsmFunction.h"
#include "Dual.h"
namespace cva {
	namespace ublas = boost::numeric::ublas;
	
	double f0(const double& x) {
		return 1.0;
	}
	double f1(const double& x) {
		return x;
	}
	double f2(const double x) {
		return x * x;
	}

	Dual<double> g0(const Dual<double>& x) {
		return Dual<double>(1.0);
	}
	Dual<double> g1(const Dual<double>& x) {
		return x;
	}
	Dual<double> g2(const Dual<double> x) {
		return x * x;
	}
	void lsmFunctionTest()
	{
		ublas::vector<double> a(3);
		a(0) = 1;
		a(1) = 2;
		a(2) = 3;
		ublas::vector<boost::function<double (double)> >  functions(3);
		boost::function<double(double)> function0 = &f0;
		boost::function<double(double)> function1 = &f1;
		boost::function<double(double)> function2 = &f2;
		functions(0) = function0;
		functions(1) = function1;
		functions(2) = function2;
		LsmFunction<double, double> lsm(a, functions);
		std::cout << "LsmFunctionTest" << std::endl;
		std::cout << "operator(x)  = 1 + 2x + 3x^2, x=2, expected 17" 
			<< ',' << "actual = " <<  lsm(2.0) << std::endl;

		ublas::vector<boost::function<Dual<double> (const Dual<double>&)> >  dualFunctions(3);
		boost::function<Dual<double> (const Dual<double>&)> dualFunction0 = &g0;
		boost::function<Dual<double>(const Dual<double>&)> dualFunction1 = &g1;
		boost::function<Dual<double>(const Dual<double>&)> dualFunction2 = &g2;
		dualFunctions(0) = dualFunction0;
		dualFunctions(1) = dualFunction1;
		dualFunctions(2) = dualFunction2;
		LsmFunction<Dual<double>, double> lsmDual(a, dualFunctions);
		Dual<double> x(2.0, 1.0);
		Dual<double> y = lsmDual(x);
		std::cout << "LsmFunctionTest" << std::endl;
		std::cout << "operator(x)  = 1 + 2x + 3x^2, x=2, expected value = 17, dual = 14"
			<< ',' << "actual = " << y.value()  << ',' << y.deriv()<< std::endl;
	}
}