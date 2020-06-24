// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_IRR_SOUND_SOURCE_H_INCLUDED__
#define __I_IRRKLANG_IRR_SOUND_SOURCE_H_INCLUDED__

#include "ik_IVirtualRefCounted.h"
#include "ik_vec3d.h"
#include "ik_EStreamModes.h"
#include "ik_SAudioStreamFormat.h"


namespace irrklang
{

	//! A sound source describes an input file (.ogg, .mp3, .wav or similar) and its default settings.
	/** It provides some informations about the sound source like the play lenght and
	can have default settings for volume, distances for 3d etc. There is some example code on how
	to use Sound sources at @ref soundSources.*/
	class ISoundSource : public IVirtualRefCounted
	{
	public:

		//! Returns the name of the sound source (usually, this is the file name)
		virtual const ik_c8* getName() = 0;

		//! Sets the stream mode which should be used for a sound played from this source.
		/** Note that if this is set to ESM_NO_STREAMING, the engine still might decide
		to stream the sound if it is too big. The threashold for this can be 
		adjusted using ISoundSource::setForcedStreamingThreshold(). */
		virtual void setStreamMode(E_STREAM_MODE mode) = 0;

		//! Returns the detected or set type of the sound with wich the sound will be played.
		/** Note: If the returned type is ESM_AUTO_DETECT, this mode will change after the
		sound has been played the first time. */
		virtual E_STREAM_MODE getStreamMode() = 0;

		//! Returns the play length of the sound in milliseconds.
		/** Returns -1 if not known for this sound for example because its decoder
		does not support lenght reporting or it is a file stream of unknown size.
		Note: If the sound never has been played before, the sound engine will have to open
		the file and try to get the play lenght from there, so this call could take a bit depending
		on the type of file. */
		virtual ik_u32 getPlayLength() = 0;

		//! Returns informations about the sound source: channel count (mono/stereo), frame count, sample rate, etc.
		/** \return Returns the structure filled with 0 or negative values if not known for this sound for example because 
		because the file could not be opened or similar.
		Note: If the sound never has been played before, the sound engine will have to open
		the file and try to get the play lenght from there, so this call could take a bit depending
		on the type of file. */
		virtual SAudioStreamFormat getAudioFormat() = 0;

		//! Returns if sounds played from this source will support seeking via ISound::setPlayPosition().
		/* If a sound is seekable depends on the file type and the audio format. For example MOD files
		cannot be seeked currently.
		\return Returns true of the sound source supports setPlayPosition() and false if not. 
		Note: If the sound never has been played before, the sound engine will have to open
		the file and try to get the information from there, so this call could take a bit depending
		on the type of file. */
		virtual bool getIsSeekingSupported() = 0;

		//! Sets the default volume for a sound played from this source.
		/** The default value of this is 1.0f. 
		Note that the default volume is being multiplied with the master volume
		of ISoundEngine, change this via ISoundEngine::setSoundVolume(). 
		//! \param volume 0 (silent) to 1.0f (full volume). Default value is 1.0f. */
		virtual void setDefaultVolume(ik_f32 volume=1.0f) = 0;

		//! Returns the default volume for a sound played from this source.
		/** You can influence this default volume value using setDefaultVolume().
		Note that the default volume is being multiplied with the master volume
		of ISoundEngine, change this via ISoundEngine::setSoundVolume(). 
		//! \return 0 (silent) to 1.0f (full volume). Default value is 1.0f. */
		virtual ik_f32 getDefaultVolume() = 0;

		//! sets the default minimal distance for 3D sounds played from this source.
		/**  This value influences how loud a sound is heard based on its distance.
		See ISound::setMinDistance() for details about what the min distance is.
		This method only influences the initial distance value of sounds. For changing the
		distance while the sound is playing, use ISound::setMinDistance() and ISound::setMaxDistance().
		\param minDistance: Default minimal distance for 3D sounds from this source. Set it to a negative
		value to let sounds of this source use the engine level default min distance, which
		can be set via ISoundEngine::setDefault3DSoundMinDistance(). Default value is -1, causing
		the default min distance of the sound engine to take effect. */
		virtual void setDefaultMinDistance(ik_f32 minDistance) = 0;

