#include "Fruit.hpp"

Fruit::Fruit () : Weighable(0.0), name("") {}
Fruit::Fruit (const std::string& n, const double w) : Weighable(w), name(n) {}
Fruit::~Fruit() {}
