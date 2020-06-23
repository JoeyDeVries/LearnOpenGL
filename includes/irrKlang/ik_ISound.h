// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_H_INCLUDED__
#define __I_IRRKLANG_SOUND_H_INCLUDED__

#include "ik_IVirtualRefCounted.h"
#include "ik_ISoundEffectControl.h"
#include "ik_vec3d.h"


namespace irrklang
{
	class ISoundSource;
	class ISoundStopEventReceiver;

	//! Represents a sound which is currently played.
	/** The sound can be stopped, its volume or pan changed, effects added/removed
	and similar using this interface.
	Creating sounds is done using ISoundEngine::play2D() or ISoundEngine::play3D(). 
	More informations about the source of a sound can be obtained from the ISoundSource
	interface. */
	class ISound : public IVirtualRefCounted
	{
	public:

		//! returns source of the sound which stores the filename and other informations about that sound
		/** \return Returns the sound source poitner of this sound. May return 0 if the sound source
		has been removed.*/
		virtual ISoundSource* getSoundSource() = 0;

		//! returns if the sound is paused
		virtual void setIsPaused( bool paused = true) = 0;

		//! returns if the sound is paused
		virtual bool getIsPaused() = 0;

		//! Will stop the sound and free its resources.
		/** If you just want to pause the sound, use setIsPaused().
		After calling stop(), isFinished() will usually return true. 
		Be sure to also call ->drop() once you are done.*/
		virtual void stop() = 0;

		//! returns volume of the sound, a value between 0 (mute) and 1 (full volume).
		/** (this volume gets multiplied with the master volume of the sound engine
		and other parameters like distance to listener when played as 3d sound)  */
		virtual ik_f32 getVolume() = 0;

		//! sets the volume of the sound, a value between 0 (mute) and 1 (full volume).
		/** This volume gets multiplied with the master volume of the sound engine
		and other parameters like distance to listener when played as 3d sound.  */
		virtual void setVolume(ik_f32 volume) = 0;

		//! sets the pan of the sound. Takes a value between -1 and 1, 0 is center.
		virtual void setPan(ik_f32 pan) = 0;

		//! returns the pan of the sound. Takes a value between -1 and 1, 0 is center.
		virtual ik_f32 getPan() = 0;

		//! returns if the sound has been started to play looped
		virtual bool isLooped() = 0;

		//! changes the loop mode of the sound. 
		/** If the sound is playing looped and it is changed to not-looped, then it 
		will stop playing after the loop has finished. 
		If it is not looped and changed to looped, the sound will start repeating to be 
		played when it reaches its end. 
		Invoking this method will not have an effect when the sound already has stopped. */
		virtual void setIsLooped(bool looped) = 0;

		//! returns if the sound has finished playing.
		/** Don't mix this up with isPaused(). isFinished() returns if the sound has been
		finished playing. If it has, is maybe already have been removed from the playing list of the
		sound engine and calls to any other of the methods of ISound will not have any result.
		If you call stop() to a playing sound will result that this function will return true
		when invoked. */
		virtual bool isFinished() = 0;

		//! Sets the minimal distance if this is a 3D sound.
		/** Changes the distance at which the 3D sound stops getting louder. This works
		like this: As a listener approaches a 3D sound source, the sound gets louder.
		Past a certain point, it is not reasonable for the volume to continue to increase.
		Either the maximum (zero) has been reached, or the nature of the sound source
		imposes a logical limit. This is the minimum distance for the sound source.
		Similarly, the maximum distance for a sound source is the distance beyond
		which the sound does not get any quieter.
		The default minimum distance is 1, the default max distance is a huge number like 1000000000.0f. */
		virtual void setMinDistance(ik_f32 min) = 0;

		//! Returns the minimal distance if this is a 3D sound.
		/** See setMinDistance() for details. */
		virtual ik_f32 getMinDistance() = 0;

		//! Sets the maximal distance if this is a 3D sound.
		/** Changing this value is usually not necessary. Use setMinDistance() instead.
		Don't change this value if you don't know what you are doing: This value causes the sound
		to stop attenuating after it reaches the max distance. Most people think that this sets the
		volume of the sound to 0 after this distance, but this is not true. Only change the
		minimal distance (using for example setMinDistance()) to influence this.
		The maximum distance for a sound source is the distance beyond which the sound does not get any quieter.
		The default minimum distance is 1, the default max distance is a huge number like 1000000000.0f. */
		virtual void setMaxDistance(ik_f32 max) = 0;

		//! Returns the maximal distance if this is a 3D sound.
		/** See setMaxDistance() for details. */
		virtual ik_f32 getMaxDistance() = 0;

