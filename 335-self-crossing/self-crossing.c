#include <stdbool.h>

bool isSelfCrossing(int* distance, int distanceSize) {
    if (distanceSize <= 3) return false;

    for (int i = 3; i < distanceSize; i++) {
        // Case 1: 4th line crosses 1st line (standard inward spiral)
        if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
            return true;
        }

        // Case 2: 5th line meets/crosses 1st line
        if (i >= 4) {
            if (distance[i - 1] == distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
        }

        // Case 3: 6th line crosses 1st line (transition spiral)
        if (i >= 5) {
            if (distance[i - 1] <= distance[i - 3] && 
                distance[i - 1] >= distance[i - 3] - distance[i - 5] &&
                distance[i - 2] >= distance[i - 4] &&
                distance[i] >= distance[i - 2] - distance[i - 4]) {
                return true;
            }
        }
    }

    return false;
}
