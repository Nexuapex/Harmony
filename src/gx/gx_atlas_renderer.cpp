//
// gx_atlas_renderer.cpp
// Harmony
//

#include "gx_atlas_renderer.h"

namespace harmony {
	gx::atlas_renderer::atlas_renderer() : shader_("atlas.vs", "atlas.fs") {}
	
	const gl::shader_program & gx::atlas_renderer::shader() const {
		return shader_;
	}
	
	const gl::offscreen_renderer & gx::atlas_renderer::renderer() const {
		return renderer_;
	}
}
