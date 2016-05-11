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
/// @ref gtx_hash
/// @file glm/gtx/hash.hpp
/// @date 2015-03-07 / 2015-03-07
/// @author Christophe Riccio
///
/// @see core (dependence)
///
/// @defgroup gtx_hash GLM_GTX_hash
/// @ingroup gtx
/// 
/// @brief Add std::hash support for glm types
/// 
/// <glm/gtx/hash.hpp> need to be included to use these functionalities.
///////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <functional>

#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../vec4.hpp"
#include "../gtc/vec1.hpp"

#include "../gtc/quaternion.hpp"
#include "../gtx/dual_quaternion.hpp"

#include "../mat2x2.hpp"
#include "../mat2x3.hpp"
#include "../mat2x4.hpp"

#include "../mat3x2.hpp"
#include "../mat3x3.hpp"
#include "../mat3x4.hpp"

#include "../mat4x2.hpp"
#include "../mat4x3.hpp"
#include "../mat4x4.hpp"

#if !GLM_HAS_CXX11_STL
#	error "GLM_GTX_hash requires C++11 standard library support"
#endif

namespace std
{
	template <typename T, glm::precision P>
	struct hash<glm::tvec1<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tvec1<T, P> const & v) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tvec2<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tvec2<T, P> const & v) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tvec3<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tvec3<T, P> const & v) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tvec4<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tvec4<T, P> const & v) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tquat<T,P>>
	{
		GLM_FUNC_DECL size_t operator()(glm::tquat<T, P> const & q) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tdualquat<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tdualquat<T,P> const & q) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat2x2<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat2x2<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat2x3<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat2x3<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat2x4<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat2x4<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat3x2<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat3x2<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat3x3<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat3x3<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat3x4<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat3x4<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat4x2<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat4x2<T,P> const & m) const;
	};
	
	template <typename T, glm::precision P>
	struct hash<glm::tmat4x3<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat4x3<T,P> const & m) const;
	};

	template <typename T, glm::precision P>
	struct hash<glm::tmat4x4<T,P> >
	{
		GLM_FUNC_DECL size_t operator()(glm::tmat4x4<T,P> const & m) const;
	};
} // namespace std

#include "hash.inl"
