#include "vault/shortcode.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main(void) {
    char buf[16];

    shortcode_encode(0, buf, sizeof(buf));
    assert(strcmp(buf, "0") == 0);

    shortcode_encode(9, buf, sizeof(buf));
    assert(strcmp(buf, "9") == 0);

    shortcode_encode(10, buf, sizeof(buf));
    assert(strcmp(buf, "a") == 0);

    shortcode_encode(35, buf, sizeof(buf));
    assert(strcmp(buf, "z") == 0);

    shortcode_encode(36, buf, sizeof(buf));
    assert(strcmp(buf, "A") == 0);

    shortcode_encode(61, buf, sizeof(buf));
    assert(strcmp(buf, "Z") == 0);

    shortcode_encode(62, buf, sizeof(buf));
    assert(strcmp(buf, "10") == 0);

    shortcode_encode(3843, buf, sizeof(buf)); /* 62*62 - 1 */
    assert(strcmp(buf, "ZZ") == 0);

    assert(shortcode_decode("0") == 0);
    assert(shortcode_decode("9") == 9);
    assert(shortcode_decode("a") == 10);
    assert(shortcode_decode("Z") == 61);
    assert(shortcode_decode("10") == 62);
    assert(shortcode_decode("ZZ") == 3843);

    printf("shortcode: all tests passed\n");
    return 0;
}
