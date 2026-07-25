#include "vault/shortcode.h"

void shortcode_encode(unsigned long counter, char *out, size_t out_size) {
    (void)counter;
    if (out_size > 0) {
        out[0] = '\0';
    }
    /* TODO(#2) */
}

unsigned long shortcode_decode(const char *code) {
    (void)code;
    return 0; /* TODO(#2) */
}
