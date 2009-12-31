// The texture that is placed on the actor.
uniform sampler2D sprite;

// An option for making a specific color fully transparent.
uniform bool use_transparent_color;
uniform vec3 transparent_color;

// The acceptable delta for a color to match another color.
const vec3 transparent_threshold = vec3(0.5 / 255.0);

void main() {
	// Sample the texture.
	vec4 color = texture2D(sprite, gl_TexCoord[0].st);
	
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
