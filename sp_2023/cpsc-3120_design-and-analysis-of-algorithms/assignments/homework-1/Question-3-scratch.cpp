#include <iostream>
#include <cmath>

int calc_flips(int current_increment, int k) {
	int pred_flips = 0;
	for(int i=0; i<k-1; i++) {
		pred_flips = pred_flips + (current_increment / std::pow(2, i));
	}
	return pred_flips;
}

void Increment(bool a[], int k, int &current_increment, int &total_flips) {
	current_increment++;
	int flips = 0;
	for(int j=0; j<k; j++) {
		std::cout << a[j];
	}
	std::cout << "\n";
	std::cout << "Predicting " << calc_flips(current_increment, k) << " flips on this increment\n";
	for(int i=k-1; i>=0; i--) {
		if(a[i] == 0) {
			std::cout << "	Detected and flipped 0 to 1 at a[" << i << "]\n";
			a[i] = 1;
			flips++;
			total_flips++;
			break;
		} else {
			std::cout << "	Detected and flipped 1 to 0 at a[" << i << "]\n";
			a[i] = 0;
			flips++;
			total_flips++;
		}
	}
	std::cout << "		On increment number " << current_increment << ", flipped " << flips << " times to make " << total_flips << " total.";
	std::cout << "	a[0] currently " << a[0] << " \n";
}

int main(){
	int k = 8;
	bool binary_array[k] = {0,0,0,0,0,0,0,0};
	int n = 240;
	int current_increment = 0;
	int total_flips = 0;
	for(int i=0; i<n; i++) {
		Increment(binary_array, k, current_increment, total_flips);
	}
	for(int j=0; j<n; ++j) {
		std::cout << binary_array[j];
	}
}

