//
// gl_using_vertices.cpp
// Harmony
//

#include "gl_using_vertices.h"

namespace harmony {
	gl::using_vertices::using_vertices(size_t count, size_t breadth,
		const quad_t & vertices, const quad_t & tex_coords)
		: count_(count)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(breadth, GL_FLOAT, 0, &vertices[0][0]);
		
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(breadth, GL_FLOAT, 0, &tex_coords[0][0]);
	}
	
	gl::using_vertices::~using_vertices() {
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
	void gl::using_vertices::draw(enum_t mode) const {
		glDrawArrays(mode, 0, count_);
	}
}
