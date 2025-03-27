#include "Weighable.hpp"

Weighable::~Weighable() {}

double Weighable::getWeight() const {
	return weight;
}

void Weighable::setWeight(double w) {
	weight = w;
}
