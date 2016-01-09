#include "Test.h"
#include "Path.h"
#include "Dual.h"
#include <iostream>
#include <boost/numeric/ublas/io.hpp>   

namespace cva {
	void pathTest()
	{
		const Dual x0(100.0, 5.0);
		const Dual mu(0.1);
		const Dual sigma(0.3);
		const std::size_t pathNum = 10;
		const std::size_t gridNum = 5;
		const double dt = 1.0;
		const std::size_t seed = 42;
		const Path<Dual> path(x0, mu, sigma, pathNum,
			gridNum, dt, seed);

		
	}
}