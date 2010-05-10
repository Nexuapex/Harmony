local function T(name, ...)
	return terrain.create_tile(("tile/%s.png"):format(name), ...)
end

local function F(name, ...)
	return T(name, "passable", ...)
end

local function W(name, ...)
	return T(name, "impassable", ...)
end

module "tile"

floor = {
	asphalt = F"floor/asphalt",
	boardwalk = F"floor/boardwalk",
	carpet = {
		red = F"floor/carpet red",
		white = F"floor/carpet white",
	},
	concrete_stairs = F"floor/concrete stairs",
	dirt = F"floor/dirt",
	dirt_road = {
		normal = F"floor/dirt road",
		rough = F"floor/dirt road rough",
	},
	grass = F"floor/grass",
	grating = F"floor/grating",
	grating_stairs = F"floor/grating stairs",
	metal = {
		normal = F"floor/metal",
		shiny = F"floor/metal shiny",
	},
	metal_stairs = F"floor/metal stairs",
	ocean = F"floor/ocean",
	sand = F"floor/sand",
	sidewalk = F"floor/sidewalk",
	tile = {
		black = F"floor/tile black",
		green = F"floor/tile green",
		white = F"floor/tile white",
		yellow = F"floor/tile yellow",
	},
	wood_stairs = T"floor/wood stairs",
}

wall = {
	brick = W"wall/brick",
	concrete = W"wall/concrete",
	glass = W"wall/glass",
	marble = {
		black = W"wall/marble black",
		blue = W"wall/marble blue",
		green = W"wall/marble green",
		purple = W"wall/marble purple",
		red = W"wall/marble red",
		white = W"wall/marble white",
	},
	stone = W"wall/stone",
	white = W"wall/white",
}
