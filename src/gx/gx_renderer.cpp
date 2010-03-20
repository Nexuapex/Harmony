//
// gx_renderer.cpp
// Harmony
//

#include <iostream>

#include "gx_interface.h"
#include "gl.h"
#include "game.h"

using namespace harmony;

// Resize the rendering viewport.
void hgx_reshape(hgame_ref game, size_t width, size_t height) {
	game::engine & self = *reinterpret_cast<game::engine *>(game);
	
	// Set up the camera projection.
	gl::set_viewport(width, height);
	gl::set_camera_projection(width, height);
	
	// Bias the camera so that it looks at the center of the viewport.
	self.set_camera_bias(ivec2(width / 2, height / 2));
	
	// Turn on blending.
	gl::set_blending_enabled(true);
}

// Perform the rendering.
void hgx_render(hgame_ref game, float elapsed) {
	game::engine & self = *reinterpret_cast<game::engine *>(game);
	
	// Clear the viewport.
	gl::clear();
	
	{
		// Set the camera position.
		vec2 pos = self.followed_actor()->position();
		icoord_t x = static_cast<icoord_t>(pos.x());
		icoord_t y = static_cast<icoord_t>(pos.y());
		gl::set_camera_position(ivec2(x, y) - self.camera_bias());
	}
	
	// Render the tiles of the current level.
	self.tile_renderer().draw(self.current_level());
	
	// Render the actors attached to the current level.
	self.actor_renderer().draw(elapsed, self.current_level(), self.texture_cache());
	
	// Report the last error occurring during the rendering.
	std::string err = gl::error();
	if (!err.empty())
		std::cerr << "hgx_render: " << err << std::endl;
}
