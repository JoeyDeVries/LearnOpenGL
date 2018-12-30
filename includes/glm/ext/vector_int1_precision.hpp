/// @ref ext_vector_int1_precision
/// @file glm/ext/vector_int1_precision.hpp
///
/// @defgroup ext_vector_int1_precision GLM_EXT_vector_int1_precision
/// @ingroup ext
///
/// Exposes highp_ivec1, mediump_ivec1 and lowp_ivec1 types.
///
/// Include <glm/ext/vector_int1_precision.hpp> to use the features of this extension.

#pragma once

#include "../detail/type_vec1.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_EXT_vector_int1_precision extension included")
#endif

namespace glm
{
	/// @addtogroup ext_vector_int1_precision
	/// @{

	/// 1 component vector of signed integer values.
	typedef vec<1, int, highp>			highp_ivec1;

	/// 1 component vector of signed integer values.
	typedef vec<1, int, mediump>		mediump_ivec1;

	/// 1 component vector of signed integer values.
	typedef vec<1, int, lowp>			lowp_ivec1;

	/// @}
}//namespace glm
