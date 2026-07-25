#pragma once
#include <stddef.h>

/* 이슈 #5 (확장): 태그 역색인(inverted index)
 *
 * tag 문자열 -> 그 태그를 가진 code들의 동적 배열.
 * hashtable.c 위에 얹어서 만들면 됨 — tag를 key로, "code 배열을 담은 구조체
 * 포인터"를 value로 저장하고, 배열은 필요할 때마다 realloc으로 늘리는 방식.
 */

typedef struct tagindex tagindex_t;

tagindex_t *tagindex_create(void);
void tagindex_destroy(tagindex_t *idx);

void tagindex_add(tagindex_t *idx, const char *tag, const char *code);

/* out_count에 개수를 채우고 code 문자열 포인터 배열을 반환한다.
 * 반환된 배열 자체는 호출자가 free해야 하지만, 안의 문자열 포인터들은
 * tagindex가 소유하므로 free하면 안 된다. */
char **tagindex_lookup(const tagindex_t *idx, const char *tag, size_t *out_count);
