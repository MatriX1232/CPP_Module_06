#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <ostream>

struct Data {
	std::string firstName;
	int age;
	std::string lastName;
};

// inline stream operator for Data to avoid multiple-definition across TUs
inline std::ostream &operator<<(std::ostream &os, Data const &d)
{
	// format as three lines: firstName, age, lastName
	os << d.firstName << '\n' << d.age << '\n' << d.lastName;
	return os;
}

#endif // DATA_HPP
