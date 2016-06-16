#ifndef HAVE_DEFINED_ERROR_CODE_H
#define HAVE_DEFINED_ERROR_CODE_H

enum err_code {
    NO_ERR = 0,
    ERR_INVALID_PARAM = 1,
    ERR_NO_FRAME      = 2,
    ERR_IDX_OVERFLOW  = 3,
    ERR_ARRAY_FULL    = 4,

};

#define INVALID_PARAM "Invalid parameters.\n"
#define NO_FRAME      "No free physcial frame available.\n"
#define IDX_OVERFLOW  "Index reach the limitation.\n"
#define ARRAY_FULL    "Array is full.\n"

#define IDX_INVALID   0xffffffffu

#endif

