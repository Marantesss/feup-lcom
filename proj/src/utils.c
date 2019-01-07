#include "lcom/lcf.h"
#include "utils.h"
#include <stdlib.h>

int generateRandomCoordinate(int lowerBound, int upperBound) {
	return rand() % (upperBound - lowerBound) + lowerBound;
}
