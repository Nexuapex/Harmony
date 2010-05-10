//
// gx_actor_renderer.cpp
// Harmony
//

#include <string>

#include "gx_actor_renderer.h"
#include "game_actor.h"
#include "game_level.h"
#include "gx_sprite.h"
#include "geom_rect.h"
#include "gl.h"

namespace harmony {
	gx::actor_renderer::actor_renderer() : sprite_shader_("actor.vs", "actor.fs") {}
	
	void gx::actor_renderer::draw(game::elapsed_t elapsed, game::level & level,
		gx::texture_cache & tex_cache) const
	{
#ifdef HARMONY_DRAW_COLLISION_NODES
		// Draw all the actors' collision nodes.
		draw_collision_nodes(level);
#endif // HARMONY_DRAW_COLLISION_NODES
		
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
		for (game::level::actor_iterator iter = level.begin(); iter != level.end(); ++iter) {
			game::actor_ref actor = *iter;
			
			// Draw any actors that have an associated sprite.
			if (actor->sprite())
				draw(elapsed, *actor, tex_cache);
		}
	}
	
	void gx::actor_renderer::draw(game::elapsed_t elapsed, game::actor & actor,
		gx::texture_cache & tex_cache) const
	{
		// Make rendering time elapse for the actor.
		actor.sprite_state().step(elapsed);
		
		// Get the actor's sprite.
		gx::sprite & sprite = *actor.sprite();
		
		// Get the actor's desired texture.
		std::string path = actor.sprite_state().path_for(sprite);
		
		// Load said texture and inform the sprite of it.
		gx::texture_ref texture = tex_cache.get(path);
		sprite.touch(texture);
		
		// Activate the sprite vertices.
		using_sprite active_sprite(sprite);
		
		// Set up the shader.
		gl::using_uniform<gl::texture_ref> sprite_texture(sprite_shader_, "sprite", texture->source());
		
		// Translate to the actor's position.
		gl::using_translation translation(actor.position());
		
		// Rotate to match the actor's heading. All sprites need an additional
		// rotation to account for the image's orientation.
		gl::using_rotation rotation(actor.heading() - 90.0f);
		
		// Actually draw the sprite.
		active_sprite.draw(GL_QUADS);
	}
	
#ifdef HARMONY_DRAW_COLLISION_NODES
	void gx::actor_renderer::draw_collision_nodes(game::level & level) const {
		// Iterate through all actors attached to the level.
		for (game::level::actor_iterator iter = level.begin(); iter != level.end(); ++iter) {
			game::actor_ref actor = *iter;
			
			// Iterate through all the actor's collision nodes.
			const ivec2 size = actor->collision_nodes_size();
			for (ivec2 cell; cell.y() < size.y(); cell.incr_y()) {
				for (cell.set_x(0); cell.x() < size.x(); cell.incr_x()) {
					if (actor->collision_node_active_at(cell)) {
						// Get the node rect.
						geom::rect node = actor->collision_node_rect_at(cell);
						
						// Draw the rect using immediate mode.
						glColor4f(0.0f, 0.0f, 1.0f, 0.4f);
						glBegin(GL_QUADS);
						{
							glVertex2i(node.x1(), node.y2());
							glVertex2i(node.x2(), node.y2());
							glVertex2i(node.x2(), node.y1());
							glVertex2i(node.x1(), node.y1());
						}
						glEnd();
					}
				}
			}
			
			// Draw the actor's collision rect (if it is a rect).
			if (const geom::rect * r = dynamic_cast<const geom::rect *>(actor->collision_shape().get())) {
				// Translate the collision rect to the actor's position.
				geom::rect c = *r;
				c.origin += static_cast<ivec2>(actor->position());
				
				// Draw the rect using immediate mode.
				glColor4f(1.0f, 0.0f, 0.0f, 0.6f);
				glBegin(GL_QUADS);
				{
					glVertex2i(c.x1(), c.y2());
					glVertex2i(c.x2(), c.y2());
					glVertex2i(c.x2(), c.y1());
					glVertex2i(c.x1(), c.y1());
				}
				glEnd();
			}
		}
	}
#endif // HARMONY_DRAW_COLLISION_NODES
	
	gx::actor_renderer::using_sprite::using_sprite(gx::sprite & sprite)
		: using_vertices(4, 2, sprite.vertices(), sprite.tex_coords()) {}
}
