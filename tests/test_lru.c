#include "vault/lru.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    lru_cache_t *cache = lru_create(2);
    assert(cache != NULL);

    int a = 1, b = 2, c = 3;

    lru_put(cache, "a", &a);
    lru_put(cache, "b", &b);
    assert(lru_count(cache) == 2);

    /* a를 조회 -> a가 "최근 사용"으로 갱신됨 */
    assert(lru_get(cache, "a") == &a);

    /* capacity(2) 초과 -> 가장 오래 안 쓴 b가 쫓겨나야 함 */
    lru_put(cache, "c", &c);
    assert(lru_count(cache) == 2);
    assert(lru_get(cache, "b") == NULL);
    assert(lru_get(cache, "a") == &a);
    assert(lru_get(cache, "c") == &c);

    /* 같은 키에 다시 put하면 값 갱신, count는 그대로 */
    int a2 = 10;
    lru_put(cache, "a", &a2);
    assert(lru_count(cache) == 2);
    assert(lru_get(cache, "a") == &a2);

    lru_destroy(cache);
    printf("lru: all tests passed\n");
    return 0;
}
