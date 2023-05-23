#ifndef __SDL_EXCEPTION_H__
#define __SDL_EXCEPTION_H__
#include <string>
#include "Exception.h"

class SdlException : public Exception {
public:
    SdlException(const char* description);
};

#endif
