namespace glm
{
	template<typename T>
	GLM_FUNC_QUALIFIER T min(T a, T b, T c)
	{
		return glm::min(glm::min(a, b), c);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T min(T a, T b, T c, T d)
	{
		return glm::min(glm::min(a, b), glm::min(c, d));
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T max(T a, T b, T c)
	{
		return glm::max(glm::max(a, b), c);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T max(T a, T b, T c, T d)
	{
		return glm::max(glm::max(a, b), glm::max(c, d));
	}

#	if GLM_HAS_CXX11_STL
		using std::fmin;
#	else
		template<typename T>
		GLM_FUNC_QUALIFIER T fmin(T a, T b)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

			if (isnan(a))
				return b;
			return min(a, b);
		}
#	endif

	template<typename T>
	GLM_FUNC_QUALIFIER T fmin(T a, T b, T c)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

		if (isnan(a))
			return fmin(b, c);
		if (isnan(b))
			return fmin(a, c);
		if (isnan(c))
			return min(a, b);
		return min(a, b, c);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T fmin(T a, T b, T c, T d)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmin' only accept floating-point input");

		if (isnan(a))
			return fmin(b, c, d);
		if (isnan(b))
			return min(a, fmin(c, d));
		if (isnan(c))
			return fmin(min(a, b), d);
		if (isnan(d))
			return min(a, b, c);
		return min(a, b, c, d);
	}


#	if GLM_HAS_CXX11_STL
		using std::fmax;
#	else
		template<typename T>
		GLM_FUNC_QUALIFIER T fmax(T a, T b)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

			if (isnan(a))
				return b;
			return max(a, b);
		}
#	endif

	template<typename T>
	GLM_FUNC_QUALIFIER T fmax(T a, T b, T c)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

		if (isnan(a))
			return fmax(b, c);
		if (isnan(b))
			return fmax(a, c);
		if (isnan(c))
			return max(a, b);
		return max(a, b, c);
	}

	template<typename T>
	GLM_FUNC_QUALIFIER T fmax(T a, T b, T c, T d)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'fmax' only accept floating-point input");

		if (isnan(a))
			return fmax(b, c, d);
		if (isnan(b))
			return max(a, fmax(c, d));
		if (isnan(c))
			return fmax(max(a, b), d);
		if (isnan(d))
			return max(a, b, c);
		return max(a, b, c, d);
	}
}//namespace glm
