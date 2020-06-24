// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_AUDIO_STREAM_LOADER_H_INCLUDED__
#define __I_IRRKLANG_AUDIO_STREAM_LOADER_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_IFileReader.h"

namespace irrklang
{

class IAudioStream;

//!	Class which is able to create an audio file stream from a file.
class IAudioStreamLoader : public IRefCounted
{
public:

	//! destructor
	virtual ~IAudioStreamLoader() {};

	//! Returns true if the file maybe is able to be loaded by this class.
	/** This decision should be based only on the file extension (e.g. ".wav"). The given
	filename string is guaranteed to be lower case. */
	virtual bool isALoadableFileExtension(const ik_c8* fileName) = 0;

	//! Creates an audio file input stream from a file
	/** \return Pointer to the created audio stream. Returns 0 if loading failed.
	If you no longer need the stream, you should call IAudioFileStream::drop().
	See IRefCounted::drop() for more information. */
	virtual IAudioStream* createAudioStream(IFileReader* file) = 0;
};


} // end namespace irrklang

#endif

