//
// gl_buffer.cpp
// Harmony
//

#include "gl_buffer.h"
#include "gl_library.h"

#include "gl_using_buffer.h"

namespace harmony {
	gl::buffer_layout::buffer_layout(buffer_type type, buffer_mutability mutability, buffer_usage usage)
		: type_(type), mutability_(mutability), usage_(usage) {}
	
	void gl::buffer_layout::set_attribute(buffer_attribute attribute,
		bool included, enum_t data_type, size_t breadth, size_t offset)
	{
		attribute_layout & attr = attributes_[attribute];
		attr.included = included;
		attr.type = data_type;
		attr.breadth = breadth;
		attr.offset = offset;
	}
	
	const gl::buffer_layout::attribute_layout &
		gl::buffer_layout::attribute(buffer_attribute attribute) const
	{
		return attributes_[attribute];
	}
	
	gl::buffer_type gl::buffer_layout::type() const {
		return type_;
	}
	
	gl::buffer_mutability gl::buffer_layout::mutability() const {
		return mutability_;
	}
	
	gl::buffer_usage gl::buffer_layout::usage() const {
		return usage_;
	}
	
	gl::enum_t gl::buffer_layout::hint() const {
		switch (mutability_) {
			case buffer_mutability_static: {
				switch (usage_) {
					case buffer_usage_draw:
						return GL_STATIC_DRAW;
					case buffer_usage_copy:
						return GL_STATIC_COPY;
					case buffer_usage_read:
						return GL_STATIC_READ;
				}
				break;
			}
				
			case buffer_mutability_stream: {
				switch (usage_) {
					case buffer_usage_draw:
						return GL_STREAM_DRAW;
					case buffer_usage_copy:
						return GL_STREAM_COPY;
					case buffer_usage_read:
						return GL_STREAM_READ;
				}
				break;
			}
				
			case buffer_mutability_dynamic: {
				switch (usage_) {
					case buffer_usage_draw:
						return GL_DYNAMIC_DRAW;
					case buffer_usage_copy:
						return GL_DYNAMIC_COPY;
					case buffer_usage_read:
						return GL_DYNAMIC_READ;
				}
				break;
			}
		}
		
		// An (un)reasonable default.
		return GL_DYNAMIC_DRAW;
	}
}
