///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2015 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// Restrictions:
///		By making use of the Software for military purposes, you choose to make
///		a Bunny unhappy.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref gtc_color_space
/// @file glm/gtc/color_space.hpp
/// @date 2015-02-10 / 2015-08-02
/// @author Christophe Riccio
///
/// @see core (dependence)
/// @see gtc_color_space (dependence)
///
/// @defgroup gtc_color_space GLM_GTC_color_space
/// @ingroup gtc
/// 
/// @brief Allow to perform bit operations on integer values
/// 
/// <glm/gtc/color.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#pragma once

// Dependencies
#include "../detail/setup.hpp"
#include "../detail/precision.hpp"
#include "../exponential.hpp"
#include "../vec3.hpp"
#include "../vec4.hpp"
#include <limits>

#if(defined(GLM_MESSAGES) && !defined(GLM_EXT_INCLUDED))
#	pragma message("GLM: GLM_GTC_color_space extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_color_space
	/// @{

	/// Convert a linear color to sRGB color using a standard gamma correction
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_DECL vecType<T, P> convertLinearToSRGB(vecType<T, P> const & ColorLinear);

	/// Convert a linear color to sRGB color using a custom gamma correction	
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_DECL vecType<T, P> convertLinearToSRGB(vecType<T, P> const & ColorLinear, T Gamma);

	/// Convert a sRGB color to linear color using a standard gamma correction
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_DECL vecType<T, P> convertSRGBToLinear(vecType<T, P> const & ColorSRGB);

	/// Convert a sRGB color to linear color using a custom gamma correction
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_DECL vecType<T, P> convertSRGBToLinear(vecType<T, P> const & ColorSRGB, T Gamma);

	/// @}
} //namespace glm

#include "color_space.inl"
