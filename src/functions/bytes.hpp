#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include "../constants/types.hpp"

bool isPositive(Byte value) {
    return (value & 0b10000000) == 0;
}

bool isNegative(Byte value) {
    return (value & 0b10000000) != 0;
}

bool isZero(Byte value) {
    return value == 0;
}

bool isOverflow(Byte value) {
    return (value & 0b01000000) != 0;
}

bool isAddedOverflow(Byte valueOne, Byte valueTwo) {
    return (~(valueOne ^ valueTwo) & (valueOne ^ (valueOne + valueTwo)) & 0x80) > 0;
}

bool isSubtractedOverflow(Byte valueOne, Byte valueTwo) {
    return ((valueOne ^ valueTwo) & (valueOne ^ (valueOne - valueTwo)) & 0x80) > 0;
}

bool isOdd(Byte value) {
    return (value & 0b00000001) != 0;
}

bool isClear(Bit value) {
    return !value;
}

bool isSet(Bit value) {
    return value;
}

template <typename T>
T random(T start = 0, T end = (T) pow(2, sizeof(T) * 8)) {

    int low = start <= end ? start : end;
    int high = start > end ? start : end;
    int range = high - low + 1;

    return (T) (rand() % range + low);
}

template <typename T>
T negative(T value) {

    return (T) (~value + 1);

}
