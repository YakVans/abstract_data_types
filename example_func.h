#pragma once

template <typename T>
T map_example1(T value) {
    return value * 2;
}
template <typename T>
T map_example2(T value) {
    return value + 1;
}
template <typename T>
T map_example3(T value) {
    return value * value;
}

template <typename T>
bool where_example1(T value) {
    return value >= 1;
}
template <typename T>
bool where_example2(T value) {
    return value == 0;
}
template <typename T>
bool where_example3(T value) {
    return value < -3;
}

template <typename T>
T reduce_example1(T value, T c) {
    return value * c;
}
template <typename T>
T reduce_example2(T value, T c) {
    return value + c;
}
template <typename T>
T reduce_example3(T value, T c) {
    return value - c;
}