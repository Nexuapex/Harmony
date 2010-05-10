// The texture that is placed on the tile.
uniform sampler2D tile;

// An option for making a specific color fully transparent.
uniform bool use_transparent_color;
uniform vec3 transparent_color;

// The acceptable delta for a color to match another color.
const vec3 transparent_threshold = vec3(0.5 / 255.0);

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
	vec4 color = texture2D(tile, gl_TexCoord[0].st);
	
	// Apply the color to the fragment.
	gl_FragColor = apply_transparency(color);
}
