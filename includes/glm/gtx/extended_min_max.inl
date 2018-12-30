/// @ref gtx_extended_min_max

namespace glm
{
	template<typename T>
	GLM_FUNC_QUALIFIER T min(
		T const& x,
		T const& y,
		T const& z)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z
	)
	{
		return glm::min(glm::min(x, y), z);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T min
	(
		T const& x,
		T const& y,
		T const& z,
		T const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z,
		typename C<T>::T const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> min
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z,
		C<T> const& w
	)
	{
		return glm::min(glm::min(x, y), glm::min(z, w));
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T max(
		T const& x,
		T const& y,
		T const& z)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z
	)
	{
		return glm::max(glm::max(x, y), z);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T max
	(
		T const& x,
		T const& y,
		T const& z,
		T const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		typename C<T>::T const& y,
		typename C<T>::T const& z,
		typename C<T>::T const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	template<typename T, template<typename> class C>
	GLM_FUNC_QUALIFIER C<T> max
	(
		C<T> const& x,
		C<T> const& y,
		C<T> const& z,
		C<T> const& w
	)
	{
		return glm::max(glm::max(x, y), glm::max(z, w));
	}

	// fmin
#	if GLM_HAS_CXX11_STL
		using std::fmin;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType fmin(genType x, genType y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fmin' only accept floating-point input");

			if (isnan(x))
				return y;
			if (isnan(y))
				return x;

			return min(x, y);
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fmin(vec<L, T, Q> const& a, T b)
	{
		return detail::functor2<vec, L, T, Q>::call(fmin, a, vec<L, T, Q>(b));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fmin(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
	{
		return detail::functor2<vec, L, T, Q>::call(fmin, a, b);
	}

	// fmax
#	if GLM_HAS_CXX11_STL
		using std::fmax;
#	else
		template<typename genType>
		GLM_FUNC_QUALIFIER genType fmax(genType x, genType y)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fmax' only accept floating-point input");

			if (isnan(x))
				return y;
			if (isnan(y))
				return x;

			return max(x, y);
		}
#	endif

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fmax(vec<L, T, Q> const& a, T b)
	{
		return detail::functor2<vec, L, T, Q>::call(fmax, a, vec<L, T, Q>(b));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fmax(vec<L, T, Q> const& a, vec<L, T, Q> const& b)
	{
		return detail::functor2<vec, L, T, Q>::call(fmax, a, b);
	}

	// fclamp
	template<typename genType>
	GLM_FUNC_QUALIFIER genType fclamp(genType x, genType minVal, genType maxVal)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'fclamp' only accept floating-point or integer inputs");
		return fmin(fmax(x, minVal), maxVal);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fclamp(vec<L, T, Q> const& x, T minVal, T maxVal)
	{
		return fmin(fmax(x, vec<L, T, Q>(minVal)), vec<L, T, Q>(maxVal));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> fclamp(vec<L, T, Q> const& x, vec<L, T, Q> const& minVal, vec<L, T, Q> const& maxVal)
	{
		return fmin(fmax(x, minVal), maxVal);
	}
}//namespace glm
