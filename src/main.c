#include <stdio.h>
#include <string.h>
#include "vault/hashtable.h"
#include "vault/shortcode.h"
#include "vault/store.h"

/* 이슈 #6: CLI 통합 (MVP 마무리 지점)
 *
 *   vault add <url> [tag1,tag2,...]   링크 저장, 짧은 코드 출력
 *   vault paste                        stdin 전체를 paste로 저장
 *   vault get <code>                   코드로 원본 조회
 *   vault list                         저장된 전체 목록
 *
 * 대략적인 흐름:
 *   1) vault_store_open("vault.log")
 *   2) 다음 카운터 값을 shortcode_encode로 인코딩해 code 생성
 *      (카운터는 vault_store_count()+1 정도로 단순하게 시작해도 됨)
 *   3) vault_record_t 채워서 vault_store_append
 *   4) 생성된 code를 stdout에 출력
 *   5) vault_store_close
 */

static void print_usage(const char *prog) {
    fprintf(stderr, "usage: %s <add|paste|get|list> [args...]\n", prog);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    const char *cmd = argv[1];

    if (strcmp(cmd, "add") == 0) {
        /* TODO(#6): argv[2] = url, argv[3] = comma-separated tags (optional) */
        fprintf(stderr, "add: not implemented yet\n");
    } else if (strcmp(cmd, "paste") == 0) {
        /* TODO(#6): stdin 전체를 읽어서 paste로 저장 */
        fprintf(stderr, "paste: not implemented yet\n");
    } else if (strcmp(cmd, "get") == 0) {
        /* TODO(#6): argv[2] = code */
        fprintf(stderr, "get: not implemented yet\n");
    } else if (strcmp(cmd, "list") == 0) {
        /* TODO(#6): 전체 레코드 나열 */
        fprintf(stderr, "list: not implemented yet\n");
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
