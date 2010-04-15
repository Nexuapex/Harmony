//
// gl_using_buffer.h
// Harmony
//

#ifndef HARMONY_GL_USING_BUFFER_H
#define HARMONY_GL_USING_BUFFER_H

#include "gl_buffer_fwd.h"

namespace harmony {
	namespace gl {
		// Activates an OpenGL buffer.
		template <typename T>
		class using_buffer {
		private:
			typedef typename buffer_types<T>::ref buffer_ref;
			
		private:
			const buffer_layout::attribute_layout & attribute(buffer_attribute attr) const {
				return buffer_->layout()->attribute(attr);
			}
			
		public:
			using_buffer(const buffer_ref & buf) : buffer_(buf) {
				// Bind the buffer.
				glBindBuffer(buf->layout()->type(), buf->name());
				
				{
					// Vertex coordinates.
					const buffer_layout::attribute_layout & vertices
						= attribute(buffer_attribute_coord);
					if (vertices.included) {
						glEnableClientState(GL_VERTEX_ARRAY);
						glVertexPointer(
							vertices.breadth,
							vertices.type,
							buf->stride(),
							(GLvoid *)vertices.offset
						);
					}
				}
				
				{
					// Texture coordinates.
					const buffer_layout::attribute_layout & tex_coords
						= attribute(buffer_attribute_tex_coord);
					if (tex_coords.included) {
						glEnableClientState(GL_TEXTURE_COORD_ARRAY);
						glTexCoordPointer(
							tex_coords.breadth,
							tex_coords.type,
							buf->stride(),
							(GLvoid *)tex_coords.offset
						);
					}
				}
			}
			
			~using_buffer() {
				if (attribute(buffer_attribute_coord).included)
					glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				
				if (attribute(buffer_attribute_tex_coord).included)
					glDisableClientState(GL_VERTEX_ARRAY);
				
				glBindBuffer(buffer_->layout()->type(), 0);
			}
			
			void draw(enum_t mode) const {
				glDrawElements(mode, buffer_->count(), GL_UNSIGNED_SHORT, NULL);
			}
			
		private:
			buffer_ref buffer_;
		};
	}
}

#endif // HARMONY_GL_USING_BUFFER_H
