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
		::size_t image_width, image_height, texture_width, texture_height;
		
		// Load the texture file.
		data_ = hplat_read_texture_file(filename.c_str(),
			&image_width, &image_height, &texture_width, &texture_height);

		// Store image metrics.
		size_ = ivec2(texture_width, texture_height);
		filled_size_ = ivec2(image_width, image_height);
		
		// Generate a texture name.
		glGenTextures(1, &name_);
	}
	
	gl::texture::texture(const ivec2 & size) : loaded_(false), size_(size),
		filled_size_(size), data_(NULL)
	{
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
	
	ivec2 gl::texture::size() const {
		return size_;
	}
	
	ivec2 gl::texture::filled_size() const {
		return filled_size_;
	}
	
	vec2 gl::texture::filled_portion() const {
		return vec2(filled_size_.fx() / size_.fx(), filled_size_.fy() / size_.fy());
	}
	
	void gl::texture::copy_tex_coords(float (& tex_coords)[4][2]) const {
		vec2 extent = filled_portion();
		tex_coords[0][0] = 0.00;       tex_coords[0][1] = 0.00;
		tex_coords[1][0] = 0.00;       tex_coords[1][1] = extent.y();
		tex_coords[2][0] = extent.x(); tex_coords[2][1] = extent.y();
		tex_coords[3][0] = extent.x(); tex_coords[3][1] = 0.00;
	}
	
	void gl::texture::load() {
		if (!loaded_) {
			// Set pixel format options.
			glPixelStorei(GL_UNPACK_ROW_LENGTH, size_.x());
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			
			// Set the active texture.
			glBindTexture(GL_TEXTURE_2D, name_);
			
			// Set texture parameters.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			
			// Load the texture.
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size_.x(), size_.y(), 0,
				GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, data_);
			
			// Clear the active texture.
			glBindTexture(GL_TEXTURE_2D, 0);
			
			// Remember that the texture is loaded.
			loaded_ = true;
			
			// Free the data buffer.
			free(data_);
			data_ = NULL;
		}
	}
}
