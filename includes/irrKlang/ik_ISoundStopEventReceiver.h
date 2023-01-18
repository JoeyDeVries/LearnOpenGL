// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_STOP_EVENT_RECEIVER_H_INCLUDED__
#define __I_IRRKLANG_SOUND_STOP_EVENT_RECEIVER_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_SAudioStreamFormat.h"


namespace irrklang
{


//! An enumeration listing all reasons for a fired sound stop event
enum E_STOP_EVENT_CAUSE
{
	//! The sound stop event was fired because the sound finished playing
	ESEC_SOUND_FINISHED_PLAYING = 0,

	//! The sound stop event was fired because the sound was stopped by the user, calling ISound::stop().
	ESEC_SOUND_STOPPED_BY_USER,

	//! The sound stop event was fired because the source of the sound was removed, for example
	//! because irrKlang was shut down or the user called ISoundEngine::removeSoundSource().
	ESEC_SOUND_STOPPED_BY_SOURCE_REMOVAL,

	//! This enumeration literal is never used, it only forces the compiler to 
	//! compile these enumeration values to 32 bit.
	ESEC_FORCE_32_BIT = 0x7fffffff
};


//! Interface to be implemented by the user, which receives sound stop events.
/** The interface has only one method to be implemented by the user: OnSoundStopped().
Implement this interface and set it via ISound::setSoundStopEventReceiver().
The sound stop event is guaranteed to be called when a sound or sound stream is finished,
either because the sound reached its playback end, its sound source was removed,
ISoundEngine::stopAllSounds() has been called or the whole engine was deleted. */
class ISoundStopEventReceiver
{
public:
    
	//! destructor
	virtual ~ISoundStopEventReceiver() {};

	//! Called when a sound has stopped playing. 
	/** This is the only method to be implemented by the user.
	The sound stop event is guaranteed to be called when a sound or sound stream is finished,
	either because the sound reached its playback end, its sound source was removed,
	ISoundEngine::stopAllSounds() has been called or the whole engine was deleted.
	Please note: Sound events will occur in a different thread when the engine runs in
	multi threaded mode (default). In single threaded mode, the event will happen while
	the user thread is calling ISoundEngine::update().
	\param sound: Sound which has been stopped. 
	\param reason: The reason why the sound stop event was fired. Usually, this will be ESEC_SOUND_FINISHED_PLAYING.
	When the sound was aborted by calling ISound::stop() or ISoundEngine::stopAllSounds();, this would be 
	ESEC_SOUND_STOPPED_BY_USER. If irrKlang was deleted or the sound source was removed, the value is 
	ESEC_SOUND_STOPPED_BY_SOURCE_REMOVAL.
	\param userData: userData pointer set by the user when registering the interface
	via ISound::setSoundStopEventReceiver(). */
	virtual void OnSoundStopped(ISound* sound, E_STOP_EVENT_CAUSE reason, void* userData) = 0;

};


} // end namespace irrklang


#endif

