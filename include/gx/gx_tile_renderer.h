//
// gx_tile_renderer.h
// Harmony
//

#ifndef HARMONY_GX_TILE_RENDERER_H
#define HARMONY_GX_TILE_RENDERER_H

#include "gl_types.h"
#include "gl_using_shader.h"
#include "gl_using_vertices.h"
#include "game_level.h"
#include "game_terrain_layer.h"
#include "game_terrain_tile.h"

namespace harmony {
	namespace gx {
		// In charge of rendering terrain tiles.
		class tile_renderer {
		public:
			tile_renderer();
			
			void draw(game::level & level) const;
			void draw(game::terrain_layer & layer) const;
			
		private:
			gl::shader_program tile_shader_;
			
		private:
			class using_layer : public gl::using_vertices {
			public:
				using_layer(game::terrain_layer & layer, game::terrain_tile & initial_tile);
			};
		};
	}
}

#endif // HARMONY_GX_TILE_RENDERER_H
