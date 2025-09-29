#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter {
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter&);
	ScalarConverter& operator=(const ScalarConverter&);
	static bool isSpecial(const std::string &s);

public:
	static void convert(const std::string &s);
};

#endif // SCALARCONVERTER_HPP
