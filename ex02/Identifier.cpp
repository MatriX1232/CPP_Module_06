#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h> // use C header for uintptr_t to remain C++98 compatible

struct Data;

class Serializer {
private:
	Serializer();
	Serializer(const Serializer &);
	Serializer &operator=(const Serializer &);

public:
	static uintptr_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);
};

#endif // SERIALIZER_HPP

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

#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

static int pickRandom() {
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(NULL)));
		seeded = true;
	}
	return std::rand() % 3;
}

Base *generate(void) {
	switch (pickRandom()) {
		case 0:
			std::cout << "Generated: A\n";
			return new A();
		case 1:
			std::cout << "Generated: B\n";
			return new B();
		default:
			std::cout << "Generated: C\n";
			return new C();
	}
}

void identify(Base *p) {
	if (p == NULL) {
		std::cout << "Unknown (null)\n";
		return;
	}
	if (dynamic_cast<A *>(p)) {
		std::cout << "A\n";
	} else if (dynamic_cast<B *>(p)) {
		std::cout << "B\n";
	} else if (dynamic_cast<C *>(p)) {
		std::cout << "C\n";
	} else {
		std::cout << "Unknown\n";
	}
}

void identify(Base &p) {
	try {
		(void)dynamic_cast<A &>(p);
		std::cout << "A\n";
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<B &>(p);
		std::cout << "B\n";
		return;
	} catch (...) {}
	try {
		(void)dynamic_cast<C &>(p);
		std::cout << "C\n";
		return;
	} catch (...) {}
	std::cout << "Unknown\n";
}