#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
	Data sample;
	sample.firstName = "Peter";
	sample.age = 42;
	sample.lastName = "Meier";

	uintptr_t raw = Serializer::serialize(&sample);
	Data *restored = Serializer::deserialize(raw);

	if (restored != &sample) {
		std::cerr << "Error: pointer mismatch.\n";
		return 1;
	}


    // print original and restored data
    std::cout << sample << std::endl;   
    std::cout << *restored << std::endl;
	return 0;
}