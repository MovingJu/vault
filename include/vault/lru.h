#pragma once
#include <stddef.h>

/* 이슈 #4 (확장): LRU 캐시 — 해시테이블 + 이중연결리스트
 *
 * LeetCode 146(LRU Cache)과 동일한 구조. capacity를 넘기면 가장 오래 조회 안 된
 * 항목을 자동으로 쫓아낸다(evict). get으로 조회하면 그 항목은 "방금 사용됨"으로
 * 갱신되어 리스트 맨 앞으로 이동한다.
 *
 * 용도: store.c의 핫 링크(자주 조회되는 code)를 매번 디스크/해시테이블까지
 * 안 가고 캐시에서 바로 서빙하기 위함.
 */

typedef struct lru_cache lru_cache_t;

lru_cache_t *lru_create(size_t capacity);
void lru_destroy(lru_cache_t *cache);

/* value의 소유권은 호출자에게 있다 — 캐시는 포인터만 보관 */
void lru_put(lru_cache_t *cache, const char *key, void *value);

/* 조회에 성공하면 그 키를 최근 사용으로 갱신한다 */
void *lru_get(lru_cache_t *cache, const char *key);

size_t lru_count(const lru_cache_t *cache);
