//
// plat_interface.h
// Harmony
//

#ifndef HARMONY_PLAT_INTERFACE_H
#define HARMONY_PLAT_INTERFACE_H

#include "glue.h"

// Returns the search path for scripts. The resulting buffer must be free'd.
HARMONY_API char * hplat_get_script_path();

// Reads the file at the given filename. The resulting buffer must be free'd.
HARMONY_API char * hplat_read_text_file(const char * filename);

// Reads the texture at the given filename. The resulting buffer must be free'd.
// The image dimensions and texture dimensions may be different, on platforms
// where textures must be powers of two.
HARMONY_API void * hplat_read_texture_file(const char * filename,
	size_t * image_width, size_t * image_height,
	size_t * texture_width, size_t * texture_height);

#endif // HARMONY_PLAT_INTERFACE_H
