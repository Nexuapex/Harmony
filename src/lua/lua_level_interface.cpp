//
// lua_level_interface.cpp
// Harmony
//

#include "lua_level.h"
#include "lua_vector.h"
#include "lua_mark.h"
#include "game.h"

namespace harmony {
	namespace lua {
		static void load_terrain_element(const engine & engine,
			const game::level_ref & level, game::terrain_layer & layer,
			const ivec2 & cell)
		{
			if (!lua_isnil(engine, -1)) {
				// Get the tile, if it is a tile.
				game::terrain_tile_ref tile = lua::to_terrain_tile(engine, -1);
				
				if (tile) {
					// Insert the tile into the layer.
					layer.set_tile(cell, tile);
				} else {
					// Get the position that any mark will occupy.
					vec2 position = layer.cell_center(cell);
					
					// Get the actor, if it is an actor.
					game::actor_ref actor = lua::to_actor(engine, -1);
					
					if (actor) {
						// Insert the actor into the level.
						actor->set_position(level, position);
					} else {
						// Get the mark, if it is a mark.
						game::mark_ref mark = lua::to_mark(engine, -1);
						
						if (mark) {
							// Insert the mark into the level.
							mark->set_position(level, position);
						}
					}
				}
			}
			
			// empty stack
			lua_pop(engine, 1);
		}
		
		static void load_terrain_layers(const engine & engine, const game::level_ref & level) {
			// <layer table> <origin>
			lua_getfield(engine, -1, "origin");
			ivec2 origin = lua::to_ivec2(engine, -1);
			
			// <layer table>
			lua_pop(engine, 1);
			
			// <layer table> <width>
			lua_getfield(engine, -1, "width");
			game::size_t width = lua_tointeger(engine, -1);
			
			// <layer table>
			lua_pop(engine, 1);
			
			// <layer table> <height>
			lua_getfield(engine, -1, "height");
			game::size_t height = lua_tointeger(engine, -1);
			
			// <layer table>
			lua_pop(engine, 1);
			
			// <layer table> <tile size>
			lua_getfield(engine, -1, "tile_size");
			game::size_t tile_size = lua_tointeger(engine, -1);
			
			// <layer table>
			lua_pop(engine, 1);
			
			// Create the stack of layers.
			std::vector<game::terrain_layer_ref> layers;
			
			// Create the initial terrain layer.
			ivec2 size(width, height);
			game::terrain_layer_ref layer(new game::terrain_layer(origin, size, tile_size));
			layers.push_back(layer);
			
			for (ivec2 cell; cell.uy() < height; cell.incr_y()) {
				// <layer table> <index>
				lua_pushinteger(engine, cell.y() + 1);
				
				// <layer table> <row table>
				lua_gettable(engine, -2);
				
				for (cell.set_x(0); cell.ux() < width; cell.incr_x()) {
					// <layer table> <row table> <index>
					lua_pushinteger(engine, cell.x() + 1);
					
					// <layer table> <row table> <tile>
					lua_gettable(engine, -2);
					
					if (lua_istable(engine, -1)) {
						// Get the number of elements in the tile table.
						size_t depth = lua_objlen(engine, -1);
						
						// Create new layers as needed.
						for (unsigned index = layers.size(); index < depth; ++index) {
							game::terrain_layer_ref layer(
								new game::terrain_layer(origin, size, tile_size)
							);
							layers.push_back(layer);
						}
						
						for (unsigned index = 0; index < depth; ++index) {
							// <layer table> <row table> <tile> <index>
							lua_pushinteger(engine, index + 1);
							
							// <layer table> <row table> <tile> <tile element>
							lua_gettable(engine, -2);
							
							// <layer table> <row table> <tile>
							load_terrain_element(engine, level, *layers[index], cell);
						}
						
						// <layer table> <row table>
						lua_pop(engine, 1);
					} else {
						// <layer table> <row table>
						load_terrain_element(engine, level, *layer, cell);
					}
				}
				
				// <layer table>
				lua_pop(engine, 1);
			}
			
			// empty stack
			lua_pop(engine, 1);
			
			// Insert the new layers.
			for (unsigned index = 0; index < layers.size(); ++index)
				level->add_terrain_layer(layers[index]);
		}
	} // namespace lua
	
	game::level_ref lua::load_level(const engine & engine, const std::string & filename) {
		// Create the new level.
		game::level_ref level(new game::level);
		
		// <level table>
		lua_createtable(engine, 0, 1);
		
		// <level table> <layers table>
		lua_newtable(engine);
		
		// <level table>
		lua_setfield(engine, -2, "layers");
		
		// <level table> <level table>
		lua_pushvalue(engine, -1);
		
		// <level table>
		engine.run_script("loading level", "level/" + filename, 1, 0);
		
		// <level table> <layers table>
		lua_getfield(engine, -1, "layers");
		
		// Get the number of layers.
		size_t count = lua_objlen(engine, -1);
		
		for (unsigned index = 1; index <= count; ++index) {
			// <level table> <layers table> <index>
			lua_pushinteger(engine, index);
			
			// <level table> <layers table> <layer table>
			lua_gettable(engine, -2);
			
			// <level table> <layers table>
			load_terrain_layers(engine, level);
		}
		
		// empty stack
		lua_pop(engine, 2);
		
		// Return the new level.
		return level;
	}
}
