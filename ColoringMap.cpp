#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>

using namespace std;

int** szomszedsagiMatrix;
int elekSzama, n;
int* colors;

int nextValue(int step) {
	int i;
	while (true) {
		colors[step] = (colors[step] + 1) % 4;
		if (colors[step] == 0)
			return 0;
		for (i = 1; i <= n; i++)
			if (szomszedsagiMatrix[step][i] && colors[step] == colors[i])
				break;
		if (i == n + 1)
			return 0;
	}
}

void coloring(int step) {
	int i;
	while (true) {
		nextValue(step);
		if (colors[step] == 0)
			break;
		if (step == n) {
			for (i = 1; i <= n; i++) {
				cout << " " << colors[i];
			}
			cout << "\n";
		}
		else {
			coloring(step + 1);
		}

	}
}

int main() {
	ifstream in("graf.txt");
	if (!in.is_open()) {
		cout << "Sikertelen beolvasas!" << endl;
		return 0;
	}
	in >> n >> elekSzama;

	szomszedsagiMatrix = new int* [n];
	for (int i = 1; i <= n; i++) {
		szomszedsagiMatrix[i] = new int[n];
	}
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			szomszedsagiMatrix[i][j] = 0;
		}
	}

	int x, y;
	while (!in.eof()) {
		in >> x >> y;
		szomszedsagiMatrix[x][y] = 1;
		szomszedsagiMatrix[y][x] = 1;
	}
	in.close();

	colors = new int[n];
	for (int i = 1; i <= n; ++i) {
		colors[i] = 0;
	}

	cout << "Szomszedsagi matrix: " << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << szomszedsagiMatrix[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl << "A kovetkezo szinezesek lehetsegesek: " << endl;

	clock_t t;
	t = clock();
	coloring(1);
	t = clock() - t;

	cout << endl << "Ido: " << ((float)t) / CLOCKS_PER_SEC << endl;
}


