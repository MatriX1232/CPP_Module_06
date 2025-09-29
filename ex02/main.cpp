#include <iostream>
#include "Base.hpp"

// ...existing declarations...
Base *generate(void);
void identify(Base *p);
void identify(Base &p);

int main() {
	const int iterations = 5;
	for (int i = 0; i < iterations; ++i) {
		Base *obj = generate();
		std::cout << "identify(pointer): ";
		identify(obj);
		std::cout << "identify(reference): ";
		identify(*obj);
		delete obj;
		std::cout << "----\n";
	}
	return 0;
}
