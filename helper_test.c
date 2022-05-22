#include <assert.h>

#include "helper_test.h"

#include "helper.h"

void open_stat_file_works(void) {
    FILE* const stat_file = open_stat_file();

    assert(stat_file != NULL);

    fclose(stat_file);
}
