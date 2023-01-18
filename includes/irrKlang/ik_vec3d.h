// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __IRR_IRRKLANG_VEC_3D_H_INCLUDED__
#define __IRR_IRRKLANG_VEC_3D_H_INCLUDED__

#include <math.h>
#include "ik_irrKlangTypes.h"


namespace irrklang
{

	//! a 3d vector template class for representing vectors and points in 3d
	template <class T>
	class vec3d
	{
	public:

		vec3d(): X(0), Y(0), Z(0) {};
		vec3d(T nx, T ny, T nz) : X(nx), Y(ny), Z(nz) {};
		vec3d(const vec3d<T>& other)	:X(other.X), Y(other.Y), Z(other.Z) {};

		//! constructor creating an irrklang vec3d from an irrlicht vector.
		#ifdef __IRR_POINT_3D_H_INCLUDED__
		template<class B>
		vec3d(const B& other)	:X(other.X), Y(other.Y), Z(other.Z) {};
		#endif // __IRR_POINT_3D_H_INCLUDED__

		// operators

		vec3d<T> operator-() const { return vec3d<T>(-X, -Y, -Z);   }

		vec3d<T>& operator=(const vec3d<T>& other)	{ X = other.X; Y = other.Y; Z = other.Z; return *this; }

		vec3d<T> operator+(const vec3d<T>& other) const { return vec3d<T>(X + other.X, Y + other.Y, Z + other.Z);	}
		vec3d<T>& operator+=(const vec3d<T>& other)	{ X+=other.X; Y+=other.Y; Z+=other.Z; return *this; }

		vec3d<T> operator-(const vec3d<T>& other) const { return vec3d<T>(X - other.X, Y - other.Y, Z - other.Z);	}
		vec3d<T>& operator-=(const vec3d<T>& other)	{ X-=other.X; Y-=other.Y; Z-=other.Z; return *this; }

		vec3d<T> operator*(const vec3d<T>& other) const { return vec3d<T>(X * other.X, Y * other.Y, Z * other.Z);	}
		vec3d<T>& operator*=(const vec3d<T>& other)	{ X*=other.X; Y*=other.Y; Z*=other.Z; return *this; }
		vec3d<T> operator*(const T v) const { return vec3d<T>(X * v, Y * v, Z * v);	}
		vec3d<T>& operator*=(const T v) { X*=v; Y*=v; Z*=v; return *this; }

		vec3d<T> operator/(const vec3d<T>& other) const { return vec3d<T>(X / other.X, Y / other.Y, Z / other.Z);	}
		vec3d<T>& operator/=(const vec3d<T>& other)	{ X/=other.X; Y/=other.Y; Z/=other.Z; return *this; }
		vec3d<T> operator/(const T v) const { T i=(T)1.0/v; return vec3d<T>(X * i, Y * i, Z * i);	}
		vec3d<T>& operator/=(const T v) { T i=(T)1.0/v; X*=i; Y*=i; Z*=i; return *this; }

		bool operator<=(const vec3d<T>&other) const { return X<=other.X && Y<=other.Y && Z<=other.Z;};
		bool operator>=(const vec3d<T>&other) const { return X>=other.X && Y>=other.Y && Z>=other.Z;};

		bool operator==(const vec3d<T>& other) const { return other.X==X && other.Y==Y && other.Z==Z; }
		bool operator!=(const vec3d<T>& other) const { return other.X!=X || other.Y!=Y || other.Z!=Z; }

		// functions

		//! returns if this vector equalsfloat the other one, taking floating point rounding errors into account
		bool equals(const vec3d<T>& other)
		{
			return equalsfloat(X, other.X) &&
				   equalsfloat(Y, other.Y) &&
				   equalsfloat(Z, other.Z);
		}

		void set(const T nx, const T ny, const T nz) {X=nx; Y=ny; Z=nz; }
		void set(const vec3d<T>& p) { X=p.X; Y=p.Y; Z=p.Z;}

		//! Returns length of the vector.
		ik_f64 getLength() const { return sqrt(X*X + Y*Y + Z*Z); }

		//! Returns squared length of the vector.
		/** This is useful because it is much faster then
		getLength(). */
		ik_f64 getLengthSQ() const { return X*X + Y*Y + Z*Z; }

		//! Returns the dot product with another vector.
		T dotProduct(const vec3d<T>& other) const
		{
			return X*other.X + Y*other.Y + Z*other.Z;
		}

		//! Returns distance from another point.
		/** Here, the vector is interpreted as point in 3 dimensional space. */
		ik_f64 getDistanceFrom(const vec3d<T>& other) const
		{
			ik_f64 vx = X - other.X; ik_f64 vy = Y - other.Y; ik_f64 vz = Z - other.Z;
			return sqrt(vx*vx + vy*vy + vz*vz);
		}

		//! Returns squared distance from another point.
		/** Here, the vector is interpreted as point in 3 dimensional space. */
		ik_f32 getDistanceFromSQ(const vec3d<T>& other) const
		{
			ik_f32 vx = X - other.X; ik_f32 vy = Y - other.Y; ik_f32 vz = Z - other.Z;
			return (vx*vx + vy*vy + vz*vz);
		}

