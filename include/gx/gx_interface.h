//
// gx_interface.h
// Harmony
//

#ifndef HARMONY_GX_INTERFACE_H
#define HARMONY_GX_INTERFACE_H

#include "glue.h"
#include "game_interface.h"

HARMONY_API void hgx_reshape(hgame_ref game, size_t width, size_t height);
HARMONY_API void hgx_render(hgame_ref game, float elapsed);

#endif // HARMONY_GX_INTERFACE_H
