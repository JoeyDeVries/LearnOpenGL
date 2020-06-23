// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_AUDIO_STREAM_H_INCLUDED__
#define __I_IRRKLANG_AUDIO_STREAM_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_SAudioStreamFormat.h"

namespace irrklang
{


//!	Reads and decodes audio data into an usable audio stream for the ISoundEngine
class IAudioStream : public IRefCounted
{
public:

	//! destructor
	virtual ~IAudioStream() {};

	//! returns format of the audio stream
	virtual SAudioStreamFormat getFormat() = 0;

	//! sets the position of the audio stream.
	/** For example to let the stream be read from the beginning of the file again, 
	setPosition(0) would be called. This is usually done be the sound engine to
	loop a stream after if has reached the end. Return true if sucessful and 0 if not. 
	\param pos: Position in frames.*/
	virtual bool setPosition(ik_s32 pos) = 0;

	//! returns true if the audio stream is seekable
	/* Some file formats like (MODs) don't support seeking */
	virtual bool getIsSeekingSupported() { return true; }

    //! tells the audio stream to read frameCountToRead audio frames into the specified buffer
	/** \param target: Target data buffer to the method will write the read frames into. The
	specified buffer will be at least getFormat().getFrameSize()*frameCountToRead bytes big.
	\param frameCountToRead: amount of frames to be read.
	\returns Returns amount of frames really read. Should be frameCountToRead in most cases. */
	virtual ik_s32 readFrames(void* target, ik_s32 frameCountToRead) = 0;
};


} // end namespace irrklang

#endif

