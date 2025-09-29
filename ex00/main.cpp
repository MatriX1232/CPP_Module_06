#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <cctype>
#include <limits>
#include "ScalarConverter.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Usage: ./convert <literal>\n";
		return 1;
	}
	std::string s(argv[1]);
	ScalarConverter::convert(s);
	return 0;
}
