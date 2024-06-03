//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#ifndef XEOM_ERROR_H
#define XEOM_ERROR_H

#include <inttypes.h>

enum XeomError : uint16_t {
        XEOM_NO_ERROR = 0,

        XEOM_IMG_INVALID_DIMENSIONS,
        XEOM_IMG_INVALID_FORMAT,
        XEOM_IMG_UNSUPPORTED_FORMAT,
        XEOM_IMG_OUT_OF_BOUNDS,
        XEOM_IMG_AVG_UNMATCHED_SIZES,

        XEOM_UNMATCHED_SIZES,

        XEOM_FOPEN_FAIL,
};

extern enum XeomError xeom_err;

void raise_error(enum XeomError error);

const char *xeom_string_error();

#endif //XEOM_ERROR_H