		//! Returns the default minimal distance for 3D sounds played from this source.
		/**  This value influences how loud a sound is heard based on its distance.
		See ISound::setMinDistance() for details about what the minimal distance is.
		\return Default minimal distance for 3d sounds from this source. If setDefaultMinDistance()
		was set to a negative value, it will return the default value set in the engine,
		using ISoundEngine::setDefault3DSoundMinDistance(). Default value is -1, causing
		the default min distance of the sound engine to take effect. */
		virtual ik_f32 getDefaultMinDistance() = 0;

		//! Sets the default maximal distance for 3D sounds played from this source.
		/**  Changing this value is usually not necessary. Use setDefaultMinDistance() instead.
		Don't change this value if you don't know what you are doing: This value causes the sound
		to stop attenuating after it reaches the max distance. Most people think that this sets the
		volume of the sound to 0 after this distance, but this is not true. Only change the
		minimal distance (using for example setDefaultMinDistance()) to influence this.
		See ISound::setMaxDistance() for details about what the max distance is.
		This method only influences the initial distance value of sounds. For changing the
		distance while the sound is played, use ISound::setMinDistance() 
		and ISound::setMaxDistance().
		\param maxDistance Default maximal distance for 3D sounds from this source. Set it to a negative
		value to let sounds of this source use the engine level default max distance, which
		can be set via ISoundEngine::setDefault3DSoundMaxDistance(). Default value is -1, causing
		the default max distance of the sound engine to take effect. */
		virtual void setDefaultMaxDistance(ik_f32 maxDistance) = 0;

		//! returns the default maxmial distance for 3D sounds played from this source.
		/** This value influences how loud a sound is heard based on its distance.
		Changing this value is usually not necessary. Use setDefaultMinDistance() instead.
		Don't change this value if you don't know what you are doing: This value causes the sound
		to stop attenuating after it reaches the max distance. Most people think that this sets the
		volume of the sound to 0 after this distance, but this is not true. Only change the
		minimal distance (using for example setDefaultMinDistance()) to influence this.
		See ISound::setMaxDistance() for details about what the max distance is.
		\return Default maximal distance for 3D sounds from this source. If setDefaultMaxDistance()
		was set to a negative value, it will return the default value set in the engine,
		using ISoundEngine::setDefault3DSoundMaxDistance(). Default value is -1, causing
		the default max distance of the sound engine to take effect. */
		virtual ik_f32 getDefaultMaxDistance() = 0;

		//! Forces the sound to be reloaded at next replay.
		/** Sounds which are not played as streams are buffered to make it possible to
		replay them without much overhead. If the sound file is altered after the sound
		has been played the first time, the engine won't play the changed file then.
		Calling this method makes the engine reload the file before the file is played
		the next time.*/
		virtual void forceReloadAtNextUse() = 0;

		//! Sets the threshold size where irrKlang decides to force streaming a file independent of the user specified setting.
		/** When specifying ESM_NO_STREAMING for playing back a sound file, irrKlang will
		ignore this setting if the file is bigger than this threshold and stream the file
		anyway. Please note that if an audio format loader is not able to return the 
		size of a sound source and returns -1 as length, this will be ignored as well 
		and streaming has to be forced.
		\param threshold: New threshold. The value is specified in uncompressed bytes and its default value is 
		about one Megabyte. Set to 0 or a negative value to disable stream forcing. */
		virtual void setForcedStreamingThreshold(ik_s32 thresholdBytes) = 0;

		//! Returns the threshold size where irrKlang decides to force streaming a file independent of the user specified setting.
		/**  The value is specified in uncompressed bytes and its default value is 
		about one Megabyte. See setForcedStreamingThreshold() for details. */
		virtual ik_s32 getForcedStreamingThreshold() = 0;

		//! Returns a pointer to the loaded and decoded sample data.
		/** \return Returns a pointer to the sample data. The data is provided in decoded PCM data. The
		exact format can be retrieved using getAudioFormat(). Use getAudioFormat().getSampleDataSize()
		for getting the amount of bytes. The returned pointer will only be valid as long as the sound
		source exists.
		This function will only return a pointer to the data if the 
		audio file is not streamed, namely ESM_NO_STREAMING. Otherwise this function will return 0.
		Note: If the sound never has been played before, the sound engine will have to open
		the file and decode audio data from there, so this call could take a bit depending
		on the type of the file.*/
		virtual void* getSampleData() = 0;
	};

} // end namespace irrklang


#endif
