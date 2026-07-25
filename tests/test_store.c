#include "vault/store.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    const char *path = "/tmp/vault_test_store.log";
    unlink(path);

    vault_store_t *store = vault_store_open(path);
    assert(store != NULL);
    assert(vault_store_count(store) == 0);

    vault_record_t rec;
    memset(&rec, 0, sizeof(rec));
    strcpy(rec.code, "abc1");
    rec.kind = 'L';
    rec.content = "https://example.com";
    rec.tags = "rust,cli";

    assert(vault_store_append(store, &rec) == 0);
    assert(vault_store_count(store) == 1);

    const vault_record_t *found = vault_store_find(store, "abc1");
    assert(found != NULL);
    assert(strcmp(found->content, "https://example.com") == 0);
    assert(strcmp(found->tags, "rust,cli") == 0);
    assert(vault_store_find(store, "missing") == NULL);

    vault_store_close(store);

    /* 재시작 시뮬레이션 — 로그를 다시 열었을 때 인덱스가 복구돼야 함 */
    vault_store_t *reopened = vault_store_open(path);
    assert(vault_store_count(reopened) == 1);
    const vault_record_t *found2 = vault_store_find(reopened, "abc1");
    assert(found2 != NULL);
    assert(strcmp(found2->content, "https://example.com") == 0);

    vault_store_close(reopened);
    unlink(path);

    printf("store: all tests passed\n");
    return 0;
}
