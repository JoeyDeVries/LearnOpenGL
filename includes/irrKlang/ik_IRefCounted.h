// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_IREFERENCE_COUNTED_H_INCLUDED__
#define __I_IRRKLANG_IREFERENCE_COUNTED_H_INCLUDED__

#include "ik_irrKlangTypes.h"

namespace irrklang
{
	//! Base class of most objects of the irrKlang.
	/** This class provides reference counting through the methods grab() and drop().
	It also is able to store a debug string for every instance of an object.
	Most objects of irrKlang are derived from IRefCounted, and so they are reference counted.

	When you receive an object in irrKlang (for example an ISound using play2D() or
	play3D()), and you no longer need the object, you have 
	to call drop(). This will destroy the object, if grab() was not called
	in another part of you program, because this part still needs the object.
	Note, that you only don't need to call drop() for all objects you receive, it
	will be explicitly noted in the documentation.

	A simple example:

	If you want to play a sound, you may want to call the method
	ISoundEngine::play2D. You call
	ISound* mysound = engine->play2D("foobar.mp3", false, false true);
	If you no longer need the sound interface, call mysound->drop(). The 
	sound may still play on after this because the engine still has a reference
	to that sound, but you can be sure that it's memory will be released as soon
	the sound is no longer used.

	If you want to add a sound source, you may want to call a method
	ISoundEngine::addSoundSourceFromFile. You do this like
	ISoundSource* mysource = engine->addSoundSourceFromFile("example.jpg");
	You will not have to drop the pointer to the source, because
	sound sources are managed by the engine (it will live as long as the sound engine) and
	the documentation says so. 
	*/
	class IRefCounted
	{
	public:

		//! Constructor.
		IRefCounted()
			: ReferenceCounter(1)
		{
		}

		//! Destructor.
		virtual ~IRefCounted()
		{
		}

		//! Grabs the object. Increments the reference counter by one.
		//! Someone who calls grab() to an object, should later also call
		//! drop() to it. If an object never gets as much drop() as grab()
		//! calls, it will never be destroyed.
		//! The IRefCounted class provides a basic reference counting mechanism
		//! with its methods grab() and drop(). Most objects of irrklang
		//! are derived from IRefCounted, and so they are reference counted.
		//!
		//! When you receive an object in irrKlang (for example an ISound using play2D() or
		//! play3D()), and you no longer need the object, you have 
		//! to call drop(). This will destroy the object, if grab() was not called
		//! in another part of you program, because this part still needs the object.
		//! Note, that you only don't need to call drop() for all objects you receive, it
		//! will be explicitly noted in the documentation.
		//! 
		//! A simple example:
		//! 
		//! If you want to play a sound, you may want to call the method
		//! ISoundEngine::play2D. You call
		//! ISound* mysound = engine->play2D("foobar.mp3", false, false true);
		//! If you no longer need the sound interface, call mysound->drop(). The 
		//! sound may still play on after this because the engine still has a reference
		//! to that sound, but you can be sure that it's memory will be released as soon
		//! the sound is no longer used.
		void grab() { ++ReferenceCounter; }

		//! When you receive an object in irrKlang (for example an ISound using play2D() or
		//! play3D()), and you no longer need the object, you have 
		//! to call drop(). This will destroy the object, if grab() was not called
		//! in another part of you program, because this part still needs the object.
		//! Note, that you only don't need to call drop() for all objects you receive, it
		//! will be explicitly noted in the documentation.
		//! 
		//! A simple example:
		//! 
		//! If you want to play a sound, you may want to call the method
		//! ISoundEngine::play2D. You call
		//! ISound* mysound = engine->play2D("foobar.mp3", false, false true);
		//! If you no longer need the sound interface, call mysound->drop(). The 
		//! sound may still play on after this because the engine still has a reference
		//! to that sound, but you can be sure that it's memory will be released as soon
		//! the sound is no longer used.
		bool drop()
		{
			--ReferenceCounter;

			if (!ReferenceCounter)
			{
				delete this;
				return true;
			}

			return false;
		}

	private:

		ik_s32	ReferenceCounter;
	};

} // end namespace irr

#endif

