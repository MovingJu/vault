#include "vault/hashtable.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    hashtable_t *ht = ht_create(4);
    assert(ht != NULL);
    assert(ht_count(ht) == 0);

    int a = 1, b = 2, c = 3;
    ht_set(ht, "one", &a);
    ht_set(ht, "two", &b);
    ht_set(ht, "three", &c);
    assert(ht_count(ht) == 3);

    assert(*(int *)ht_get(ht, "two") == 2);
    assert(ht_get(ht, "missing") == NULL);

    /* 같은 키로 다시 set하면 덮어써야 함 — count가 늘어나면 안 됨 */
    int b2 = 20;
    ht_set(ht, "two", &b2);
    assert(ht_count(ht) == 3);
    assert(*(int *)ht_get(ht, "two") == 20);

    assert(ht_remove(ht, "one") == 1);
    assert(ht_count(ht) == 2);
    assert(ht_get(ht, "one") == NULL);
    assert(ht_remove(ht, "one") == 0); /* 이미 지운 키 */

    /* capacity 4에서 load factor 0.75를 넘겨서 리사이징 유도 */
    char keybuf[16];
    for (int i = 0; i < 20; i++) {
        snprintf(keybuf, sizeof(keybuf), "k%d", i);
        ht_set(ht, keybuf, &a);
    }
    assert(ht_count(ht) == 22); /* two, three, k0..k19 */
    assert(ht_get(ht, "k19") == &a);

    ht_destroy(ht);
    printf("hashtable: all tests passed\n");
    return 0;
}
