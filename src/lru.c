#include "vault/lru.h"
#include "vault/hashtable.h"

/* TODO(#4): 실제 필드(hashtable_t* + 이중연결리스트 head/tail, capacity)를 채울 것 */
struct lru_cache {
    int unused;
};

lru_cache_t *lru_create(size_t capacity) {
    (void)capacity;
    return NULL; /* TODO(#4) */
}

void lru_destroy(lru_cache_t *cache) {
    (void)cache;
    /* TODO(#4) */
}

void lru_put(lru_cache_t *cache, const char *key, void *value) {
    (void)cache;
    (void)key;
    (void)value;
    /* TODO(#4) */
}

void *lru_get(lru_cache_t *cache, const char *key) {
    (void)cache;
    (void)key;
    return NULL; /* TODO(#4) */
}

size_t lru_count(const lru_cache_t *cache) {
    (void)cache;
    return 0; /* TODO(#4) */
}
