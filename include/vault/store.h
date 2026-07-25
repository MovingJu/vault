#pragma once
#include <stddef.h>

/* 이슈 #3: append-only 로그 저장소 (Bitcask 스타일)
 *
 * 메모리에는 code -> (파일 오프셋, 길이)만 인덱싱한다 — 본문(content)은 메모리에
 * 상주하지 않고, 조회할 때마다 그 오프셋으로 파일을 읽어서 반환한다. 그래서
 * 레코드가 아무리 늘어도 인덱스 메모리는 "레코드 수 * 몇 바이트" 수준으로 유지된다
 * (본문 크기와 무관). 자주 조회되는 것만 메모리에 캐싱하고 싶으면 #4 LRU 캐시를
 * vault_store_find 앞단에 끼워넣으면 됨 — Riak의 Bitcask 스토리지 엔진이 쓰는
 * 것과 같은 구조.
 *
 * - vault_store_open: 로그 파일을 열고(없으면 생성), 기존 레코드를 스캔하며
 *   code -> offset 인덱스만 재구성한다 (본문은 안 읽음, 위치만 기록).
 * - vault_store_append: 새 레코드를 로그 파일 끝에 이어 쓰고, 그 오프셋을 인덱스에 기록.
 * - vault_store_find: 인덱스에서 offset을 찾아 그 위치를 디스크에서 읽어
 *   레코드를 새로 할당해 반환한다 — 호출자가 vault_record_free로 해제해야 함.
 * - 파일 포맷은 자유 — 탭/개행 구분 텍스트든, 길이-프리픽스 바이너리든 상관없음.
 *   단, "재시작해도 vault_store_open만으로 인덱스가 전부 복구된다"는 계약은 필수.
 * - 내부적으로 hashtable.c(이슈 #1)를 code -> offset 인덱스로 사용한다.
 */

typedef struct {
    char code[16];   /* 짧은 코드 */
    char kind;       /* 'L' = link, 'P' = paste */
    char *content;   /* URL 원본 또는 paste 본문 (malloc, vault_record_free로 해제) */
    char *tags;      /* 콤마로 구분된 태그, 없으면 NULL (malloc, vault_record_free로 해제) */
} vault_record_t;

typedef struct vault_store vault_store_t;

vault_store_t *vault_store_open(const char *path);
void vault_store_close(vault_store_t *store);

/* 0 = 성공, 음수 = 실패(예: 이미 존재하는 code) */
int vault_store_append(vault_store_t *store, const vault_record_t *record);

/* 없으면 NULL. 반환된 포인터는 호출자가 소유 — 다 쓰면 반드시 vault_record_free */
vault_record_t *vault_store_find(vault_store_t *store, const char *code);
void vault_record_free(vault_record_t *record);

size_t vault_store_count(const vault_store_t *store);
