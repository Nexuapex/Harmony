//
// geom_shape_fwd.h
// Harmony
//

#ifndef HARMONY_GEOM_SHAPE_FWD_H
#define HARMONY_GEOM_SHAPE_FWD_H

#include <boost/shared_ptr.hpp>

namespace harmony {
	namespace geom {
		class shape;
		typedef boost::shared_ptr<const shape> shape_ref;
	}
}

#endif // HARMONY_GEOM_SHAPE_FWD_H
