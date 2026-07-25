#include "vault/hashtable.h"

hashtable_t *ht_create(size_t initial_capacity) {
    (void)initial_capacity;
    return NULL; /* TODO(#1) */
}

void ht_destroy(hashtable_t *ht) {
    (void)ht;
    /* TODO(#1) */
}

void ht_set(hashtable_t *ht, const char *key, void *value) {
    (void)ht;
    (void)key;
    (void)value;
    /* TODO(#1) */
}

void *ht_get(const hashtable_t *ht, const char *key) {
    (void)ht;
    (void)key;
    return NULL; /* TODO(#1) */
}

int ht_remove(hashtable_t *ht, const char *key) {
    (void)ht;
    (void)key;
    return 0; /* TODO(#1) */
}

size_t ht_count(const hashtable_t *ht) {
    (void)ht;
    return 0; /* TODO(#1) */
}
