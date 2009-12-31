//
// gl_texture.cpp
// Harmony
//

#include <cstddef>
#include <cstdlib>

#include "gl_texture.h"
#include "gl_library.h"
#include "plat_interface.h"

namespace harmony {
	gl::texture::texture(const std::string & filename) : loaded_(false) {
		::size_t imageWidth, imageHeight, textureWidth, textureHeight;
		
		// Load the texture file.
		data_ = hplat_read_texture_file(filename.c_str(),
			&imageWidth, &imageHeight, &textureWidth, &textureHeight);

		// Store image metrics.
		width_ = textureWidth;
		height_ = textureHeight;
		width_ratio_ = static_cast<float_t>(imageWidth) / static_cast<float_t>(textureWidth);
		height_ratio_ = static_cast<float_t>(imageHeight) / static_cast<float_t>(textureHeight);
		
		// Generate a texture name.
		glGenTextures(1, &name_);
	}
	
	gl::texture::~texture() {
		glDeleteTextures(1, &name_);
		free(data_);
	}
	
	gl::texture_t gl::texture::name(bool require_loaded) {
		if (require_loaded)
			load();
		
		return name_;
	}
	
	gl::size_t gl::texture::width() const {
		return width_;
	}
	
	gl::size_t gl::texture::height() const {
		return height_;
	}

	gl::float_t gl::texture::width_ratio() const {
		return width_ratio_;
	}
	
	gl::float_t gl::texture::height_ratio() const {
		return height_ratio_;
	}
	
	void gl::texture::load_tex_coords(float (& tex_coords)[4][2]) const {
		tex_coords[0][0] = 0.00;         tex_coords[0][1] = 0.00;
		tex_coords[1][0] = 0.00;         tex_coords[1][1] = height_ratio_;
		tex_coords[2][0] = width_ratio_; tex_coords[2][1] = height_ratio_;
		tex_coords[3][0] = width_ratio_; tex_coords[3][1] = 0.00;
	}
	
	void gl::texture::load() {
		if (!loaded_) {
			// Set pixel format options.
			glPixelStorei(GL_UNPACK_ROW_LENGTH, width_);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			
			// Set the active texture.
			glBindTexture(GL_TEXTURE_2D, name_);
			
			// Set texture parameters.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			
			// Load the texture.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0,
				GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data_);
			
			// Remember that the texture is loaded.
			loaded_ = true;
		}
	}
}
