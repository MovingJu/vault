#include "vault/store.h"
#include "vault/hashtable.h"

/* TODO(#3): 실제 필드(파일 디스크립터, code->offset 인덱스로 쓸 hashtable_t* 등)를 채울 것 */
struct vault_store {
    int unused;
};

vault_store_t *vault_store_open(const char *path) {
    (void)path;
    return NULL; /* TODO(#3) */
}

void vault_store_close(vault_store_t *store) {
    (void)store;
    /* TODO(#3) */
}

int vault_store_append(vault_store_t *store, const vault_record_t *record) {
    (void)store;
    (void)record;
    return -1; /* TODO(#3) */
}

vault_record_t *vault_store_find(vault_store_t *store, const char *code) {
    (void)store;
    (void)code;
    return NULL; /* TODO(#3) */
}

void vault_record_free(vault_record_t *record) {
    (void)record;
    /* TODO(#3) */
}

size_t vault_store_count(const vault_store_t *store) {
    (void)store;
    return 0; /* TODO(#3) */
}
