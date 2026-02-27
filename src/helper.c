#include <float.h>

#include "../include/helper.h"

float min3(float a, float b, float c) {
	float min = FLT_MAX;
	float nums[3] = {a, b, c};
	for (int i = 0; i < 3; i++) {
		if (nums[i] < min) {
			min = nums[i];
		}
	}

	return min;
}

float max3(float a, float b, float c) {
	float max = FLT_MIN;
	float nums[3] = {a, b, c};
	for (int i = 0; i < 3; i++) {
		if (nums[i] > max) {
			max = nums[i];
		}
	}

	return max;
}

float signed_area(float ax, float ay, float bx, float by, float cx, float cy) {
	return (cx - ax) * (by - ay) - (cy - ay) * (bx - ax);
}
