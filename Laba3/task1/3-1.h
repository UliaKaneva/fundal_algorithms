#ifndef LAB2_3_1_H
#define LAB2_3_1_H
#include <stdio.h>

#define add_1(number_s) do { \
    long long nums = 1;\
    while ((number_s) & nums) {\
        (number_s) = (number_s) ^ nums;\
        nums <<= 1;\
    }\
    (number_s) |= nums;\
    } while(0)


#define del_1(number_s) do { \
    int nums = 1;\
    while (!((number_s) & nums) && nums) {\
        (number_s) = (number_s) | nums;\
        nums <<= 1;\
    }\
    (number_s) = (number_s) ^ nums;    \
}while(0)

int ten_to_two(int number, int r, char ans[]);


#endif //LAB2_3_1_H
