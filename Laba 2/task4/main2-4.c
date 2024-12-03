#include <stdio.h>
#include "2-4.h"


int main() {

    int res = is_convex_polygon(10, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.6, 0.5);
    if (res < 0){
        return 1;
    }
    printf("This polygon is convex? - %d\n", res);


    double ans = polynomial_at_point(6, 2, 1.0, -2.0, 0.0);
    if (isnan(ans)){
        printf("Error n < 0\n");
    }
    else{
        printf("x0: %lf\n", ans);
    }
    int s = 2;
    char *result = (char *) calloc(s, sizeof(char));
    if (result == NULL) {
        return 1;
    }
    if (number_caprecara(&result, &s, 12, 41, "1", "b", "56", "66", "bb", "444", "778", "bbb", "12aa",
                         "1640", "2046", "2929", "3333", "4973", "5b60", "6060", "7249", "8889", "9293", "9b76", "a580",
                         "a912", "bbbb", "22223", "48730", "72392", "99999", "bbbbb", "12b649", "16ba51", "1a1a1a",
                         "222222", "22a54a", "26a952", "35186b", "39a39a", "404040", "4197a2", "450770", "5801b8",
                         "5bb600")) {
        free(result);
        return 1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}