//
// gx_actor_renderer.h
// Harmony
//

#ifndef HARMONY_GX_ACTOR_RENDERER_H
#define HARMONY_GX_ACTOR_RENDERER_H

#include "game_types.h"
#include "game_level.h"
#include "gx_sprite.h"
#include "gl_texture_cache.h"
#include "gl_shader_program.h"
#include "gl_using_shader.h"
#include "gl_using_vertices.h"

namespace harmony {
	namespace gx {
		// In charge of rendering actors.
		class actor_renderer {
		public:
			actor_renderer();
			
			void draw(game::elapsed_t elapsed, game::level & level,
				gl::texture_cache & tex_cache) const;
			void draw(game::elapsed_t elapsed, game::actor & actor,
				gl::texture_cache & tex_cache, gl::using_shader & active_shader)
				const;
			
		private:
			gl::shader_program sprite_shader_;
			
		private:
			
		private:
			class using_sprite : public gl::using_vertices {
			public:
				using_sprite(gx::sprite & sprite);
			};
		};
	}
}

#endif // HARMONY_GX_ACTOR_RENDERER_H
