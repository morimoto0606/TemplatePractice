#include <iostream>
#include "TraitAndTagDispacher.h"
#include "TraitTest2.h"

int main() {
	char x = 1;
	char y = 2;

	study::run(x);
	study::run(study::Hoge());
	return 0;
}