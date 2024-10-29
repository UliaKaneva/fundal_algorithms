#include <stdio.h>
#include "3-1.h"



int main(void){
    int a = -120;
    char ans[34];
    if (ten_to_two(a, 1, ans)){
        printf("Incorrect options\n");
        return 1;
    }
    printf("%s", ans);
    return 0;
}