#include <iostream>
#include "PayOff.h"
#include "Dual.h"
#include "Functions.h"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/numeric/ublas/io.hpp>   

#include <boost/make_shared.hpp>
#include "Test.h"

namespace ublas = boost::numeric::ublas;

namespace cva {
	template <typename T, typename U>
	typename U::value_type payoffFunc(
		const cva::PayOff<T>& payoff,
		const U& x) {
		return payoff()(x);
	}

	void payoffTest()
	{
		ublas::vector<double> x(3);
		x(0) = 0.0;
		x(1) = 1.0;
		x(2) = 2.0;
		ublas::vector<double> y(3);
		y(0) = 3.0;
		y(1) = 4.0;
		y(2) = 5.0;

		ublas::matrix<double> m(3, 3, 0.0);
		for (std::size_t i = 0; i < 2; ++i) {
			for (std::size_t j = 0; j < 3; ++j) {
				m(i, j) = 3 * i + j;
			}
		}
		std::cout << m << std::endl;

		cva::Forward fwd(2.0, -1.0);
		cva::European eur(2.0, -1.0);

		std::cout << fwd(x) << ',' << fwd(y) << std::endl;
		std::cout << eur(x) << ',' << eur(y) << std::endl;
		std::cout << fwd(ublas::row(m, 1));
	}

	void payoffCrtpTest()
	{
		std::cout << "Test PayOff" << std::endl;
		ublas::vector<double> x(3);
		x(0) = 0.0;
		x(1) = 1.0;
		x(2) = 3.0;
		ublas::vector<double> y(3);
		y(0) = 3.0;
		y(1) = 4.0;
		y(2) = 5.0;

		cva::Forward fwd(2.0, -1.0);
		cva::European eur(2.0, -1.0);

		std::cout << "x = " << x << std::endl;
		std::cout << "y = " << y << std::endl;
		
		std::cout << "using Payoff Function " 
			<< payoffFunc(fwd, x) << ',' << 
			payoffFunc(eur, x) << std::endl;
		
		std::cout << "using Payoff Function " 
			<< payoffFunc(fwd, x) << ',' << 
			payoffFunc(eur, x) << std::endl;

	}

 	void payoffDerivTest()
	{
		std::cout << "Test PayOffDeriv" << std::endl;
		ublas::vector<cva::Dual<double>> x(3);
		x(0) = cva::Dual<double>(1.0);
		x(1) = cva::Dual<double>(0.1);
		x(2) = cva::Dual<double>(3.0);
		std::cout << "x = (" << x(0).value() << ',' 
			<< x(1).value() << ',' << x(2).value() << ')'  
			<< std::endl;

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

		cva::Forward fwd(2.0, -1.0);
		cva::European eur(2.0, -1.0);

		cva::Dual<double> resultFwd0 = fwd(x + d0);
		cva::Dual<double> resultFwd1 = fwd(x + d1);
		cva::Dual<double> resultFwd2 = fwd(x + d2);

		cva::Dual<double> resultEur0 = eur(x + d0);
		cva::Dual<double> resultEur1 = eur(x + d1);
		cva::Dual<double> resultEur2 = eur(x + d2);

		//std::cout << "(fwd(x), d/dx0 fwd(x)) = " <<  resultFwd0.value() << ',' << resultFwd0.deriv() << std::endl;
		//std::cout << "(fwd(x), d/dx1 fwd(x)) = " << resultFwd1.value() << ',' << resultFwd1.deriv() << std::endl;
		//std::cout << "(fwd(x), d/dx2 fwd(x)) = " << resultFwd2.value() << ',' << resultFwd2.deriv() << std::endl;

		//std::cout << "(eur(x), d/dx0 eur(x)) = " << resultEur0.value() << ',' << resultEur0.deriv() << std::endl;
		//std::cout << "(eur(x), d/dx1 eur(x)) = " << resultEur1.value() << ',' << resultEur1.deriv() << std::endl;
		//std::cout << "(eur(x), d/dx2 eur(x)) = " << resultEur2.value() << ',' << resultEur2.deriv() << std::endl;
	}
}//namespace cva {
