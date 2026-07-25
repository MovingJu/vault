# vault

개인용 링크·스니펫 저장소 + 단축 URL. C17 + [Cabin](https://github.com/cabinpkg/cabin)으로 빌드.

```
vault add https://example.com rust,cli   # 짧은 코드 발급
vault paste < snippet.rs                  # stdin을 paste로 저장
vault get <code>                          # 코드로 원본 조회
vault list                                 # 전체 목록
```

## 왜 C로 짜나

단순 CRUD 서비스지만, 뒷단을 라이브러리(SQLite 등) 없이 직접 짜서
자료구조/알고리즘을 실전처럼 써보는 게 목적. 각 모듈이 곧 하나의 개념 연습이다.

## 모듈 = 이슈

로드맵/체크리스트는 [Issues](https://github.com/MovingJu/vault/issues) 참고 (`mvp`/`stretch` 라벨로 구분).

| 모듈 | 자료구조/알고리즘 | 이슈 |
|---|---|---|
| `hashtable.c` | 체이닝 해시테이블, 리사이징 | #1 |
| `shortcode.c` | Base62 인코딩 (진법 변환) | #2 |
| `store.c` | append-only 로그, 재시작 복구 | #3 |
| `main.c` | CLI 통합 | #6 |
| `lru.c` (확장) | LRU 캐시 (해시테이블 + 이중연결리스트, LeetCode 146과 동일) | #4 |
| `tagindex.c` (확장) | 태그 역색인 (동적 배열) | #5 |
| HTTP 서버 (확장, 미스캐폴드) | 소켓 프로그래밍, 최소 HTTP 파싱 | #7 |

## 진행 방식

1. `cabin test`로 어떤 모듈이 아직 안 됐는지 확인 (지금은 전부 실패 — 정상)
2. Issues에서 다음 이슈 하나 골라서 브랜치 파고 해당 `src/*.c`만 구현
3. `cabin test`로 그 모듈 테스트만 통과하는지 확인
4. 반복. `#1 -> #2 -> #3 -> #6` 순서면 MVP 완성.

## MVP 완성선

**#1, #2, #3, #6**만 끝내면 실사용 가능한 CLI 버전 완성. `#4`, `#5`, `#7`은 여유 있을 때만.
