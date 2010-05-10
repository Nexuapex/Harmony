//
// game_terrain_layer.cpp
// Harmony
//

#include "game_terrain_layer.h"

namespace harmony {
	static gl::index_t rotated_indices[8][4] = {
		{0, 1, 2, 3}, // Normal.
		{1, 2, 3, 0}, // Rotate right.
		{2, 3, 0, 1}, // Rotate 180.
		{3, 0, 1, 2}, // Rotate left.
		{3, 2, 1, 0}, // Flip.
		{2, 1, 0, 3}, // Flip and rotate left.
		{1, 0, 3, 2}, // Flip and rotate 180.
		{0, 3, 2, 1}  // Flip and rotate right.
	};
	
	game::terrain_layer::terrain_layer(const ivec2 & origin,
		const ivec2 & size, game::size_t tile_size)
		: origin_(origin), size_(size), tile_size_(tile_size)
		, tiles_(new terrain_tile_ref[size.x() * size.y()])
		, atlas_(tile_size), dirty_(true) {}
	
	void game::terrain_layer::set_tile(const ivec2 & cell, const terrain_tile_ref & new_tile) {
		dirty_ = true;
		(*this)[cell] = new_tile;
	}
	
	ivec2 game::terrain_layer::cell_origin(const ivec2 & cell) const {
		return cell * tile_size_;
	}
	
	vec2 game::terrain_layer::cell_center(const ivec2 & cell) const {
		float size = static_cast<float>(tile_size_);
		return static_cast<vec2>(cell) * size + vec2(size / 2.0f, size / 2.0f);
	}
	
	ivec2 game::terrain_layer::cell_max(const ivec2 & cell) const {
		return (cell + ivec2(1, 1)) * tile_size_;
	}
	
	geom::irect game::terrain_layer::cell_rect(const ivec2 & cell) const {
		return geom::irect(cell_origin(cell), ivec2(tile_size_, tile_size_));
	}
	
	ivec2 game::terrain_layer::first_nonempty_cell(const geom::irect & region) const {
		const icoord_t x_max = region.x2(), y_max = region.y2();
		
		for (ivec2 cell = region.origin; cell.y() < y_max; cell.incr_y())
			for (cell.set_x(region.x1()); cell.x() < x_max; cell.incr_x())
				if ((*this)[cell])
					return cell;
		
		return ivec2(-1, -1);
	}
	
	game::size_t game::terrain_layer::tile_size() const {
		return tile_size_;
	}
	
	const game::terrain_layer::buffer_object &
		game::terrain_layer::rendering_object(gx::atlas_renderer & intermediate_renderer)
	{
		if (dirty_) {
			for (ivec2 cell; cell.y() < size_.y(); cell.incr_y())
				for (cell.set_x(0); cell.x() < size_.x(); cell.incr_x())
					if ((*this)[cell])
						atlas_.add_texture((*this)[cell]->texture());
			
			atlas_.load(intermediate_renderer);
			buffer_object_.prepare(*this);
			dirty_ = false;
		}
		
		return buffer_object_;
	}
	
	void game::terrain_layer::tile_vertex::set_tex_coords(const gl::float_t (& coords)[2]) {
		s = coords[0];
		t = coords[1];
	}
	
	void game::terrain_layer::buffer_object::prepare(terrain_layer & layer) {
		// Useful sizes.
		ivec2 size = layer.size();
		gl::size_t count = size.x() * size.y() * 4;
		
		// Create the arrays that will contain the necessary data.
		tile_vertex * vertices = new tile_vertex[count];
		gl::index_t * indices = new gl::index_t[count];
		
		// Keep a scoped reference to the original pointers.
		boost::scoped_array<tile_vertex> vertex_data(vertices);
		boost::scoped_array<gl::index_t> index_data(indices);
		
		// Start an accurate count.
		count = 0;
		
		// Populate the arrays.
		for (ivec2 cell; cell.y() < size.y(); cell.incr_y()) {
			for (cell.set_x(0); cell.x() < size.x(); cell.incr_x()) {
				if (layer[cell]) {
					// Obtain a reference to the tile.
					const terrain_tile_ref & tile = layer[cell];
					
					if (tile) {
						// Useful quantities.
						size_t size = layer.tile_size();
						ivec2 vert = cell * size;
						
						// Populate the vertex coordinates.
						vertices[0].x = vert.fx();        vertices[0].y = vert.fy();
						vertices[1].x = vert.fx();        vertices[1].y = vert.fy() + size;
						vertices[2].x = vert.fx() + size; vertices[2].y = vert.fy() + size;
						vertices[3].x = vert.fx() + size; vertices[3].y = vert.fy();
						
						// Populate the remaining attributes.
						for (unsigned vertex = 0; vertex < 4; ++vertex) {
							// Texture coordinates.
							vertices[vertex].set_tex_coords(
								tile->texture()->tex_coords()[
									rotated_indices[tile->rotation()][vertex]
								]
							);
							
							// Index coordinates.
							indices[vertex] = static_cast<gl::index_t>(indices - index_data.get() + vertex);
						}
						
						// Advance to the next set of elements.
						vertices += 4;
						indices += 4;
						count += 4;
					}
				}
			}
		}
		
		// Define the vertex buffer layout.
		gl::buffer_layout_ref vertex_layout(
			new gl::buffer_layout(
				gl::buffer_type_vertex,
				gl::buffer_mutability_static,
				gl::buffer_usage_draw
			)
		);
		vertex_layout->set_attribute(
			gl::buffer_attribute_coord, true,
			GL_FLOAT, 2, offsetof(tile_vertex, x)
		);
		vertex_layout->set_attribute(
			gl::buffer_attribute_tex_coord, true,
			GL_FLOAT, 2, offsetof(tile_vertex, s)
		);
		
		// Define the index buffer layout.
		gl::buffer_layout_ref index_layout(
			new gl::buffer_layout(
				gl::buffer_type_index,
				gl::buffer_mutability_static,
				gl::buffer_usage_draw
			)
		);
		
		// Create the new buffers.
		vertex_buffer_ref vertex_buffer_ptr(new vertex_buffer(vertex_layout, vertex_data.get(), count));
		index_buffer_ref index_buffer_ptr(new index_buffer(index_layout, index_data.get(), count));
		vertices_ = vertex_buffer_ptr;
		indices_ = index_buffer_ptr;
	}
}
