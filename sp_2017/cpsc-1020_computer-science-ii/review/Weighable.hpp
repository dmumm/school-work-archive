#ifndef WEIGHABLE_H
#define WEIGHABLE_H value

class Weighable {
	private:
		double weight;
	public:
		Weighable() 				: weight(0.0) {}
		Weighable(double w) : weight(w) {}
		virtual ~Weighable() = 0;

		double 	getWeight() const;
		void 		setWeight(double w);
};

#endif