		//! sets the position of the sound in 3d space
		virtual void setPosition(vec3df position) = 0;

		//! returns the position of the sound in 3d space
		virtual vec3df getPosition() = 0;

		//! sets the position of the sound in 3d space, needed for Doppler effects.
		/** To use doppler effects use ISound::setVelocity to set a sounds velocity, 
		ISoundEngine::setListenerPosition() to set the listeners velocity and 
		ISoundEngine::setDopplerEffectParameters() to adjust two parameters influencing 
		the doppler effects intensity. */
		virtual void setVelocity(vec3df vel) = 0;

		//! returns the velocity of the sound in 3d space, needed for Doppler effects.
		/** To use doppler effects use ISound::setVelocity to set a sounds velocity, 
		ISoundEngine::setListenerPosition() to set the listeners velocity and 
		ISoundEngine::setDopplerEffectParameters() to adjust two parameters influencing 
		the doppler effects intensity. */
		virtual vec3df getVelocity() = 0;

		//! returns the current play position of the sound in milliseconds.
		/** \return Returns -1 if not implemented or possible for this sound for example
		because it already has been stopped and freed internally or similar. */
		virtual ik_u32 getPlayPosition() = 0;

		//! sets the current play position of the sound in milliseconds.
        /** \param pos Position in milliseconds. Must be between 0 and the value returned
		by getPlayPosition().
		\return Returns true successful. False is returned for example if the sound already finished
		playing and is stopped or the audio source is not seekable, for example if it 
		is an internet stream or a a file format not supporting seeking (a .MOD file for example).
		A file can be tested if it can bee seeking using ISoundSource::getIsSeekingSupported(). */
		virtual bool setPlayPosition(ik_u32 pos) = 0;

		//! Sets the playback speed (frequency) of the sound.
		/** Plays the sound at a higher or lower speed, increasing or decreasing its
		frequency which makes it sound lower or higher.
		Note that this feature is not available on all sound output drivers (it is on the
		DirectSound drivers at least), and it does not work together with the 
		'enableSoundEffects' parameter of ISoundEngine::play2D and ISoundEngine::play3D when
		using DirectSound.
		\param speed Factor of the speed increase or decrease. 2 is twice as fast, 
		0.5 is only half as fast. The default is 1.0.
		\return Returns true if sucessful, false if not. The current sound driver might not
		support changing the playBack speed, or the sound was started with the 
		'enableSoundEffects' parameter. */
		virtual bool setPlaybackSpeed(ik_f32 speed = 1.0f) = 0;

		//! Returns the playback speed set by setPlaybackSpeed(). Default: 1.0f.
		/** See setPlaybackSpeed() for details */
		virtual ik_f32 getPlaybackSpeed() = 0;

		//! returns the play length of the sound in milliseconds.
		/** Returns -1 if not known for this sound for example because its decoder
		does not support length reporting or it is a file stream of unknown size.
		Note: You can also use ISoundSource::getPlayLength() to get the length of 
		a sound without actually needing to play it. */
		virtual ik_u32 getPlayLength() = 0;

		//! Returns the sound effect control interface for this sound.
		/** Sound effects such as Chorus, Distorsions, Echo, Reverb and similar can
		be controlled using this. The interface pointer is only valid as long as the ISound pointer is valid.
		If the ISound pointer gets dropped (IVirtualRefCounted::drop()), the ISoundEffects
		may not be used any more. 
		\return Returns a pointer to the sound effects interface if available. The sound
		has to be started via ISoundEngine::play2D() or ISoundEngine::play3D(),
		with the flag enableSoundEffects=true, otherwise 0 will be returned. Note that
		if the output driver does not support sound effects, 0 will be returned as well.*/
		virtual ISoundEffectControl* getSoundEffectControl() = 0;

		//! Sets the sound stop event receiver, an interface which gets called if a sound has finished playing.
		/** This event is guaranteed to be called when the sound or sound stream is finished,
		either because the sound reached its playback end, its sound source was removed,
		ISoundEngine::stopAllSounds() has been called or the whole engine was deleted.
		There is an example on how to use events in irrklang at @ref events .
		\param receiver Interface to a user implementation of the sound receiver. This interface
		should be as long valid as the sound exists or another stop event receiver is set.
		Set this to null to set no sound stop event receiver.
		\param userData: A iser data pointer, can be null. */
		virtual void setSoundStopEventReceiver(ISoundStopEventReceiver* reciever, void* userData=0) = 0;
	};

} // end namespace irrklang


#endif
