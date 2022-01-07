#include <iostream>

#define k 5

void write(int perm[]) {

	for (int i = 0; i < k; i++) {
		std::cout << perm[i] << " ";
	}
	std::cout << std::endl;
}

void all_perm_rec(int perm[], bool used[], int i) {

	if (i == k) {
		write(perm);
		return;
	}

	for (int j = 0; j < k; j++) {
		if (used[j]) continue;
		perm[i] = j;
		used[j] = true;
		all_perm_rec(perm, used, i + 1);
		used[j] = false;
	}

}

void all_perm(int perm[]) {

	bool used[k];
	for (int i = 0; i < k; i++) used[i] = false;

	all_perm_rec(perm, used, 0);

}

int main() {

	int perm[k];

	all_perm(&perm[0]);

	return 0;
}