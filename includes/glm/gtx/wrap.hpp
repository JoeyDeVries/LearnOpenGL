/// @ref gtx_wrap
/// @file glm/gtx/wrap.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_wrap GLM_GTX_wrap
/// @ingroup gtx
///
/// Include <glm/gtx/wrap.hpp> to use the features of this extension.
///
/// Wrapping mode of texture coordinates.

#pragma once

// Dependency:
#include "../glm.hpp"
#include "../gtc/vec1.hpp"

#ifndef GLM_ENABLE_EXPERIMENTAL
#	error "GLM: GLM_GTX_wrap is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it."
#endif

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTX_wrap extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_wrap
	/// @{

	/// Simulate GL_CLAMP OpenGL wrap mode
	/// @see gtx_wrap extension.
	template<typename genType>
	GLM_FUNC_DECL genType clamp(genType const& Texcoord);

	/// Simulate GL_REPEAT OpenGL wrap mode
	/// @see gtx_wrap extension.
	template<typename genType>
	GLM_FUNC_DECL genType repeat(genType const& Texcoord);

	/// Simulate GL_MIRRORED_REPEAT OpenGL wrap mode
	/// @see gtx_wrap extension.
	template<typename genType>
	GLM_FUNC_DECL genType mirrorClamp(genType const& Texcoord);

	/// Simulate GL_MIRROR_REPEAT OpenGL wrap mode
	/// @see gtx_wrap extension.
	template<typename genType>
	GLM_FUNC_DECL genType mirrorRepeat(genType const& Texcoord);

	/// @}
}// namespace glm

#include "wrap.inl"
