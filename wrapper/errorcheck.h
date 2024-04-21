#pragma once

#ifdef DEBUG
#define GL_CALL(func) func;error_check();
#else
#define GL_CALL(func) func;
#endif

void error_check();