namespace glm
{
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> next_float(vec<L, T, Q> const& x)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = next_float(x[i]);
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> next_float(vec<L, T, Q> const& x, int ULPs)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = next_float(x[i], ULPs);
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> next_float(vec<L, T, Q> const& x, vec<L, int, Q> const& ULPs)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = next_float(x[i], ULPs[i]);
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> prev_float(vec<L, T, Q> const& x)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prev_float(x[i]);
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> prev_float(vec<L, T, Q> const& x, int ULPs)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prev_float(x[i], ULPs);
		return Result;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> prev_float(vec<L, T, Q> const& x, vec<L, int, Q> const& ULPs)
	{
		vec<L, T, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = prev_float(x[i], ULPs[i]);
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int, Q> float_distance(vec<L, float, Q> const& x, vec<L, float, Q> const& y)
	{
		vec<L, int, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = float_distance(x[i], y[i]);
		return Result;
	}

	template<length_t L, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, int64, Q> float_distance(vec<L, double, Q> const& x, vec<L, double, Q> const& y)
	{
		vec<L, int64, Q> Result;
		for(length_t i = 0, n = Result.length(); i < n; ++i)
			Result[i] = float_distance(x[i], y[i]);
		return Result;
	}
}//namespace glm
