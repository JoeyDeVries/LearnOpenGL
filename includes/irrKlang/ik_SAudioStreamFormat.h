// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __S_IRRKLANG_AUDIO_STREAM_FORMAT_H_INCLUDED__
#define __S_IRRKLANG_AUDIO_STREAM_FORMAT_H_INCLUDED__

#include "ik_IRefCounted.h"


namespace irrklang
{

	//! audio sample data format enumeration for supported formats
	enum ESampleFormat
	{
		//! one unsigned byte (0;255)
		ESF_U8, 

		//! 16 bit, signed (-32k;32k)
		ESF_S16 
	};


	//! structure describing an audio stream format with helper functions
	struct SAudioStreamFormat
	{
		//! channels, 1 for mono, 2 for stereo
		ik_s32 ChannelCount; 

		//! amount of frames in the sample data or stream. 
		/** If the stream has an unknown lenght, this is -1 */
		ik_s32 FrameCount;		

		//! samples per second
		ik_s32 SampleRate;
		
		//! format of the sample data
		ESampleFormat SampleFormat;

		//! returns the size of a sample of the data described by the stream data in bytes
		inline ik_s32 getSampleSize() const
		{
			return (SampleFormat == ESF_U8) ? 1 : 2;
		}

		//! returns the frame size of the stream data in bytes
		inline ik_s32 getFrameSize() const
		{
			return ChannelCount * getSampleSize();
		}

		//! returns the size of the sample data in bytes
		/* Returns an invalid negative value when the stream has an unknown lenght */
		inline ik_s32 getSampleDataSize() const
		{
			return getFrameSize() * FrameCount;
		}

		//! returns amount of bytes per second
		inline ik_s32 getBytesPerSecond() const
		{
			return getFrameSize() * SampleRate;
		}
	};


} // end namespace irrklang

#endif

