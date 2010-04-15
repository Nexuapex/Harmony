//
// gl_buffer_fwd.h
// Harmony
//

#ifndef HARMONY_GL_BUFFER_FWD_H
#define HARMONY_GL_BUFFER_FWD_H

#include <boost/shared_ptr.hpp>

#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Possible attribute types for a field in the buffer.
		typedef enum {
			buffer_attribute_coord     = 0,
			buffer_attribute_tex_coord = 1
		} buffer_attribute;
		
		// The type of data stored by the buffer.
		typedef enum {
			buffer_type_vertex = GL_ARRAY_BUFFER,
			buffer_type_index  = GL_ELEMENT_ARRAY_BUFFER
		} buffer_type;
		
		// The frequency with which the buffer will be modified.
		typedef enum {
			buffer_mutability_static,
			buffer_mutability_stream,
			buffer_mutability_dynamic
		} buffer_mutability;
		
		// The usage pattern of the buffer.
		typedef enum {
			buffer_usage_draw,
			buffer_usage_copy,
			buffer_usage_read
		} buffer_usage;
		
		// Forward declarations of buffer_layout and buffer_layout_ref.
		class buffer_layout;
		typedef boost::shared_ptr<buffer_layout> buffer_layout_ref;
		
		// Forward declarations of buffer<T> and buffer_types<T>::ref.
		template <typename T>
		class buffer;
		template <typename T>
		struct buffer_types {
			typedef boost::shared_ptr< buffer<T> > ref;
		};
	}
}

#endif // HARMONY_GL_BUFFER_FWD_H
