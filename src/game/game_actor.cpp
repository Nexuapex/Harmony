//
// game_actor.cpp
// Harmony
//

#include "game_actor.h"
#include "ai_agent.h"
#include "game_level.h"
#include "game_lattice.h"
#include "geom_collision.h"
#include "geom_shape.h"
#include "geom_rect.h"

namespace harmony {
	game::actor::actor() : heading_(0)
	{
		// DEMO: Default collision shape.
		geom::shape_ref collision_shape(new geom::rect(-18, -18, 36, 36));
		set_collision_shape(collision_shape);
	}
	
	game::actor::~actor() {}
	
	bool game::actor::is_actor() const {
		return true;
	}
	
	vec2 game::actor::velocity() const {
		return velocity_;
	}
	
	void game::actor::set_velocity(const vec2 & new_velocity) {
		velocity_ = new_velocity;
	}
	
	game::angle_t game::actor::heading() const {
		return heading_;
	}
	
	void game::actor::set_heading(angle_t new_heading) {
		heading_ = new_heading;
	}
	
	geom::shape_ref game::actor::collision_shape() const {
		return collision_shape_;
	}
	
	void game::actor::set_collision_shape(const geom::shape_ref & new_shape) {
		collision_shape_ = new_shape;
		update_collision_nodes(true);
	}
	
	ai::agent_ref game::actor::agent() const {
		return agent_;
	}
	
	void game::actor::set_agent(const ai::agent_ref & new_agent) {
		agent_ = new_agent;
	}
	
	gx::sprite_ref game::actor::sprite() const {
		return sprite_;
	}
	
	void game::actor::set_sprite(const gx::sprite_ref & new_sprite) {
		sprite_ = new_sprite;
	}
	
	gx::sprite_state & game::actor::sprite_state() {
		return sprite_state_;
	}
	
	const gx::sprite_state & game::actor::sprite_state() const {
		return sprite_state_;
	}
	
	void game::actor::step(elapsed_t elapsed) {
		// Invoke AI for this step.
		if (agent_) agent_->step(boost::dynamic_pointer_cast<actor>(shared_from_this()), elapsed);
		
		// Create the collision object for this movement.
		geom::collision collision(
			collision_shape_->translate(static_cast<ivec2>(position())),
			velocity_ * (elapsed / 1000.0f)
		);
		
		// Actually move the actor.
		mark::set_position(position() + collision.displacement());
	}
	
	void game::actor::set_position(const level_ref & new_level, const vec2 & new_position) {
		// Retain the reference to the old level.
		level_ref old_level = level();
		
		// Call mark::set_position().
		mark::set_position(new_level, new_position);
		
		// Update the collision nodes. The size of the list may need to change
		// if the level has changed as part of this change in position, because
		// the lattice size of the new level may differ.
		update_collision_nodes(new_level != old_level, old_level);
	}
	
	ivec2 game::actor::collision_nodes_offset(lattice & lattice) const {
		const ivec2 pos = static_cast<ivec2>(position());
		const size_t ns = lattice.node_size();
		return ivec2((pos.x() % ns + ns) % ns, (pos.y() % ns + ns) % ns);
	}
	
	void game::actor::update_collision_nodes_shape(boost::scoped_array<collision_node> & old_nodes)
	{
		if (exists_in_level() && collision_shape_) {
			// Get a reference to the lattice for the current level.
			lattice & lattice = *(level()->lattice());
			
			// Get the new rect for the nodes.
			geom::rect bounds = collision_shape_->bounding_rect();
			geom::rect new_rect = geom::cell_aligned_bounding_rect(bounds, lattice.node_size());
			
			// Get the desired size of the array.
			ucoord_t new_size = new_rect.area();
			
			// Check if a resize is needed.
			if (new_size != collision_nodes_rect_.area()) {
				// Allocate a new array of nodes.
				old_nodes.reset(new collision_node[new_size]);
				
				// Hook each node up to this actor.
				actor_ref self = boost::dynamic_pointer_cast<actor>(shared_from_this());
				for (unsigned index = 0; index < new_size; ++index) {
					old_nodes[index].set_actor(self);
				}
				
				// Swap in the new array.
				collision_nodes_.swap(old_nodes);
			}
			
			// Update the rect.
			collision_nodes_rect_ = new_rect;
		} else {
			// No longer in a level or has no shape. Need to get rid of the
			// current set of nodes.
			old_nodes.reset();
			collision_nodes_.swap(old_nodes);
			
			// Clear the rect.
			collision_nodes_rect_ = geom::rect();
		}
	}
	
