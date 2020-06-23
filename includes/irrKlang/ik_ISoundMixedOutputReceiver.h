// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_MIXED_OUTPUT_RECEIVER_H_INCLUDED__
#define __I_IRRKLANG_SOUND_MIXED_OUTPUT_RECEIVER_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_SAudioStreamFormat.h"


namespace irrklang
{


//! Interface to be implemented by the user, which recieves the mixed output when it it played by the sound engine.
/** This can be used to store the sound output as .wav file or for creating a Oscillograph or similar. 
 Simply implement your own class derived from ISoundMixedOutputReceiver and use ISoundEngine::setMixedDataOutputReceiver
 to let the audio driver know about it. */
class ISoundMixedOutputReceiver
{
public:
    
	//! destructor
	virtual ~ISoundMixedOutputReceiver() {};

	//! Called when a chunk of sound has been mixed and is about to be played. 
	/** Note: This is called from the playing thread of the sound library, so you need to 
	make everything you are doing in this method thread safe. Additionally, it would
	be a good idea to do nothing complicated in your implementation and return as fast as possible,
	otherwise sound output may be stuttering.
	\param data representing the sound frames which just have been mixed. Sound data always
	consists of two interleaved sound channels at 16bit per frame. 
	 \param byteCount Amount of bytes of the data 
	 \param playbackrate The playback rate at samples per second (usually something like 44000). 
	 This value will not change and always be the same for an instance of an ISoundEngine. */
	virtual void OnAudioDataReady(const void* data, int byteCount, int playbackrate) = 0;

};


} // end namespace irrklang


#endif

