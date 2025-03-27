#include "Fruit.hpp"

#ifndef APPLE_H
#define APPLE_H value

class Apple: public Fruit {
	protected:
		std::string type;
	public:
		Apple ();
		Apple (const std::string& t, const double w);
		~Apple ();

		friend std::ostream& operator << (std::ostream& out, const Apple& a) {
			return out << "Apple: " << a.type << " " << a.Weighable::getWeight() << "oz";
		}
};

#endif
