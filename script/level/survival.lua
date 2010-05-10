local level = ...

require "tile"
local a  = tile.floor.asphalt
local b  = tile.floor.boardwalk
local cr = tile.floor.carpet.red
local cw = tile.floor.carpet.white
local cs = tile.floor.concrete_stairs
local d  = tile.floor.dirt
local dn = tile.floor.dirt_road.normal
local dr = tile.floor.dirt_road.rough
local g  = tile.floor.grass
local s  = tile.floor.sand
local wb = tile.wall.brick
local wc = tile.wall.concrete
local ws = tile.wall.stone

-- Create an actor that the player controls.
local player = object.create_actor()
player.sprite = object.create_sprite("player", ".png", 48)

local ps = {g, player}

-- And now, the level layout.
table.insert(level.layers, {

width = 36,
height = 24,
tile_size = 48,

{ws,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wb,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b, b,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, d, d, d,dn,dn,dr,dn,dn,dn,dn,dr,dr,dn,dn,dn,dn,dn,dn,dn,dn,dr,dn,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, d, d, d,dn,dn,dn,dn,dn,dn,dn,dn,dn,dn,dn,dr,dn,dn,dn,dr,dn,dn,dr,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, d, d, d, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,cr,cr, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws,cs,cs,cs,cs, g, g, g, g, g, g, g, g, g, g, g, g,ps, g, g,cr,cr, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, s, s, s,cs, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,cr,cr, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, s, s, s,cs, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, s, s, s,cs, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws,cs,cs,cs,cs, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g,cw,cw,cw, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g,cw,cw,cw, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g,cw,cw,cw, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g,cw,cw,cw, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g, g,wc,},
{ws,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,wc,},

})
