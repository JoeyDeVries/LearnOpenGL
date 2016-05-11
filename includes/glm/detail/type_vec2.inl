///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Mathematics (glm.g-truc.net)
///
/// Copyright (c) 2005 - 2014 G-Truc Creation (www.g-truc.net)
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
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file glm/core/type_tvec2.inl
/// @date 2008-08-18 / 2011-06-15
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	// -- Implicit basic constructors --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS || !defined(GLM_FORCE_NO_CTOR_INIT)
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2()
#			ifndef GLM_FORCE_NO_CTOR_INIT
				: x(0), y(0)
#			endif
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec2<T, P> const & v)
			: x(v.x), y(v.y)
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <precision Q>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec2<T, Q> const & v)
		: x(v.x), y(v.y)
	{}

	// -- Explicit basic constructors --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(ctor)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(T const & scalar)
		: x(scalar), y(scalar)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(T const & s1, T const & s2)
		: x(s1), y(s2)
	{}

	// -- Conversion scalar constructors --

	template <typename T, precision P>
	template <typename A, typename B>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(A const & a, B const & b)
		: x(static_cast<T>(a))
		, y(static_cast<T>(b))
	{}

	template <typename T, precision P>
	template <typename A, typename B>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec1<A, P> const & a, tvec1<B, P> const & b)
		: x(static_cast<T>(a.x))
		, y(static_cast<T>(b.x))
	{}

	// -- Conversion vector constructors --

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec2<U, Q> const & v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec3<U, Q> const & v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER tvec2<T, P>::tvec2(tvec4<U, Q> const & v)
		: x(static_cast<T>(v.x))
		, y(static_cast<T>(v.y))
	{}

	// -- Component accesses --

#	ifdef GLM_FORCE_SIZE_FUNC
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tvec2<T, P>::size_type tvec2<T, P>::size() const
		{
			return 2;
		}

		template <typename T, precision P>
		GLM_FUNC_QUALIFIER T & tvec2<T, P>::operator[](typename tvec2<T, P>::size_type i)
		{
			assert(i >= 0 && static_cast<detail::component_count_t>(i) < detail::component_count(*this));
			return (&x)[i];
		}

		template <typename T, precision P>
		GLM_FUNC_QUALIFIER T const & tvec2<T, P>::operator[](typename tvec2<T, P>::size_type i) const
		{
			assert(i >= 0 && static_cast<detail::component_count_t>(i) < detail::component_count(*this));
			return (&x)[i];
		}
#	else
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename tvec2<T, P>::length_type tvec2<T, P>::length() const
		{
			return 2;
		}

		template <typename T, precision P>
		GLM_FUNC_QUALIFIER T & tvec2<T, P>::operator[](typename tvec2<T, P>::length_type i)
		{
			assert(i >= 0 && static_cast<detail::component_count_t>(i) < detail::component_count(*this));
			return (&x)[i];
		}

		template <typename T, precision P>
		GLM_FUNC_QUALIFIER T const & tvec2<T, P>::operator[](typename tvec2<T, P>::length_type i) const
		{
			assert(i >= 0 && static_cast<detail::component_count_t>(i) < detail::component_count(*this));
			return (&x)[i];
		}
