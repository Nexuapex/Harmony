local function T(name, ...)
	return terrain.create_tile(("tile/%s.png"):format(name), ...)
end

module "tile"

floor = {
	asphalt = T"floor/asphalt",
	boardwalk = T"floor/boardwalk",
	carpet = {
		red = T"floor/carpet red",
		white = T"floor/carpet white",
	},
	concrete_stairs = T"floor/concrete stairs",
	dirt = T"floor/dirt",
	dirt_road = {
		normal = T"floor/dirt road",
		rough = T"floor/dirt road rough",
	},
	grass = T"floor/grass",
	grating = T"floor/grating",
	grating_stairs = T"floor/grating stairs",
	metal = {
		normal = T"floor/metal",
		shiny = T"floor/metal shiny",
	},
	metal_stairs = T"floor/metal stairs",
	ocean = T"floor/ocean",
	sand = T"floor/sand",
	sidewalk = T"floor/sidewalk",
	tile = {
		black = T"floor/tile black",
		green = T"floor/tile green",
		white = T"floor/tile white",
		yellow = T"floor/tile yellow",
	},
	wood_stairs = T"floor/wood stairs",
}

wall = {
	brick = T"wall/brick",
	concrete = T"wall/concrete",
	glass = T"wall/glass",
	marble = {
		black = T"wall/marble black",
		blue = T"wall/marble blue",
		green = T"wall/marble green",
		purple = T"wall/marble purple",
		red = T"wall/marble red",
		white = T"wall/marble white",
	},
	stone = T"wall/stone",
	white = T"wall/white",
}
