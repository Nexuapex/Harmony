//
// gx_tile_renderer.h
// Harmony
//

#ifndef HARMONY_GX_TILE_RENDERER_H
#define HARMONY_GX_TILE_RENDERER_H

#include "game_level.h"
#include "game_terrain_layer.h"
#include "game_terrain_tile.h"
#include "geom_rect.h"
#include "gl_types.h"
#include "gl_using_buffer.h"
#include "gl_using_shader.h"
#include "gl_using_translation.h"
#include "gl_using_uniform.h"
#include "gl_using_vertices.h"

namespace harmony {
	namespace gx {
		// The subsystem in charge of rendering terrain tiles.
		class tile_renderer {
		public:
			tile_renderer();
			
			void draw(gx::atlas_renderer & intermediate_renderer, game::level & level) const;
			void draw(gx::atlas_renderer & intermediate_renderer, game::terrain_layer & layer) const;
			
		private:
			gl::shader_program tile_shader_;
			
		private:
			struct using_layer {
				gl::using_shader shader;
				gl::using_buffer<game::terrain_layer::tile_vertex> vertex_buffer;
				gl::using_buffer<gl::index_t> index_buffer;
				gl::using_translation translation;
				gl::using_uniform<vec2> extent;
				gl::using_uniform<gl::texture_ref> texture;
				gl::using_uniform<gl::int_t> rotation;
				
				using_layer(const gl::shader_program & shader,
					game::terrain_layer & layer,
					const game::terrain_layer::buffer_object & rendering_object,
					const game::terrain_tile & initial_tile);
				
				void draw();
			};
		};
	}
}

#endif // HARMONY_GX_TILE_RENDERER_H
