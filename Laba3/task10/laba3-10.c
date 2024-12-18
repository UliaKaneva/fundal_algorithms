#include "3-10.h"

#include <stdio.h>

int main(int argc, char **argv) {
    String *name_in_put;
    String *name_out_put;
    if (get_opts(&name_in_put, &name_out_put, argc, argv)) {
        return 1;
    }
    String *result = create("");
    if (result == NULL) {
        delete(name_in_put);
        delete(name_out_put);
        return 1;
    }
    FILE *in_put = fopen(name_in_put->data, "r");
    if (in_put == NULL) {
        delete(name_in_put);
        delete(name_out_put);
        delete(result);
        return 1;
    }
    delete(name_in_put);

    if (parse_expression(in_put, result, 0)) {
        fclose(in_put);
        delete(name_out_put);
        delete(result);
        return 1;
    }

    fclose(in_put);
    FILE *out_put = fopen(name_out_put->data, "w");
    if (out_put == NULL) {
        delete(name_out_put);
        delete(result);
        return 1;
    }
    delete(name_out_put);
    fprintf(out_put, "%s", result->data);

    fclose(out_put);
    delete(result);
    return 0;

}
