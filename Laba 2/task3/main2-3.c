#include "2-3.h"



int main(){
    int size = 2;
    char *ans = (char *) malloc(size * sizeof(char));
    if (ans == NULL){
        return 1;
    }
    char str[100] = "nana\n";
    if (find_in_files(str, &ans, &size, 2, "test1.txt", "test2.txt")){
        free(ans);
        return 1;
    }
    printf("%s", ans);
    free(ans);
    return 0;
}