#include <vector>
#include <iostream>

typedef std::vector < std::vector <int> > vect_o_vects;
typedef std::vector<int>::iterator vectit;

void print_sets (vect_o_vects input);
vect_o_vects all_subsets(std::vector<int> set);

int main () {
	int my_ints[] = { 2, 3, 4 };
	std::vector<int> set(my_ints, my_ints + sizeof(my_ints) / sizeof(int));
	vect_o_vects res = all_subsets(set);
	print_sets(res);
}

void print_sets (vect_o_vects input) {
	for (int i = 0; i < input.size(); ++i) {
		std::cout << "[";
		for (int j = 0; j < input[i].size(); ++j) {
			std::cout << input[i][j] << ", ";
		}
		std::cout << "]\n";
	}
}

 vect_o_vects all_subsets(std::vector<int> set) {
	// initialize, and add the whole set
	vect_o_vects results;
	results.push_back(set);

	// If it's an empty set, it only contains the empty set
	if (!set.size()) {
		return results;
	}

	// Add the empty set
	std::vector<int> mt;
	results.push_back(mt);

	if (set.size() == 1) {
		return results;
	}

	vect_o_vects *previous = new vect_o_vects;

	for (vectit iter = set.begin(); iter != set.end(); iter++) {
		std::vector<int> res;
		std::vector<int> ind;
		res.push_back(*iter);
		results.push_back(res);
		ind.push_back(results.size() - 1);
		(*previous).push_back(ind);
	}

	vect_o_vects *next = new vect_o_vects;

	int base_ind = 1;
	while (base_ind != set.size() - 1) {
		(*next).clear();
		for (int i = 0; i < set.size(); ++i) {
			std::vector<int> constructed_vector;
			(*next).push_back(constructed_vector);
		}
		for (int i = base_ind; i < set.size(); ++i) {
			// look back through all previous positions..
			for (int prev_ind = i - 1; prev_ind >= 0; prev_ind--){
				// loop through each set in there
				for (int j = 0; j < (*previous)[prev_ind].size(); ++j) {
					// Append current element to all sets for this element
					int index_of_set = (*previous)[prev_ind][j];
					std::vector<int> new_res = results[index_of_set];
					new_res.push_back(set[i]);
					results.push_back(new_res);
					(*next)[i].push_back(results.size() - 1);
				}
			}
		}
		vect_o_vects *temp = next;
		next = previous;
		previous = temp;
		base_ind++;
	}

	return results;
}