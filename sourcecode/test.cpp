#include "error.hpp"

void Error::note(const char *errMsg, ...)
{
    va_list va;
    va_start(va, errMsg);

    fprintf(stderr,
            ERROR_NOTE_STYLE "%10s:" ERROR_RESET " ", "note");
    vfprintf(stderr, errMsg, va);
    fputc('\n', stderr); // 改行

    va_end(va);
}