		//! Calculates the cross product with another vector
		vec3d<T> crossProduct(const vec3d<T>& p) const
		{
			return vec3d<T>(Y * p.Z - Z * p.Y, Z * p.X - X * p.Z, X * p.Y - Y * p.X);
		}

		//! Returns if this vector interpreted as a point is on a line between two other points.
		/** It is assumed that the point is on the line. */
		bool isBetweenPoints(const vec3d<T>& begin, const vec3d<T>& end) const
		{
			ik_f32 f = (ik_f32)(end - begin).getLengthSQ();
			return (ik_f32)getDistanceFromSQ(begin) < f &&
				(ik_f32)getDistanceFromSQ(end) < f;
		}

		//! Normalizes the vector.
		vec3d<T>& normalize()
		{
			T l = (T)getLength();
			if (l == 0)
				return *this;

			l = (T)1.0 / l;
			X *= l;
			Y *= l;
			Z *= l;
			return *this;
		}

		//! Sets the length of the vector to a new value
		void setLength(T newlength)
		{
			normalize();
			*this *= newlength;
		}

		//! Inverts the vector.
		void invert()
		{
			X *= -1.0f;
			Y *= -1.0f;
			Z *= -1.0f;
		}

		//! Rotates the vector by a specified number of degrees around the Y
		//! axis and the specified center.
		//! \param degrees: Number of degrees to rotate around the Y axis.
		//! \param center: The center of the rotation.
		void rotateXZBy(ik_f64 degrees, const vec3d<T>& center)
		{
			degrees *= IK_DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			X -= center.X;
			Z -= center.Z;
			set(X*cs - Z*sn, Y, X*sn + Z*cs);
			X += center.X;
			Z += center.Z;
		}

		//! Rotates the vector by a specified number of degrees around the Z
		//! axis and the specified center.
		//! \param degrees: Number of degrees to rotate around the Z axis.
		//! \param center: The center of the rotation.
		void rotateXYBy(ik_f64 degrees, const vec3d<T>& center)
		{
			degrees *= IK_DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			X -= center.X;
			Y -= center.Y;
			set(X*cs - Y*sn, X*sn + Y*cs, Z);
			X += center.X;
			Y += center.Y;
		}

		//! Rotates the vector by a specified number of degrees around the X
		//! axis and the specified center.
		//! \param degrees: Number of degrees to rotate around the X axis.
		//! \param center: The center of the rotation.
		void rotateYZBy(ik_f64 degrees, const vec3d<T>& center)
		{
			degrees *= IK_DEGTORAD64;
			T cs = (T)cos(degrees);
			T sn = (T)sin(degrees);
			Z -= center.Z;
			Y -= center.Y;
			set(X, Y*cs - Z*sn, Y*sn + Z*cs);
			Z += center.Z;
			Y += center.Y;
		}

		//! Returns interpolated vector.
		/** \param other: other vector to interpolate between
		\param d: value between 0.0f and 1.0f. */
		vec3d<T> getInterpolated(const vec3d<T>& other, ik_f32 d) const
		{
			ik_f32 inv = 1.0f - d;
			return vec3d<T>(other.X*inv + X*d,
								other.Y*inv + Y*d,
								other.Z*inv + Z*d);
		}

		//! Gets the Y and Z rotations of a vector.
		/** Thanks to Arras on the Irrlicht forums to add this method.
		 \return A vector representing the rotation in degrees of
		this vector. The Z component of the vector will always be 0. */
		vec3d<T> getHorizontalAngle()
		{
			vec3d<T> angle;

			angle.Y = (T)atan2(X, Z);
			angle.Y *= (ik_f32)IK_RADTODEG;

			if (angle.Y < 0.0f) angle.Y += 360.0f;
			if (angle.Y >= 360.0f) angle.Y -= 360.0f;

			ik_f32 z1 = (T)sqrt(X*X + Z*Z);

			angle.X = (T)atan2(z1, Y);
			angle.X *= (ik_f32)IK_RADTODEG;
			angle.X -= 90.0f;

			if (angle.X < 0.0f) angle.X += 360.0f;
			if (angle.X >= 360) angle.X -= 360.0f;

			return angle;
		}

		//! Fills an array of 4 values with the vector data (usually floats).
		/** Useful for setting in shader constants for example. The fourth value
		 will always be 0. */
		void getAs4Values(T* array)
		{
			array[0] = X;
			array[1] = Y;
			array[2] = Z;
			array[3] = 0;
		}


		// member variables

		T X, Y, Z;
	};


	//! Typedef for a ik_f32 3d vector, a vector using floats for X, Y and Z
	typedef vec3d<ik_f32> vec3df;

	//! Typedef for an integer 3d vector, a vector using ints for X, Y and Z
	typedef vec3d<ik_s32> vec3di;

	template<class S, class T> vec3d<T> operator*(const S scalar, const vec3d<T>& vector) { return vector*scalar; }

} // end namespace irrklang


#endif

