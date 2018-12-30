/// @ref gtc_round

#include "../integer.hpp"

namespace glm{
namespace detail
{
	template<length_t L, typename T, qualifier Q, bool compute = false>
	struct compute_ceilShift
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T)
		{
			return v;
		}
	};

	template<length_t L, typename T, qualifier Q>
	struct compute_ceilShift<L, T, Q, true>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& v, T Shift)
		{
			return v | (v >> Shift);
		}
	};

	template<length_t L, typename T, qualifier Q, bool isSigned = true>
	struct compute_ceilPowerOfTwo
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			GLM_STATIC_ASSERT(!std::numeric_limits<T>::is_iec559, "'ceilPowerOfTwo' only accept integer scalar or vector inputs");

			vec<L, T, Q> const Sign(sign(x));

			vec<L, T, Q> v(abs(x));

			v = v - static_cast<T>(1);
			v = v | (v >> static_cast<T>(1));
			v = v | (v >> static_cast<T>(2));
			v = v | (v >> static_cast<T>(4));
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 2>::call(v, 8);
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 4>::call(v, 16);
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 8>::call(v, 32);
			return (v + static_cast<T>(1)) * Sign;
		}
	};

	template<length_t L, typename T, qualifier Q>
	struct compute_ceilPowerOfTwo<L, T, Q, false>
	{
		GLM_FUNC_QUALIFIER static vec<L, T, Q> call(vec<L, T, Q> const& x)
		{
			GLM_STATIC_ASSERT(!std::numeric_limits<T>::is_iec559, "'ceilPowerOfTwo' only accept integer scalar or vector inputs");

			vec<L, T, Q> v(x);

			v = v - static_cast<T>(1);
			v = v | (v >> static_cast<T>(1));
			v = v | (v >> static_cast<T>(2));
			v = v | (v >> static_cast<T>(4));
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 2>::call(v, 8);
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 4>::call(v, 16);
			v = compute_ceilShift<L, T, Q, sizeof(T) >= 8>::call(v, 32);
			return v + static_cast<T>(1);
		}
	};

	template<bool is_float, bool is_signed>
	struct compute_ceilMultiple{};

	template<>
	struct compute_ceilMultiple<true, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source > genType(0))
				return Source + (Multiple - std::fmod(Source, Multiple));
			else
				return Source + std::fmod(-Source, Multiple);
		}
	};

	template<>
	struct compute_ceilMultiple<false, false>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			genType Tmp = Source - genType(1);
			return Tmp + (Multiple - (Tmp % Multiple));
		}
	};

	template<>
	struct compute_ceilMultiple<false, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source > genType(0))
			{
				genType Tmp = Source - genType(1);
				return Tmp + (Multiple - (Tmp % Multiple));
			}
			else
				return Source + (-Source % Multiple);
		}
	};

	template<bool is_float, bool is_signed>
	struct compute_floorMultiple{};

	template<>
	struct compute_floorMultiple<true, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - std::fmod(Source, Multiple);
			else
				return Source - std::fmod(Source, Multiple) - Multiple;
		}
	};

	template<>
	struct compute_floorMultiple<false, false>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - Source % Multiple;
			else
			{
				genType Tmp = Source + genType(1);
				return Tmp - Tmp % Multiple - Multiple;
			}
		}
	};

	template<>
	struct compute_floorMultiple<false, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - Source % Multiple;
			else
			{
				genType Tmp = Source + genType(1);
				return Tmp - Tmp % Multiple - Multiple;
			}
		}
	};

	template<bool is_float, bool is_signed>
	struct compute_roundMultiple{};

	template<>
	struct compute_roundMultiple<true, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - std::fmod(Source, Multiple);
			else
			{
				genType Tmp = Source + genType(1);
				return Tmp - std::fmod(Tmp, Multiple) - Multiple;
			}
		}
	};

	template<>
	struct compute_roundMultiple<false, false>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - Source % Multiple;
			else
			{
				genType Tmp = Source + genType(1);
				return Tmp - Tmp % Multiple - Multiple;
			}
		}
	};

	template<>
	struct compute_roundMultiple<false, true>
	{
		template<typename genType>
		GLM_FUNC_QUALIFIER static genType call(genType Source, genType Multiple)
		{
			if(Source >= genType(0))
				return Source - Source % Multiple;
			else
			{
				genType Tmp = Source + genType(1);
				return Tmp - Tmp % Multiple - Multiple;
			}
		}
	};
}//namespace detail

	////////////////
	// isPowerOfTwo

	template<typename genType>
	GLM_FUNC_QUALIFIER bool isPowerOfTwo(genType Value)
	{
		genType const Result = glm::abs(Value);
		return !(Result & (Result - 1));
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isPowerOfTwo(vec<L, T, Q> const& Value)
	{
		vec<L, T, Q> const Result(abs(Value));
		return equal(Result & (Result - 1), vec<L, T, Q>(0));
	}

	//////////////////
	// ceilPowerOfTwo

	template<typename genType>
	GLM_FUNC_QUALIFIER genType ceilPowerOfTwo(genType value)
	{
		return detail::compute_ceilPowerOfTwo<1, genType, defaultp, std::numeric_limits<genType>::is_signed>::call(vec<1, genType, defaultp>(value)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> ceilPowerOfTwo(vec<L, T, Q> const& v)
	{
		return detail::compute_ceilPowerOfTwo<L, T, Q, std::numeric_limits<T>::is_signed>::call(v);
	}

	///////////////////
	// floorPowerOfTwo

	template<typename genType>
	GLM_FUNC_QUALIFIER genType floorPowerOfTwo(genType value)
	{
		return isPowerOfTwo(value) ? value : static_cast<genType>(1) << findMSB(value);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> floorPowerOfTwo(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(floorPowerOfTwo, v);
	}

	///////////////////
	// roundPowerOfTwo

	template<typename genIUType>
	GLM_FUNC_QUALIFIER genIUType roundPowerOfTwo(genIUType value)
	{
		if(isPowerOfTwo(value))
			return value;

		genIUType const prev = static_cast<genIUType>(1) << findMSB(value);
		genIUType const next = prev << static_cast<genIUType>(1);
		return (next - value) < (value - prev) ? next : prev;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> roundPowerOfTwo(vec<L, T, Q> const& v)
	{
		return detail::functor1<vec, L, T, T, Q>::call(roundPowerOfTwo, v);
	}

	////////////////
	// isMultiple

	template<typename genType>
	GLM_FUNC_QUALIFIER bool isMultiple(genType Value, genType Multiple)
	{
		return isMultiple(vec<1, genType>(Value), vec<1, genType>(Multiple)).x;
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isMultiple(vec<L, T, Q> const& Value, T Multiple)
	{
		return (Value % Multiple) == vec<L, T, Q>(0);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, bool, Q> isMultiple(vec<L, T, Q> const& Value, vec<L, T, Q> const& Multiple)
	{
		return (Value % Multiple) == vec<L, T, Q>(0);
	}

	//////////////////////
	// ceilMultiple

	template<typename genType>
	GLM_FUNC_QUALIFIER genType ceilMultiple(genType Source, genType Multiple)
	{
		return detail::compute_ceilMultiple<std::numeric_limits<genType>::is_iec559, std::numeric_limits<genType>::is_signed>::call(Source, Multiple);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> ceilMultiple(vec<L, T, Q> const& Source, vec<L, T, Q> const& Multiple)
	{
		return detail::functor2<vec, L, T, Q>::call(ceilMultiple, Source, Multiple);
	}

	//////////////////////
	// floorMultiple

	template<typename genType>
	GLM_FUNC_QUALIFIER genType floorMultiple(genType Source, genType Multiple)
	{
		return detail::compute_floorMultiple<std::numeric_limits<genType>::is_iec559, std::numeric_limits<genType>::is_signed>::call(Source, Multiple);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> floorMultiple(vec<L, T, Q> const& Source, vec<L, T, Q> const& Multiple)
	{
		return detail::functor2<vec, L, T, Q>::call(floorMultiple, Source, Multiple);
	}

	//////////////////////
	// roundMultiple

	template<typename genType>
	GLM_FUNC_QUALIFIER genType roundMultiple(genType Source, genType Multiple)
	{
		return detail::compute_roundMultiple<std::numeric_limits<genType>::is_iec559, std::numeric_limits<genType>::is_signed>::call(Source, Multiple);
	}

	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_QUALIFIER vec<L, T, Q> roundMultiple(vec<L, T, Q> const& Source, vec<L, T, Q> const& Multiple)
	{
		return detail::functor2<vec, L, T, Q>::call(roundMultiple, Source, Multiple);
	}
}//namespace glm
