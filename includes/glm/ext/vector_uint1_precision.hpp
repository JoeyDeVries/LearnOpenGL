/// @ref ext_vector_uint1_precision
/// @file glm/ext/vector_uint1_precision.hpp
///
/// @defgroup ext_vector_uint1_precision GLM_EXT_vector_uint1_precision
/// @ingroup ext
///
/// Exposes highp_uvec1, mediump_uvec1 and lowp_uvec1 types.
///
/// Include <glm/ext/vector_uint1_precision.hpp> to use the features of this extension.

#pragma once

#include "../detail/type_vec1.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_uint1_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_uint1_precision
	/// @{

	/// 1 component vector of unsigned integer values.
	///
	/// @see ext_vector_uint1_precision
	typedef vec<1, unsigned int, highp>			highp_uvec1;

	/// 1 component vector of unsigned integer values.
	///
	/// @see ext_vector_uint1_precision
	typedef vec<1, unsigned int, mediump>		mediump_uvec1;

	/// 1 component vector of unsigned integer values.
	///
	/// @see ext_vector_uint1_precision
	typedef vec<1, unsigned int, lowp>			lowp_uvec1;

	/// @}
}//namespace glm
