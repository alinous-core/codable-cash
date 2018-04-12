
#ifdef __SSE2__
#include "yescrypt-simd.h"
#else
#include "yescrypt-opt.h"
#warning "XXXXXXXXXXXXXXXXX yescrypt-opt.h"
#endif

