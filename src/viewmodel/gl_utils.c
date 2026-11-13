#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

void ClearDepthOnly(void) {
    glClear(GL_DEPTH_BUFFER_BIT);
}