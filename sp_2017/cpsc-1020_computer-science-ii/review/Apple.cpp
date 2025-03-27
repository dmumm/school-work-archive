#include "Apple.hpp"

Apple::Apple () : Fruit("Apple", 0.0), type("") {}
Apple::Apple (const std::string& t, const double w) : Fruit("Apple",w), type(t) {}
Apple::~Apple () {}
