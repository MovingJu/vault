#pragma once
#include <stddef.h>

/* 이슈 #1: 해시테이블
 *
 * - 문자열 키 -> void* 값을 저장하는 범용 해시테이블.
 * - 해시 함수: djb2 또는 FNV-1a 중 하나를 골라 구현 (문자열 순회하며 누적).
 * - 충돌 해결: 체이닝(연결리스트) 방식을 추천 — 버킷마다 ht_entry 연결리스트.
 * - 리사이징: count/capacity >= 0.75가 되면 capacity를 2배로 늘리고 전체 재해싱.
 * - store.c와 lru.c가 내부적으로 이 모듈을 사용하므로 먼저 구현해야 다른 이슈가 풀림.
 */

typedef struct ht_entry {
    char *key;
    void *value;
    struct ht_entry *next;
} ht_entry;

typedef struct {
    ht_entry **buckets;
    size_t capacity;
    size_t count;
} hashtable_t;

hashtable_t *ht_create(size_t initial_capacity);
void ht_destroy(hashtable_t *ht);

/* key는 내부에서 복사(strdup)해서 소유한다. value의 소유권은 호출자에게 있다. */
void ht_set(hashtable_t *ht, const char *key, void *value);
void *ht_get(const hashtable_t *ht, const char *key);

/* 성공적으로 지웠으면 1, 키가 없었으면 0 */
int ht_remove(hashtable_t *ht, const char *key);

size_t ht_count(const hashtable_t *ht);
