#pragma once
#include <stddef.h>

/* 이슈 #2: Base62 짧은 코드 생성기
 *
 * - 내부 카운터(1부터 증가하는 unsigned long)를 62진법 문자열로 인코딩.
 * - 자리값 순서: 0-9(0~9), a-z(10~35), A-Z(36~61).
 * - encode(0) == "0", encode(61) == "Z", encode(62) == "10" (자리올림).
 * - decode는 encode의 역함수 — 디버깅/테스트/URL 파싱에 사용.
 */

void shortcode_encode(unsigned long counter, char *out, size_t out_size);
unsigned long shortcode_decode(const char *code);
