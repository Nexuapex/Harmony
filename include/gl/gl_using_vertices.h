//
// gl_using_vertices.h
// Harmony
//

#ifndef HARMONY_GL_USING_VERTICES_H
#define HARMONY_GL_USING_VERTICES_H

#include "gl_library.h"
#include "gl_types.h"

namespace harmony {
	namespace gl {
		// Activates a set of vertices and texture coordinates.
		class using_vertices {
		public:
			using_vertices(gl::size_t count, gl::size_t breadth,
				const gl::float_t * vertices, const gl::float_t * tex_coords)
				: count_(count)
			{
				glEnableClientState(GL_VERTEX_ARRAY);
				glVertexPointer(breadth, GL_FLOAT, 0, vertices);
				
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glTexCoordPointer(breadth, GL_FLOAT, 0, tex_coords);
			}
			
			~using_vertices() {
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glDisableClientState(GL_VERTEX_ARRAY);
			}
			
			void draw(gl::enum_t mode) {
				glDrawArrays(mode, 0, count_);
			}

		private:
			gl::size_t count_;
		};
	}
}

#endif // HARMONY_GL_USING_VERTICES_H
