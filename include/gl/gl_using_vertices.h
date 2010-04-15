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
			using_vertices(size_t count, size_t breadth,
				const float_t * vertices, const float_t * tex_coords);
			~using_vertices();
			
			void draw(enum_t mode) const;

		private:
			size_t count_;
		};
	}
}

#endif // HARMONY_GL_USING_VERTICES_H
