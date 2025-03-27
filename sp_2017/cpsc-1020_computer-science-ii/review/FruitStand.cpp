#include "FruitStand.hpp"

FruitStand::FruitStand() : fruits() {}
FruitStand::~FruitStand() {
	for(std::vector<Fruit*>::iterator itr = fruits.begin(); itr != fruits.end(); itr++) {
		delete(*itr);
	}
	fruits.clear();
}

void FruitStand::addFruit(Fruit* fruit) {
	fruits.push_back(fruit);
}

double FruitStand::totalWeight() const {
	// IMPLEMENT
	return 0.0;
}

int FruitStand::numApples() const {
	// IMPLEMENT
	return 0;
}

int FruitStand::numBananas() const {
	// IMPLEMENT
	return 0;
}
