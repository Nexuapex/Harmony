// The texture that is placed on the tile.
uniform sampler2D tile;

// The rotation to apply to the texture.
uniform int rotation;

// An option for making a specific color fully transparent.
uniform bool use_transparent_color;
uniform vec3 transparent_color;

// The acceptable delta for a color to match another color.
const vec3 transparent_threshold = vec3(0.5 / 255.0);

void main() {
	vec4 src = gl_TexCoord[0];
	vec2 coord;
	
	// Rotate the texture.
	if (rotation == 0) {
		coord = src.st;
	} else if (rotation == 1) {
		coord.s = -src.t;
		coord.t = src.s;
	} else if (rotation == 2) {
		coord.s = -src.s;
		coord.t = -src.t;
	} else if (rotation == 3) {
		coord.s = src.t;
		coord.t = -src.s;
	} else if (rotation == 4) {
		coord.s = -src.s;
		coord.t = src.t;
	} else if (rotation == 5) {
		coord.s = -src.t;
		coord.t = -src.s;
	} else if (rotation == 6) {
		coord.s = src.s;
		coord.t = -src.t;
	} else if (rotation == 7) {
		coord = src.ts;
	}
	
	// Sample the texture.
	vec4 color = texture2D(tile, coord);
	
	// Make a specific color transparent.
	if (use_transparent_color) {
		vec3 color_delta = abs(vec3(color) - transparent_color);
		if (all(lessThan(color_delta, transparent_threshold))) {
			color.a = 0.0;
		}
	}
	
	// Apply the color to the fragment.
	gl_FragColor = color;
}
