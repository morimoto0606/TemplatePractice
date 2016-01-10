#include "Test.h"
namespace cva {
	//namespace cva {
	//	template <typename T>
	//	double payoffFunc(const cva::PayOff<T, double>& payoff,
	//		const ublas::vector<double>& x) {
	//		return payoff(x);
	//	}
	//	cva::Dual quadFunc(const cva::Dual& x) {
	//		return x * x - 2.0;
	//	}
	//	cva::Dual quadFunc(const ublas::vector<cva::Dual>& x) {
	//		return ublas::inner_prod(x, x);
	//	}
	//	ublas::bounded_vector<cva::Dual, 2> f(
	//		const ublas::bounded_vector<cva::Dual, 3>& x)
	//	{
	//		ublas::vector<cva::Dual> y(2);
	//		y(0) = x(0) * x(1) * x(2);
	//		y(1) = x(0) / x(1) / x(2);
	//		return y;
	//	}
	//	ublas::bounded_matrix<double, 2, 3> df(
	//		const ublas::bounded_vector<double, 3>& x)
	//	{
	//		ublas::matrix<double> y(2, 3);
	//		y(0, 0) = x(1) * x(2);
	//		y(0, 1) = x(0) *  x(2);
	//		y(0, 2) = x(0) * x(1);
	//
	//		y(1, 0) = 1.0 / x(1) / x(2);
	//		y(1, 1) = -x(0) / x(1) / x(1) / x(2);
	//		y(1, 2) = -x(0) / x(1) / x(2) / x(2);
	//
	//		return y;
	//	}
	//	ublas::bounded_matrix<double, 1, 2> dg()
	//	{
	//		ublas::matrix<double> z(1, 2);
	//		z(0, 0) = 1.0;
	//		z(0, 1) = -1.0;
	//		return z;
	//	}
	//	cva::Dual g(const ublas::bounded_vector<cva::Dual, 2>& y)
	//	{
	//		cva::Dual z = y(0) - y(1);
	//		return z;
	//	}
	//	cva::Dual h(const ublas::vector<cva::Dual>& x)
	//	{
	//		return g(f(x));
	//	}
	//
	//	{
	//		std::cout << "Test PayOff" << std::endl;
	//		ublas::vector<double> x(3);
	//		x(0) = 1.0;
	//		x(1) = 2.0;
	//		x(2) = 3.0;
	//		ublas::matrix<double> m(3, 3, -2.0);
	//		cva::Forward<double> fwd(1.0, -1.0);
	//		cva::European<double> eur(1.0, -1.0);
	//
	//		//cva::PayOff<double>* fwdPayoff = new cva::Forward<double>(1.0, -1.0);
	//		std::cout << fwd(x) << std::endl;
	//		std::cout << eur(x) << std::endl;
	//		std::cout << payoffFunc(fwd, x) << std::endl;
	//		std::cout << fwd(ublas::column(m, 2)) << std::endl;
	//		std::cout << eur(ublas::column(m, 2)) << std::endl;
	//		std::cout << payoffFunc(eur, ublas::column(m, 2)) << std::endl;
	//	}
	//	{std::cout << "test f : R -> R" << std::endl;
	//	cva::Dual x(1.0);
	//	cva::Dual d(0.0, 1.0);
	//	//y = (d/dx quadFunc)(1.0)
	//	cva::Dual y = quadFunc(x + d);
	//	std::cout << y.value() << ',' << y.deriv() << std::endl;
	//	y = cva::max(x + d, 0.0);
	//	std::cout << y.value() << ',' << y.deriv() << std::endl;
	//	}
	//	{
	//		std::cout << "Test  f : R^3 -> R" << std::endl;
	//		ublas::vector<cva::Dual> x(3);
	//		x(0) = cva::Dual(2.0);
	//		x(1) = cva::Dual(-1.0);
	//		x(2) = cva::Dual(3.0);
	//
	//		ublas::vector<cva::Dual> d0(3);
	//		d0(0) = cva::Dual(0.0, 1.0);
	//		d0(1) = cva::Dual(0.0);
	//		d0(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d1(3);
	//		d1(0) = cva::Dual(0.0);
	//		d1(1) = cva::Dual(0.0, 1.0);
	//		d1(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d2(3);
	//		d2(0) = cva::Dual(0.0);
	//		d2(1) = cva::Dual(0.0);
	//		d2(2) = cva::Dual(0.0, 1.0);
	//
	//		//calculate (d / dx(0)) (x0, x1, x2)
	//		cva::Dual y = quadFunc(x + d0);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//
	//		//calculate (d / dx(1)) fwd(x0, x1, x2)
	//		y = quadFunc(x + d1);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//
	//		//calculate (d / dx(2)) fwd(x0, x1, x2)
	//		y = quadFunc(x + d2);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//	}
	//	{
	//		std::cout << "Test h(x) = g(f(x)), where f : R^3 -> R^2, g: R^2 -> R" << std::endl;
	//		ublas::vector<cva::Dual> x(3);
	//		x(0) = cva::Dual(2.0);
	//		x(1) = cva::Dual(-1.0);
	//		x(2) = cva::Dual(3.0);
	//
	//		ublas::vector<cva::Dual> d0(3);
	//		d0(0) = cva::Dual(0.0, 1.0);
	//		d0(1) = cva::Dual(0.0);
	//		d0(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d1(3);
	//		d1(0) = cva::Dual(0.0);
	//		d1(1) = cva::Dual(0.0, 1.0);
	//		d1(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d2(3);
	//		d2(0) = cva::Dual(0.0);
	//		d2(1) = cva::Dual(0.0);
	//		d2(2) = cva::Dual(0.0, 1.0);
	//
	//		//calculate (d / dx(0)) h(x0, x1, x2)
	//		cva::Dual y = h(x + d0);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//
	//		//calculate (d / dx(1)) h(x0, x1, x2)
	//		y = h(x + d1);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//
	//		//calculate (d / dx(2)) h(x0, x1, x2)
	//		y = h(x + d2);
	//		std::cout << y.value() << ',' << y.deriv() << std::endl;
	//
	//		ublas::vector<double> x2(3);
	//		x2(0) = 2.0;
	//		x2(1) = -1.0;
	//		x2(2) = 3.0;
	//		ublas::matrix<double> dh = ublas::prod(dg(), df(x2));
	//		std::cout << "check" << ',' << dh << std::endl;
	//	}
	//	{
	//		std::cout << "Test PayOffDeriv" << std::endl;
	//		ublas::vector<cva::Dual> x(3);
	//		x(0) = cva::Dual(1.0);
	//		x(1) = cva::Dual(0.1);
	//		x(2) = cva::Dual(3.0);
	//		ublas::vector<cva::Dual> d0(3);
	//		d0(0) = cva::Dual(0.0, 1.0);
	//		d0(1) = cva::Dual(0.0);
	//		d0(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d1(3);
	//		d1(0) = cva::Dual(0.0);
	//		d1(1) = cva::Dual(0.0, 1.0);
	//		d1(2) = cva::Dual(0.0);
	//
	//		ublas::vector<cva::Dual> d2(3);
	//		d2(0) = cva::Dual(0.0);
	//		d2(1) = cva::Dual(0.0);
	//		d2(2) = cva::Dual(0.0, 1.0);
	//
	//		cva::Forward<cva::Dual> fwd(cva::Dual(2.0), cva::Dual(-1.0));
	//		cva::European<cva::Dual> eur(cva::Dual(2.0), cva::Dual(-1.0));
	//
	//		cva::Dual resultFwd0 = fwd(x + d0);
	//		cva::Dual resultFwd1 = fwd(x + d1);
	//		cva::Dual resultFwd2 = fwd(x + d2);
	//
	//		cva::Dual resultEur0 = eur(x + d0);
	//		cva::Dual resultEur1 = eur(x + d1);
	//		cva::Dual resultEur2 = eur(x + d2);
	//
	//		std::cout << resultFwd0.value() << ',' << resultFwd0.deriv() << std::endl;
	//		std::cout << resultFwd1.value() << ',' << resultFwd1.deriv() << std::endl;
	//		std::cout << resultFwd2.value() << ',' << resultFwd2.deriv() << std::endl;
	//
	//		std::cout << resultEur0.value() << ',' << resultEur0.deriv() << std::endl;
	//		std::cout << resultEur1.value() << ',' << resultEur1.deriv() << std::endl;
	//		std::cout << resultEur2.value() << ',' << resultEur2.deriv() << std::endl;
	//	}
	//}//namespace cva
} //namespace cva