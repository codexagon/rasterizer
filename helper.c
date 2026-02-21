#include "limits.h"

#include "helper.h"

int min3(int a, int b, int c) {
	int min = INT_MAX;
	int nums[3] = {a, b, c};
	for (int i = 0; i < 3; i++) {
		if (nums[i] < min) {
			min = nums[i];
		}
	}

	return min;
}

int max3(int a, int b, int c) {
	int max = INT_MIN;
	int nums[3] = {a, b, c};
	for (int i = 0; i < 3; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}

	return max;
}

int sign(int ax, int ay, int bx, int by, int px, int py) {
	return (bx - ax) * (py - ay) - (by - ay) * (px - ax);
}
