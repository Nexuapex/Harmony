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
			
			void draw(const geom::rect & viewport, game::level & level) const;
			void draw(const geom::rect & viewport, game::terrain_layer & layer) const;
			
		private:
			gl::shader_program tile_shader_;
			
		private:
			class using_layer : public gl::using_shader, public gl::using_vertices {
			public:
				using_layer(const gl::shader_program & shader,
					const game::terrain_layer & layer,
					const game::terrain_tile & initial_tile);
				
			private:
				gl::using_translation translation_;
				gl::using_uniform<vec2> tile_ratio_;
			};
		};
	}
}

#endif // HARMONY_GX_TILE_RENDERER_H
