#include "vault/tagindex.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    tagindex_t *idx = tagindex_create();
    assert(idx != NULL);

    tagindex_add(idx, "rust", "abc1");
    tagindex_add(idx, "rust", "abc2");
    tagindex_add(idx, "cli", "abc1");

    size_t n = 0;
    char **codes = tagindex_lookup(idx, "rust", &n);
    assert(n == 2);
    assert(codes != NULL);
    free(codes);

    n = 42;
    codes = tagindex_lookup(idx, "missing-tag", &n);
    assert(n == 0);

    tagindex_destroy(idx);
    printf("tagindex: all tests passed\n");
    return 0;
}