	void game::actor::update_collision_nodes(bool should_update_shape, const level_ref & old_level) {
		// Keep track of the current node rect.
		geom::rect old_rect = collision_nodes_rect_;
		
		// Storage for the old set of collision nodes, if needed.
		boost::scoped_array<collision_node> old_nodes;
		
		if (should_update_shape) {
			// If the caller thinks that the shape of the nodes may have
			// changed, then check that. The old list of nodes, if any, will be
			// returned by reference.
			update_collision_nodes_shape(old_nodes);
			
			if (old_nodes) {
				// Get a reference to the lattice for the level in question.
				lattice & lattice = *((old_level) ? old_level : level())->lattice();
				
				// All old active nodes should be listed as newly inactive.
				for (ivec2 cell; cell.uy() < old_rect.height(); cell.incr_y()) {
					for (cell.set_x(0); cell.ux() < old_rect.width(); cell.incr_x()) {
						// Get the node.
						collision_node & node = collision_node_at(cell, old_nodes, old_rect);
						
						if (node.active()) {
							// Node is now obsolete (inactive).
							lattice.set_collision_node_active(node, false, ivec2());
						}
					}
				}
			}
		}
		
		if (collision_nodes_) {
			// Get a reference to the lattice for the current level.
			lattice & lattice = *(level()->lattice());
			
			// In order to avoid translating arbitrary shapes (and thus causing
			// frequent allocations), create an offset that moves the origin
			// point of each collision node.
			const ivec2 pos = static_cast<ivec2>(position());
			const ivec2 offset = collision_nodes_offset(lattice);
			
			// Search through all current nodes.
			for (ivec2 cell; cell.uy() < collision_nodes_rect_.height(); cell.incr_y()) {
				for (cell.set_x(0); cell.ux() < collision_nodes_rect_.width(); cell.incr_x()) {
					// Get the node.
					collision_node & node = collision_node_at(cell);
					
					// Get the rectangle that corresponds to the node.
					geom::rect node_rect = lattice.node_rect(cell + collision_nodes_rect_.origin);
					node_rect.origin -= offset;
					
					// Update the lattice coordinate for this node.
					ivec2 lattice_cell = lattice.node_at(pos + node_rect.origin);
					
					// Update the node in the lattice.
					bool should_be_active = collision_shape_->intersects(node_rect);
					lattice.set_collision_node_active(node, should_be_active, lattice_cell);
				}
			}
		}
	}
	
#ifdef HARMONY_DRAW_COLLISION_NODES
	ivec2 game::actor::collision_nodes_size() const {
		return collision_nodes_rect_.size;
	}
	
	bool game::actor::collision_node_active_at(const ivec2 & cell) const {
		return collision_node_at(cell).active();
	}
	
	geom::rect game::actor::collision_node_rect_at(const ivec2 & cell) const {
		lattice & lattice = *(level()->lattice());
		geom::rect node_rect = lattice.node_rect(cell + collision_nodes_rect_.origin);
		node_rect.origin = lattice.node_at(
			static_cast<ivec2>(position())
			+ node_rect.origin
			- collision_nodes_offset(lattice)
		) * lattice.node_size();
		return node_rect;
	}
#endif // HARMONY_DRAW_COLLISION_NODES
}
