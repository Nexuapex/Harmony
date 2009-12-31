//
// gl_library.h
// Harmony
//

#ifndef HARMONY_GL_LIBRARY_H
#define HARMONY_GL_LIBRARY_H

#include "glee.h"

#ifdef HARMONY_MAC
#import <OpenGL/OpenGL.h>
#import <OpenGL/glu.h>
#endif

#ifdef HARMONY_WIN
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#endif

#endif // HARMONY_GL_LIBRARY_H
