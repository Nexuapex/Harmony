//
// gx_actor_renderer.cpp
// Harmony
//

#include <string>

#include "gx_actor_renderer.h"
#include "game_actor.h"
#include "gl.h"

namespace harmony {
	gx::actor_renderer::actor_renderer() : sprite_shader_("actor.vs", "actor.fs") {}
	
	void gx::actor_renderer::draw(game::elapsed_t elapsed, game::level & level,
		gl::texture_cache & tex_cache) const
	{
		// Activate the shader.
		gl::using_shader active_shader(sprite_shader_);
		
		// DEMO: Transparency uniforms.
		gl::using_uniform<bool> use_transparent_color(
			sprite_shader_, "use_transparent_color", true
		);
		gl::using_uniform<gl::color> transparent_color(
			sprite_shader_, "transparent_color", gl::color(1.0f, 1.0f, 1.0f)
		);
		
		// Iterate through all actors attached to the level.
		for (game::level::actor_iterator iter(level); iter; ++iter) {
			game::actor_ref actor = *iter;
			
			// Draw any actors that have an associated sprite.
			if (actor->sprite())
				draw(elapsed, *actor, tex_cache);
		}
	}
	
	void gx::actor_renderer::draw(game::elapsed_t elapsed, game::actor & actor,
		gl::texture_cache & tex_cache) const
	{
		// Make rendering time elapsed for the actor.
		actor.sprite_state().step(elapsed);
		
		// Get the actor's sprite.
		gx::sprite & sprite = *actor.sprite();
		
		// Get the actor's desired texture.
		std::string path = actor.sprite_state().path_for(sprite);
		
		// Load said texture and inform the sprite of it.
		gl::texture_ref texture = tex_cache.get(path);
		sprite.touch(texture);
		
		// Activate the sprite vertices.
		using_sprite active_sprite(sprite);
		
		// Set up the shader.
		gl::using_uniform<gl::texture_ref> sprite_texture(sprite_shader_, "sprite", texture);
		
		// Translate to the actor's position.
		gl::using_translation translation(actor.position());
		
		// Rotate to match the actor's heading. All sprites need an additional
		// rotation to account for the image's orientation.
		gl::using_rotation rotation(actor.heading() - 90.0f);
		
		// Actually draw the sprite.
		active_sprite.draw(GL_QUADS);
	}
	
	gx::actor_renderer::using_sprite::using_sprite(gx::sprite & sprite)
		: using_vertices(4, 2, sprite.vertices(), sprite.tex_coords()) {}
}
