#include "Header.h"
int main() {
	srand(time(NULL));
	int op;
	int arr[4][4];
	int x, y, count = 0;
	gridinit(arr);
	printgrid(arr);
	while ((op = getoperation(arr)) != -1) {
		gridmanip(arr, op);
	}
	return 0;
}
