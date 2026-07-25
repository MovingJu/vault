#pragma once
#include <stddef.h>

/* 이슈 #3: append-only 로그 저장소
 *
 * - vault_store_open: 로그 파일을 열고(없으면 생성), 기존에 쓰여있던 레코드를
 *   전부 읽어서 내부 해시테이블 인덱스를 재구성한다 (재시작 복구).
 * - vault_store_append: 새 레코드를 로그 파일 끝에 이어 쓴다.
 * - 파일 포맷은 자유 — 탭/개행 구분 텍스트든, 길이-프리픽스 바이너리든 상관없음.
 *   단, "재시작해도 vault_store_open만으로 전부 복구된다"는 계약은 반드시 지킬 것.
 * - 내부적으로 hashtable.c(이슈 #1)를 code -> record 인덱스로 사용한다.
 */

typedef struct {
    char code[16];   /* 짧은 코드 */
    char kind;       /* 'L' = link, 'P' = paste */
    char *content;   /* URL 원본 또는 paste 본문 (malloc으로 소유) */
    char *tags;      /* 콤마로 구분된 태그, 없으면 NULL (malloc으로 소유) */
} vault_record_t;

typedef struct vault_store vault_store_t;

vault_store_t *vault_store_open(const char *path);
void vault_store_close(vault_store_t *store);

/* 0 = 성공, 음수 = 실패(예: 이미 존재하는 code) */
int vault_store_append(vault_store_t *store, const vault_record_t *record);

/* 없으면 NULL. 반환된 포인터는 store가 소유 — free하지 말 것 */
const vault_record_t *vault_store_find(vault_store_t *store, const char *code);

size_t vault_store_count(const vault_store_t *store);
