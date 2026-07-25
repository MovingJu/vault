# 이슈 로드맵

브랜치+PR로 하나씩. 이슈 번호 = 브랜치명(`issue-1-hashtable` 등) 그대로 써도 됨.

## MVP (여기까지 끝내면 완성)

### #1 해시테이블
`src/hashtable.c`, 테스트: `cabin test hashtable_test`

- [ ] djb2 또는 FNV-1a 해시 함수
- [ ] 체이닝으로 충돌 해결
- [ ] load factor 0.75 넘으면 capacity 2배로 리사이징 + 전체 재해싱
- [ ] `ht_set`은 같은 키 재대입시 값만 덮어쓰고 count 안 늘어남
- [ ] `ht_remove`는 지운 뒤 다시 지우면 0 반환

가장 먼저 풀 것 — `store.c`, `lru.c`가 전부 이 위에 얹힘.

### #2 Base62 짧은 코드
`src/shortcode.c`, 테스트: `cabin test shortcode_test`

- [ ] `0-9`(0~9) → `a-z`(10~35) → `A-Z`(36~61) 순서로 진법 변환
- [ ] `encode(0) == "0"`, `encode(61) == "Z"`, `encode(62) == "10"` (자리올림 확인)
- [ ] `decode`는 `encode`의 정확한 역함수

### #3 저장소
`src/store.c`, 테스트: `cabin test store_test`

- [ ] `vault_store_open`: 파일 없으면 생성, 있으면 읽어서 인덱스(해시테이블) 재구성
- [ ] `vault_store_append`: 로그 파일 끝에 레코드 이어쓰기
- [ ] **재시작 시뮬레이션이 핵심** — close 후 다시 open했을 때 count/find가 그대로여야 함
- [ ] 파일 포맷은 자유 (텍스트든 바이너리든), 단 "로그만으로 완전 복구" 계약은 필수

### #6 CLI 통합 (MVP 완성선)
`src/main.c` — 테스트는 따로 없음, 직접 실행해서 확인

- [ ] `vault add <url> [tags]` → store에 append, 발급된 code 출력
- [ ] `vault paste` → stdin 전체를 읽어 paste로 저장
- [ ] `vault get <code>` → 원본 출력, 없으면 에러 메시지 + 종료코드 1
- [ ] `vault list` → 전체 레코드 요약 출력

여기까지 되면 `cabin build && cabin run -- add https://example.com`으로 실제로 쓸 수 있는 버전.

---

## 확장 (여유 있을 때만 — MVP 끝나기 전엔 손대지 않기)

### #4 (확장) LRU 캐시
`src/lru.c`, 테스트: `cabin test lru_test`

- [ ] 해시테이블 + 이중연결리스트 조합 (LeetCode 146과 동일 구조)
- [ ] `lru_get` 성공시 해당 항목을 리스트 맨 앞(최근 사용)으로 이동
- [ ] capacity 초과시 리스트 맨 뒤(가장 오래 안 쓴 항목) 제거

`main.c`의 `get` 커맨드 앞단에 캐시로 끼워넣으면 실사용 효과도 확인 가능.

### #5 (확장) 태그 역색인
`src/tagindex.c`, 테스트: `cabin test tagindex_test`

- [ ] 해시테이블 위에 tag → code 동적 배열 구조 얹기
- [ ] `tagindex_lookup`은 없는 태그 조회시 count 0, NULL 아닌 값도 허용

### #7 (확장, 미스캐폴드) 미니 HTTP 서버
아직 헤더/스텁 없음 — 여기까지 다 끝나면 원시 소켓으로 직접 만들어보기.
`GET /s/<code>` 정도만 지원하는 최소 버전으로 시작 권장.
