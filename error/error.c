//
// Created by Piotr Krzysztof Wyrwas on 26.05.24.
//

#include "error.h"

enum XeomError xeom_err = 0;

void raise_error(enum XeomError error)
{
        xeom_err = error;
}

const char *xeom_string_error()
{
#define ERROR(code, string) case code: return string

        switch (xeom_err) {
                ERROR(XEOM_NO_ERROR, "No error");
                ERROR(XEOM_IMG_INVALID_DIMENSIONS, "Invalid Image dimensions");
                ERROR(XEOM_FOPEN_FAIL, "Could not open file");
                ERROR(XEOM_IMG_INVALID_FORMAT, "The provided format is invalid");
                ERROR(XEOM_IMG_UNSUPPORTED_FORMAT, "The provided format is not supported");
                ERROR(XEOM_IMG_OUT_OF_BOUNDS, "The provided Image coordinate is out of bounds");
                ERROR(XEOM_UNMATCHED_SIZES, "The output image dimensions must match the frame dimensions of the camera");
        }

#undef ERROR

        return "Invalid error";
}
