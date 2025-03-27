#include "Weighable.hpp"
#include "iostream"

#ifndef FRUIT_H
#define FRUIT_H value

class Fruit: public Weighable {
	protected:
		std::string name;
	public:
		Fruit ();
		Fruit (const std::string& n, const double w);
		virtual ~Fruit () = 0;

		friend std::ostream& operator << (std::ostream& out, const Fruit& f) {
			return out << "Fruit: " << f.name << " " << f.Weighable::getWeight();
		}
};

#endif
