#include "vector"
#include "ostream"
#include "Fruit.hpp"
#include "Apple.hpp"

#ifndef FRUIT_STAND_H
#define FRUIT_STAND_H value

class FruitStand {
	protected:
		std::vector<Fruit*> fruits;
	public:
		FruitStand ();
		~FruitStand ();

		void addFruit (Fruit* fruit);
		double totalWeight() const;
		int numApples() const;
		int numBananas() const;

		// Print out summary of fruit stand
		friend std::ostream& operator << (std::ostream& out, const FruitStand& fs) {
			// Print number of apples and bananas and total weight
			out << "Fruit Stand!" 		<< std::endl
					<< "Apples : " 				<< fs.numApples() << std::endl
					<< "Bananas : " 			<< fs.numBananas() << std::endl
					<< "Total Weight : " 	<< fs.totalWeight() << std::endl;

			// Print out all fruits

			// ...

			//

			return out;
		}

};

#endif
