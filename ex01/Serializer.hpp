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
