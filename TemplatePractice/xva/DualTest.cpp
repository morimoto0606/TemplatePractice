#include "Test.h"
#include "Dual.h"
#include "Functions.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/io.hpp>   

namespace cva {
	namespace ublas = boost::numeric::ublas;

	cva::Dual<double> quadFunc(const cva::Dual<double>& x) {
		return x * x - 2.0;
	}
	cva::Dual<double> quadFunc(const ublas::vector<cva::Dual<double>>& x) {
		return ublas::inner_prod(x, x);
	}
	ublas::bounded_vector<cva::Dual<double>, 2> f(
		const ublas::bounded_vector<cva::Dual<double>, 3>& x)
	{
		ublas::vector<cva::Dual<double>> y(2);
		y(0) = x(0) * x(1) * x(2);
		y(1) = x(0) / x(1) / x(2);
		return y;
	}
	ublas::bounded_matrix<double, 2, 3> df(
		const ublas::bounded_vector<double, 3>& x)
	{
		ublas::matrix<double> y(2, 3);
		y(0, 0) = x(1) * x(2);
		y(0, 1) = x(0) *  x(2);
		y(0, 2) = x(0) * x(1);

		y(1, 0) = 1.0 / x(1) / x(2);
		y(1, 1) = -x(0) / x(1) / x(1) / x(2);
		y(1, 2) = -x(0) / x(1) / x(2) / x(2);

		return y;
	}
	ublas::bounded_matrix<double, 1, 2> dg()
	{
		ublas::matrix<double> z(1, 2);
		z(0, 0) = 1.0;
		z(0, 1) = -1.0;
		return z;
	}
	cva::Dual<double> g(const ublas::bounded_vector<cva::Dual<double>, 2>& y)
	{
		cva::Dual<double> z = y(0) - y(1);
		return z;
	}
	cva::Dual<double> h(const ublas::vector<cva::Dual<double>>& x)
	{
		return g(f(x));
	}

	void dualTest()
	{
		std::cout << "test f : R -> R" << std::endl;
	cva::Dual<double> x(1.0);
	cva::Dual<double> d(0.0, 1.0);
	cva::Dual<double> y = quadFunc(x + d);
	std::cout << "(d/dx quadFunc)(1.0) = " 
		<< y.value() << ',' << y.deriv() << std::endl;
	y = cva::max(x + d, 0.0);
	std::cout << y.value() << ',' << y.deriv() << std::endl;
	}

	void dualVectorTest()
	{
		std::cout << "Test  f : R^3 -> R" << std::endl;
		ublas::vector<cva::Dual<double>> x(3);
		x(0) = cva::Dual<double>(2.0);
		x(1) = cva::Dual<double>(-1.0);
		x(2) = cva::Dual<double>(3.0);

		ublas::vector<cva::Dual<double>> d0(3);
		d0(0) = cva::Dual<double>(0.0, 1.0);
		d0(1) = cva::Dual<double>(0.0);
		d0(2) = cva::Dual<double>(0.0);

		ublas::vector<cva::Dual<double>> d1(3);
		d1(0) = cva::Dual<double>(0.0);
		d1(1) = cva::Dual<double>(0.0, 1.0);
		d1(2) = cva::Dual<double>(0.0);

		ublas::vector<cva::Dual<double>> d2(3);
		d2(0) = cva::Dual<double>(0.0);
		d2(1) = cva::Dual<double>(0.0);
		d2(2) = cva::Dual<double>(0.0, 1.0);

		cva::Dual<double> y = quadFunc(x + d0);
		std::cout << "(d / dx(0)) (x0, x1, x2) = " 
			<<y.value() << ',' << y.deriv() << std::endl;

		y = quadFunc(x + d1);
		std::cout << "(d / dx(1)) fwd(x0, x1, x2) = " 
			<<y.value() << ',' << y.deriv() << std::endl;

		y = quadFunc(x + d2);
		std::cout << "(d / dx(2)) fwd(x0, x1, x2) = "
			<< y.value() << ',' << y.deriv() << std::endl;
	}

	void dualCompositionTest()
	{
		std::cout << "Test h(x) = g(f(x)), where f : R^3 -> R^2, g: R^2 -> R" << std::endl;
		ublas::vector<cva::Dual<double>> x(3);
		x(0) = cva::Dual<double>(2.0);
		x(1) = cva::Dual<double>(-1.0);
		x(2) = cva::Dual<double>(3.0);

		ublas::vector<cva::Dual<double>> d0(3);
		d0(0) = cva::Dual<double>(0.0, 1.0);
		d0(1) = cva::Dual<double>(0.0);
		d0(2) = cva::Dual<double>(0.0);

		ublas::vector<cva::Dual<double>> d1(3);
		d1(0) = cva::Dual<double>(0.0);
		d1(1) = cva::Dual<double>(0.0, 1.0);
		d1(2) = cva::Dual<double>(0.0);

		ublas::vector<cva::Dual<double>> d2(3);
		d2(0) = cva::Dual<double>(0.0);
		d2(1) = cva::Dual<double>(0.0);
		d2(2) = cva::Dual<double>(0.0, 1.0);

		cva::Dual<double> y = h(x + d0);
		std::cout << "(d / dx(0)) h(x0, x1, x2) = " <<
			y.value() << ',' << y.deriv() << std::endl;

		y = h(x + d1);
		std::cout << "(d / dx(1)) h(x0, x1, x2) = " <<
			y.value() << ',' << y.deriv() << std::endl;

		y = h(x + d2);
		std::cout << "(d / dx(2)) h(x0, x1, x2) = " <<
			y.value() << ',' << y.deriv() << std::endl;

		ublas::vector<double> x2(3);
		x2(0) = 2.0;
		x2(1) = -1.0;
		x2(2) = 3.0;
		ublas::matrix<double> dh = ublas::prod(dg(), df(x2));
		std::cout << "dh(analytic) = " << ',' << dh << std::endl;
	}
	
} //namespace cva