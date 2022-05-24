#include <stdlib.h>
#include <assert.h>

#include "../src/helper.h"

static void open_stat_file_works(void) {
    FILE* const stat_file = open_stat_file(NULL);

    assert(stat_file != NULL);

    fclose(stat_file);
}

static void get_cores_count_works(void) {
    assert(get_cores_count(NULL) > 0);
}

int main(void) {
    open_stat_file_works();
    get_cores_count_works();

    return EXIT_SUCCESS;
}
