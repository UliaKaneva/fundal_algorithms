#include "3-1.h"


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


long long my_abs(long long number) {
    if (number & (1 << 31)) {
        long long res = number;
        res = ~res;
        add_1(res);
        return res;
    } else { return number; }
}


int ten_to_two(int number, int r, char ans[]) {
    if (r > 5 || r < 1) { return 1; }
    char const digit[33] = "0123456789abcdefghijklmnopqrstuv";
    int index = 0;
    int index_ans = 0;
    long long number_v = number;
    char res[33];
    int ost = 0;
    int num = 1;
    int n = 0;

    if (number_v < 0) {
        ans[0] = '-';
        number_v = my_abs(number_v);
        add_1(index_ans);
    }

    while (num < (1 << r)) {
        ost |= num;
        num <<= 1;
    }

    while (number_v >= (1 << r)) {
        n = (int) (number_v & ost);
        number_v >>= r;
        res[index] = digit[n];
        add_1(index);
    }
    res[index] = digit[number_v];

    while (index >= 0) {
        ans[index_ans] = res[index];
        add_1(index_ans);
        del_1(index);
    }
    ans[index_ans] = '\0';
    return 0;
}