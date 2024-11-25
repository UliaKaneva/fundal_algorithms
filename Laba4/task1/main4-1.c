#include <stdio.h>
#include "../../Laba3/task4/strings.h"
#include "4-1.h"


int main(int argc, char **argv) {

    String *filename = create("");
    if (filename == NULL) { return 1; }

    if (GetOpts(argc, argv, filename)) {
        delete(filename);
        return 1;
    }

    FILE *file = fopen(filename->data, "r");
    if (file == NULL) {
        delete(filename);
        return 1;
    }

    String *buffer = create("");
    if (buffer == NULL) {
        delete(filename);
        fclose(file);
        return 1;
    }

    if (replace_macros(file, buffer)) {
        delete(buffer);
        delete(filename);
        fclose(file);
        return 1;
    }

    fclose(file);
    file = fopen(filename->data, "w");
    if (file == NULL) {
        delete(buffer);
        delete(filename);
        fclose(file);
        return 1;
    }

    fprintf(file, "%s", buffer->data);

    delete(buffer);
    delete(filename);
    fclose(file);

    return 0;
}