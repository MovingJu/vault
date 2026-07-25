#include "vault/tagindex.h"

/* TODO(#5): 실제 필드(hashtable_t* tag -> 동적 배열)를 채울 것 */
struct tagindex {
    int unused;
};

tagindex_t *tagindex_create(void) {
    return NULL; /* TODO(#5) */
}

void tagindex_destroy(tagindex_t *idx) {
    (void)idx;
    /* TODO(#5) */
}

void tagindex_add(tagindex_t *idx, const char *tag, const char *code) {
    (void)idx;
    (void)tag;
    (void)code;
    /* TODO(#5) */
}

char **tagindex_lookup(const tagindex_t *idx, const char *tag, size_t *out_count) {
    (void)idx;
    (void)tag;
    if (out_count) {
        *out_count = 0;
    }
    return NULL; /* TODO(#5) */
}
