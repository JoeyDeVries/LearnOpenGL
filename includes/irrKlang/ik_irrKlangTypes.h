// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __IRRKLANG_TYPES_H_INCLUDED__
#define __IRRKLANG_TYPES_H_INCLUDED__


namespace irrklang
{

	//! 8 bit unsigned variable.
	/** This is a typedef for unsigned char, it ensures portability of the engine. */
	typedef unsigned char ik_u8;

	//! 8 bit signed variable.
	/** This is a typedef for signed char, it ensures portability of the engine. */
	typedef signed char	ik_s8;

	//! 8 bit character variable.
	/** This is a typedef for char, it ensures portability of the engine. */
	typedef char ik_c8;



	//! 16 bit unsigned variable.
	/** This is a typedef for unsigned short, it ensures portability of the engine. */
	typedef unsigned short ik_u16;

	//! 16 bit signed variable.
	/** This is a typedef for signed short, it ensures portability of the engine. */
	typedef signed short ik_s16;



	//! 32 bit unsigned variable.
	/** This is a typedef for unsigned int, it ensures portability of the engine. */
	typedef unsigned int ik_u32;

	//! 32 bit signed variable.
	/** This is a typedef for signed int, it ensures portability of the engine. */
	typedef signed int ik_s32;



	//! 32 bit floating point variable.
	/** This is a typedef for float, it ensures portability of the engine. */
	typedef float ik_f32;

	//! 64 bit floating point variable.
	/** This is a typedef for double, it ensures portability of the engine. */
	typedef double ik_f64;



    // some constants

	const ik_f32 IK_ROUNDING_ERROR_32	= 0.000001f;
	const ik_f64 IK_PI64			    = 3.1415926535897932384626433832795028841971693993751;
	const ik_f32 IK_PI32			    = 3.14159265359f;
	const ik_f32 IK_RADTODEG            = 180.0f / IK_PI32;
	const ik_f32 IK_DEGTORAD            = IK_PI32 / 180.0f;
	const ik_f64 IK_RADTODEG64          = 180.0 / IK_PI64;
	const ik_f64 IK_DEGTORAD64          = IK_PI64 / 180.0;

	//! returns if a float equals the other one, taking floating
	//! point rounding errors into account
	inline bool equalsfloat(const ik_f32 a, const ik_f32 b, const ik_f32 tolerance = IK_ROUNDING_ERROR_32)
	{
		return (a + tolerance > b) && (a - tolerance < b);
	}

} // end irrklang namespace

// ensure wchar_t type is existing for unicode support
#include <wchar.h>

// define the wchar_t type if not already built in.
#ifdef _MSC_VER  // microsoft compiler
	#ifndef _WCHAR_T_DEFINED
		//! A 16 bit wide character type.
		/**
			Defines the wchar_t-type.
			In VS6, its not possible to tell
			the standard compiler to treat wchar_t as a built-in type, and
			sometimes we just don't want to include the huge stdlib.h or wchar.h,
			so we'll use this.
		*/
		typedef unsigned short wchar_t;
		#define _WCHAR_T_DEFINED
	#endif // wchar is not defined
#endif // microsoft compiler


#endif // __IRR_TYPES_H_INCLUDED__

