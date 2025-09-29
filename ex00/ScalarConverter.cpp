#include "ScalarConverter.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <limits>

bool ScalarConverter::isSpecial(const std::string &s) {
	// nan, nanf, inf, inff, +inf, -inf, +inff, -inff
	if (s == "nan" || s == "nanf") return true;
	if (s == "inf" || s == "+inf" || s == "-inf") return true;
	if (s == "inff" || s == "+inff" || s == "-inff") return true;
	return false;
}

void ScalarConverter::convert(const std::string &s) {
	bool fromChar = false;
	bool isFloatLiteral = false;
	double value = 0.0;
	bool parseOk = true;

	// single non-digit char -> treat as char
	if (s.size() == 1 && !std::isdigit(static_cast<unsigned char>(s[0]))) {
		fromChar = true;
		value = static_cast<double>(s[0]);
	}
	else if (isSpecial(s)) {
		if (s == "nan" || s == "nanf")
			value = std::numeric_limits<double>::quiet_NaN();
		else if (s == "inf" || s == "+inf" || s == "inff" || s == "+inff")
			value = std::numeric_limits<double>::infinity();
		else if (s == "-inf" || s == "-inff")
			value = -std::numeric_limits<double>::infinity();
		if (!s.empty() && s[s.size() - 1] == 'f')
			isFloatLiteral = true;
	} else {
		errno = 0;
		char *end = NULL;
		value = std::strtod(s.c_str(), &end);
		if (end == s.c_str()) {
			parseOk = false;
		} else {
			if (*end == 'f' && *(end + 1) == '\0') {
				isFloatLiteral = true;
			} else if (*end != '\0') {
				parseOk = false;
			}
		}
	}

    (void)fromChar; // to avoid unused variable warning
    (void)isFloatLiteral; // to avoid unused variable warning

	// CHAR
	std::cout << "char: ";
	if (!parseOk || std::isnan(value) || std::isinf(value) || value < 0 || value > 127) {
		std::cout << "impossible\n";
	} else {
		char c = static_cast<char>(value);
		if (!std::isprint(static_cast<unsigned char>(c)))
			std::cout << "Non displayable\n";
		else
			std::cout << "'" << c << "'\n";
	}

	// INT
	std::cout << "int: ";
	if (!parseOk || std::isnan(value) || std::isinf(value)
		|| value < static_cast<double>(INT_MIN) || value > static_cast<double>(INT_MAX)) {
		std::cout << "impossible\n";
	} else {
		int i = static_cast<int>(value);
		std::cout << i << "\n";
	}

	// FLOAT
	std::cout << "float: ";
	if (!parseOk) {
		std::cout << "impossible\n";
	} else if (std::isnan(value)) {
		std::cout << "nanf\n";
	} else if (std::isinf(value)) {
		if (value < 0) std::cout << "-inff\n";
		else std::cout << "inff\n";
	} else {
		double intpart = 0.0;
		bool integral = (std::modf(value, &intpart) == 0.0);
		std::ostringstream oss;
		if (integral)
			oss << std::fixed << std::setprecision(1) << static_cast<float>(value);
		else
			oss << std::setprecision(6) << static_cast<float>(value);
		std::string out = oss.str();
		if (integral && out.find('.') == std::string::npos) out += ".0";
		std::cout << out << "f\n";
	}

	// DOUBLE
	std::cout << "double: ";
	if (!parseOk) {
		std::cout << "impossible\n";
	} else if (std::isnan(value)) {
		std::cout << "nan\n";
	} else if (std::isinf(value)) {
		if (value < 0) std::cout << "-inf\n";
		else std::cout << "inf\n";
	} else {
		double intpart = 0.0;
		bool integral = (std::modf(value, &intpart) == 0.0);
		std::ostringstream oss;
		if (integral)
			oss << std::fixed << std::setprecision(1) << value;
		else
			oss << std::setprecision(15) << value;
		std::string out = oss.str();
		if (integral && out.find('.') == std::string::npos) out += ".0";
		std::cout << out << "\n";
	}
}