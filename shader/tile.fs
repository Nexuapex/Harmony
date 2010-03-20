// The texture that is placed on the tile.
uniform sampler2D tile;

// The region of the tile that is occupied by the texture.
uniform vec2 tile_ratio;

// The rotation to apply to the texture.
uniform int rotation;

// An option for making a specific color fully transparent.
uniform bool use_transparent_color;
uniform vec3 transparent_color;

// The acceptable delta for a color to match another color.
const vec3 transparent_threshold = vec3(0.5 / 255.0);

vec2 apply_rotation(in vec4 src) {
	vec2 coord;
	
	if (rotation == 0) {
		// Normal.
		coord = src.st;
	} else if (rotation == 1) {
		// Rotate right.
		coord.s = tile_ratio.t - src.t;
		coord.t = src.s;
	} else if (rotation == 2) {
		// Rotate 180.
		coord.s = tile_ratio.s - src.s;
		coord.t = tile_ratio.t - src.t;
	} else if (rotation == 3) {
		// Rotate left.
		coord.s = src.t;
		coord.t = tile_ratio.s - src.s;
	} else if (rotation == 4) {
		// Flip.
		coord.s = tile_ratio.s - src.s;
		coord.t = src.t;
	} else if (rotation == 5) {
		// Flip and rotate left.
		coord.s = tile_ratio.t - src.t;
		coord.t = tile_ratio.s - src.s;
	} else if (rotation == 6) {
		// Flip and rotate 180.
		coord.s = src.s;
		coord.t = tile_ratio.t - src.t;
	} else if (rotation == 7) {
		// Flip and rotate right.
		coord = src.ts;
	}
	
	return coord;
}

vec4 apply_transparency(in vec4 color) {
	if (use_transparent_color) {
		vec3 color_delta = abs(vec3(color) - transparent_color);
		if (all(lessThan(color_delta, transparent_threshold))) {
			color.a = 0.0;
		}
	}
	
	return color;
}

void main() {
	// Sample the texture.
	vec4 color = texture2D(tile, apply_rotation(gl_TexCoord[0]));
	
	// Apply the color to the fragment.
	gl_FragColor = apply_transparency(color);
}
