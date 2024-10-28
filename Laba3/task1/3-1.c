#include "3-1.h"


long long my_abs(long long number) {
    if (number & (1 << 31)) {
        long long res = 0;
        for (int i = 1; i != (1 << 31); i <<= 1) {
            res = (number & i) ? res : res | i;
        }
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

    while (number_v != 0) {
        n = (int) (number_v & ost);
        number_v >>= r;
        res[index] = digit[n];
        add_1(index);
    }

    del_1(index);

    while (index >= 0) {
        ans[index_ans] = res[index];
        add_1(index_ans);
        del_1(index);
    }
    ans[index_ans] = '\0';
    return 0;
}