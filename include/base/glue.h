//
// glue.h
// Harmony
//

#ifndef HARMONY_GLUE_H
#define HARMONY_GLUE_H

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#ifdef __cplusplus
#define HARMONY_API extern "C"
#else
#define HARMONY_API extern
#endif

#define HARMONY_DRAW_COLLISION_NODES

#endif // HARMONY_GLUE_H
