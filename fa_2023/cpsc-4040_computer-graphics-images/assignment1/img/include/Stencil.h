#ifndef STENCIL_H
#define STENCIL_H

#include <ctime>
#include <random>
#include <iostream> //TODO: debug
#include <iomanip> //TODO: debug
#include <cassert>

namespace image {

class Stencil {

      public:

	static int const DEFAULT_HALF_WIDTH = 2;

	Stencil(int halfwidth = DEFAULT_HALF_WIDTH);
	~Stencil();

    /* bool setToIdentity(void); */
    bool setToSharpen(void);
    bool setToBlur(void);

	int getHalfwidth() const { return half_width; }
	int getFullWidth() const;
	int getSize() const;
	int getIndex(int iCol, int jRow) const;

	void printStencil(void) const;

	// float & operator()(int iCol, int jRow);
	float const & operator() (int iCol, int jRow) const;

      private:

	int half_width;
	float * stencil_values;

}; // class Stencil

} // namespace image

#endif // STENCIL_H
