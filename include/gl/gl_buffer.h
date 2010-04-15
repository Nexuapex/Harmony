//
// gl_buffer.h
// Harmony
//

#ifndef HARMONY_GL_BUFFER_H
#define HARMONY_GL_BUFFER_H

#include <cstddef>

#include "gl_buffer_fwd.h"

namespace harmony {
	namespace gl {
		// Describes the layout and attributes of a class of buffers.
		class buffer_layout {
		public:
			class attribute_layout {
			public:
				attribute_layout() : included(false) {}
				
			public:
				bool included;
				enum_t type;
				size_t breadth;
				size_t offset;
			};
			
		public:
			// Constructor.
			buffer_layout(buffer_type type, buffer_mutability mutability,
				buffer_usage usage);
			
			// Set up the layout of a specific attribute.
			void set_attribute(buffer_attribute attribute, bool included,
				enum_t data_type, size_t breadth, size_t offset);
			
			// Get the layout of a specific attribute.
			const attribute_layout & attribute(buffer_attribute attribute) const;
			
			// The type (target) of the buffer.
			buffer_type type() const;
			
			// The mutability hint of the buffer.
			buffer_mutability mutability() const;
			
			// The usage hint of the buffer.
			buffer_usage usage() const;
			
			// OpenGL-usable mutability/usage hint of the buffer.
			enum_t hint() const;
			
		private:
			buffer_type type_;
			buffer_mutability mutability_;
			buffer_usage usage_;
			attribute_layout attributes_[2];
		};
		
		// A buffer containing an array of some kind of data for OpenGL.
		template <typename T>
		class buffer {
		public:
			// Constructor.
			buffer(const buffer_layout_ref & layout, const T * data, size_t count)
				: count_(count), layout_(layout)
			{
				// Generate a buffer name.
				glGenBuffers(1, &name_);
				
				// Set up the buffer.
				glBindBuffer(layout_->type(), name_);
				glBufferData(layout_->type(), size(), data, layout_->hint());
				glBindBuffer(layout_->type(), 0);
			}
			
			// Destructor.
			~buffer() {
				glDeleteBuffers(1, &name_);
			}
			
			// A reference to the buffer itself, to be used with OpenGL calls.
			buffer_t name() const {
				return name_;
			}
			
			// The number of elements in the buffer.
			size_t count() const {
				return count_;
			}
			
			// The size of a single element in the buffer.
			size_t stride() const {
				return sizeof(T);
			}
			
			// The size of the buffer, in bytes.
			ptrsize_t size() const {
				return sizeof(T) * count_;
			}
			
			// The layout specifier of the buffer.
			buffer_layout_ref layout() const {
				return layout_;
			}
			
		private:
			buffer_t name_;
			size_t count_;
			buffer_layout_ref layout_;
		};
	}
}

#endif // HARMONY_GL_BUFFER_H