#	endif//GLM_FORCE_SIZE_FUNC

	// -- Unary arithmetic operators --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator=(tvec2<T, P> const & v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator=(tvec2<U, P> const & v)
	{
		this->x = static_cast<T>(v.x);
		this->y = static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(U scalar)
	{
		this->x += static_cast<T>(scalar);
		this->y += static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(tvec1<U, P> const & v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(tvec2<U, P> const & v)
	{
		this->x += static_cast<T>(v.x);
		this->y += static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(U scalar)
	{
		this->x -= static_cast<T>(scalar);
		this->y -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(tvec1<U, P> const & v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(tvec2<U, P> const & v)
	{
		this->x -= static_cast<T>(v.x);
		this->y -= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(U scalar)
	{
		this->x *= static_cast<T>(scalar);
		this->y *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(tvec1<U, P> const & v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(tvec2<U, P> const & v)
	{
		this->x *= static_cast<T>(v.x);
		this->y *= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(U scalar)
	{
		this->x /= static_cast<T>(scalar);
		this->y /= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(tvec1<U, P> const & v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(tvec2<U, P> const & v)
	{
		this->x /= static_cast<T>(v.x);
		this->y /= static_cast<T>(v.y);
		return *this;
	}

	// -- Increment and decrement operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator++()
	{
		++this->x;
		++this->y;
		return *this;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator--()
	{
		--this->x;
		--this->y;
		return *this;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec2<T, P> tvec2<T, P>::operator++(int)
	{
		tvec2<T, P> Result(*this);
		++*this;
		return Result;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec2<T, P> tvec2<T, P>::operator--(int)
	{
		tvec2<T, P> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(U scalar)
	{
		this->x %= static_cast<T>(scalar);
		this->y %= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(tvec1<U, P> const & v)
	{
		this->x %= static_cast<T>(v.x);
		this->y %= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(tvec2<U, P> const & v)
	{
		this->x %= static_cast<T>(v.x);
		this->y %= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(U scalar)
	{
		this->x &= static_cast<T>(scalar);
		this->y &= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(tvec1<U, P> const & v)
	{
		this->x &= static_cast<T>(v.x);
		this->y &= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(tvec2<U, P> const & v)
	{
		this->x &= static_cast<T>(v.x);
		this->y &= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(U scalar)
	{
		this->x |= static_cast<T>(scalar);
		this->y |= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(tvec1<U, P> const & v)
	{
		this->x |= static_cast<T>(v.x);
		this->y |= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(tvec2<U, P> const & v)
	{
		this->x |= static_cast<T>(v.x);
		this->y |= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(U scalar)
	{
		this->x ^= static_cast<T>(scalar);
		this->y ^= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(tvec1<U, P> const & v)
	{
		this->x ^= static_cast<T>(v.x);
		this->y ^= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(tvec2<U, P> const & v)
	{
		this->x ^= static_cast<T>(v.x);
		this->y ^= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(U scalar)
	{
		this->x <<= static_cast<T>(scalar);
		this->y <<= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(tvec1<U, P> const & v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(tvec2<U, P> const & v)
	{
		this->x <<= static_cast<T>(v.x);
		this->y <<= static_cast<T>(v.y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(U scalar)
	{
		this->x >>= static_cast<T>(scalar);
		this->y >>= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(tvec1<U, P> const & v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(tvec2<U, P> const & v)
	{
		this->x >>= static_cast<T>(v.x);
		this->y >>= static_cast<T>(v.y);
		return *this;
	}

	// -- Unary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v)
	{
		return v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			-v.x, 
			-v.y);
	}

	// -- Binary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x + scalar,
			v.y + scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x + v2.x,
			v1.y + v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar + v.x,
			scalar + v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x + v2.x,
			v1.x + v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x + v2.x,
			v1.y + v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x - scalar,
			v.y - scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x - v2.x,
			v1.y - v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar - v.x,
			scalar - v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x - v2.x,
			v1.x - v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x - v2.x,
			v1.y - v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v1, T const & v2)
	{
		return tvec2<T, P>(
			v1.x * v2,
			v1.y * v2);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x * v2.x,
			v1.y * v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar * v.x,
			scalar * v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x * v2.x,
			v1.x * v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x * v2.x,
			v1.y * v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x / scalar,
			v.y / scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x / v2.x,
			v1.y / v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar / v.x,
			scalar / v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x / v2.x,
			v1.x / v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x / v2.x,
			v1.y / v2.y);
	}

	// -- Binary bit operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x % scalar,
			v.y % scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x % v2.x,
			v1.y % v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar % v.x,
			scalar % v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x % v2.x,
			v1.x % v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x % v2.x,
			v1.y % v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x & scalar,
			v.y & scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x & v2.x,
			v1.y & v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar & v.x,
			scalar & v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x & v2.x,
			v1.x & v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x & v2.x,
			v1.y & v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x | scalar,
			v.y | scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x | v2.x,
			v1.y | v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar | v.x,
			scalar | v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x | v2.x,
			v1.x | v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x | v2.x,
			v1.y | v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x ^ scalar,
			v.y ^ scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x ^ v2.x,
			v1.y ^ v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar ^ v.x,
			scalar ^ v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x ^ v2.x,
			v1.x ^ v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x ^ v2.x,
			v1.y ^ v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x << scalar,
			v.y << scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x << v2.x,
			v1.y << v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar << v.x,
			scalar << v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x << v2.x,
			v1.x << v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x << v2.x,
			v1.y << v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v, T const & scalar)
	{
		return tvec2<T, P>(
			v.x >> scalar,
			v.y >> scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x >> v2.x,
			v1.y >> v2.x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(T const & scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar >> v.x,
			scalar >> v.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x >> v2.x,
			v1.x >> v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.x >> v2.x,
			v1.y >> v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator~(tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			~v.x,
			~v.y);
	}

	// -- Boolean operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator==(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return (v1.x == v2.x) && (v1.y == v2.y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator!=(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return (v1.x != v2.x) || (v1.y != v2.y);
	}
}//namespace glm
