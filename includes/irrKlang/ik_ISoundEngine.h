// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_ENGINE_H_INCLUDED__
#define __I_IRRKLANG_SOUND_ENGINE_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_vec3d.h"
#include "ik_ISoundSource.h"
#include "ik_ISound.h"
#include "ik_EStreamModes.h"
#include "ik_IFileFactory.h"
#include "ik_ISoundMixedOutputReceiver.h"


namespace irrklang
{
	class IAudioStreamLoader;
	struct SInternalAudioInterface;

	//! Interface to the sound engine, for playing 3d and 2d sound and music.
	/** This is the main interface of irrKlang. You usually would create this using
	the createIrrKlangDevice() function. 
	*/
	class ISoundEngine : public virtual irrklang::IRefCounted
	{
	public:

		//! returns the name of the sound driver, like 'ALSA' for the alsa device
		/** Possible returned strings are "NULL", "ALSA", "CoreAudio", "winMM", 
		"DirectSound" and "DirectSound8". */
		virtual const char* getDriverName() = 0;

		//! loads a sound source (if not loaded already) from a file and plays it.
		/** \param sourceFileName Filename of sound, like "sounds/test.wav" or "foobar.ogg".
		 \param playLooped plays the sound in loop mode. If set to 'false', the sound is played once, then stopped and deleted from the internal playing list. Calls to
		 ISound have no effect after such a non looped sound has been stopped automatically.
		 \param startPaused starts the sound paused. This implies that track=true. Use this if you want to modify some of the playing
		 parameters before the sound actually plays. Usually you would set this parameter to true, then use the ISound interface to
		 modify some of the sound parameters and then call ISound::setPaused(false);
		 Note: You need to call ISound::drop() when setting this parameter to true and you don't need the ISound
		 object anymore. See 'return' for details.
		 \param track Makes it possible to track the sound. Causes the method to return an ISound interface. See 'return' for details.
		 \param streamMode Specifies if the file should be streamed or loaded completely into memory for playing.
		 ESM_AUTO_DETECT sets this to autodetection. Note: if the sound has been loaded or played before into the
		 engine, this parameter has no effect.
		 \param enableSoundEffects Makes it possible to use sound effects such as chorus, distortions, echo, 
		 reverb and similar for this sound. Sound effects can then be controlled via ISound::getSoundEffectControl().
		 Only enable if necessary. 
		 \return Only returns a pointer to an ISound if the parameters 'track', 'startPaused' or 
		 'enableSoundEffects' have been	 set to true. Note: if this method returns an ISound as result, 
		 you HAVE to call ISound::drop() after you don't need the ISound interface anymore. Otherwise this 
		 will cause memory waste. This method also may return 0 although 'track', 'startPaused' or 
		 'enableSoundEffects' have been set to true, if the sound could not be played.*/
		virtual ISound* play2D(const char* soundFileName, 
							   bool playLooped = false,
							   bool startPaused = false, 
							   bool track = false,
							   E_STREAM_MODE streamMode = ESM_AUTO_DETECT,
							   bool enableSoundEffects = false) = 0;

		//! Plays a sound source as 2D sound with its default settings stored in ISoundSource.
		/** An ISoundSource object will be created internally when playing a sound the first time,
		or can be added with getSoundSource().
		\param source The sound source, specifying sound file source and default settings for this file.
		Use the other ISoundEngine::play2D() overloads if you want to specify a filename string instead of this.
		\param playLooped plays the sound in loop mode. If set to 'false', the sound is played once, then stopped and deleted from the internal playing list. Calls to
		 ISound have no effect after such a non looped sound has been stopped automatically.
		\param startPaused starts the sound paused. This implies that track=true. Use this if you want to modify some of the playing
		 parameters before the sound actually plays. Usually you would set this parameter to true, then use the ISound interface to
		 modify some of the sound parameters and then call ISound::setPaused(false);
		 Note: You need to call ISound::drop() when setting this parameter to true and you don't need the ISound
		 object anymore. See 'return' for details.
		 \param track Makes it possible to track the sound. Causes the method to return an ISound interface. See 'return' for details.
		 \param enableSoundEffects Makes it possible to use sound effects such as chorus, distortions, echo, 
		 reverb and similar for this sound. Sound effects can then be controlled via ISound::getSoundEffectControl().
		 Only enable if necessary. 
		 \return Only returns a pointer to an ISound if the parameters 'track', 'startPaused' or 
		 'enableSoundEffects' have been	 set to true. Note: if this method returns an ISound as result, 
		 you HAVE to call ISound::drop() after you don't need the ISound interface anymore. Otherwise this 
		 will cause memory waste. This method also may return 0 although 'track', 'startPaused' or 
		 'enableSoundEffects' have been set to true, if the sound could not be played.*/
		virtual ISound* play2D(ISoundSource* source, 
							   bool playLooped = false,
							   bool startPaused = false, 
							   bool track = false,
							   bool enableSoundEffects = false) = 0;

		//! Loads a sound source (if not loaded already) from a file and plays it as 3D sound.
		/** There is some example code on how to work with 3D sound at @ref sound3d.
		\param sourceFileName Filename of sound, like "sounds/test.wav" or "foobar.ogg".
		 \param pos Position of the 3D sound.
		 \param playLooped plays the sound in loop mode. If set to 'false', the sound is played once, then stopped and deleted from the internal playing list. Calls to
		 ISound have no effect after such a non looped sound has been stopped automatically.
		 \param startPaused starts the sound paused. This implies that track=true. Use this if you want to modify some of the playing
		 parameters before the sound actually plays. Usually you would set this parameter to true, then use the ISound interface to
		 modify some of the sound parameters and then call ISound::setPaused(false);
		 Note: You need to call ISound::drop() when setting this parameter to true and you don't need the ISound
		 object anymore. See 'return' for details.
		 \param track Makes it possible to track the sound. Causes the method to return an ISound interface. See 'return' for details.
 		 \param streamMode Specifies if the file should be streamed or loaded completely into memory for playing.
		 ESM_AUTO_DETECT sets this to autodetection. Note: if the sound has been loaded or played before into the
		 engine, this parameter has no effect.
		 \param enableSoundEffects Makes it possible to use sound effects such as chorus, distortions, echo, 
		 reverb and similar for this sound. Sound effects can then be controlled via ISound::getSoundEffectControl().
		 Only enable if necessary. 
		 \return Only returns a pointer to an ISound if the parameters 'track', 'startPaused' or 
		 'enableSoundEffects' have been	 set to true. Note: if this method returns an ISound as result, 
		 you HAVE to call ISound::drop() after you don't need the ISound interface anymore. Otherwise this 
		 will cause memory waste. This method also may return 0 although 'track', 'startPaused' or 
		 'enableSoundEffects' have been set to true, if the sound could not be played.*/
		virtual ISound* play3D(const char* soundFileName, vec3df pos,
							   bool playLooped = false, 
							   bool startPaused = false,
							   bool track = false, 
							   E_STREAM_MODE streamMode = ESM_AUTO_DETECT,
							   bool enableSoundEffects = false) = 0;

		//! Plays a sound source as 3D sound with its default settings stored in ISoundSource.
		/** An ISoundSource object will be created internally when playing a sound the first time,
		or can be added with getSoundSource(). There is some example code on how to work with 3D sound @ref sound3d.
		\param source The sound source, specifying sound file source and default settings for this file.
		Use the other ISoundEngine::play2D() overloads if you want to specify a filename string instead of this.
		\param pos Position of the 3D sound.
		\param playLooped plays the sound in loop mode. If set to 'false', the sound is played once, then stopped and deleted from the internal playing list. Calls to
		 ISound have no effect after such a non looped sound has been stopped automatically.
		\param startPaused starts the sound paused. This implies that track=true. Use this if you want to modify some of the playing
		 parameters before the sound actually plays. Usually you would set this parameter to true, then use the ISound interface to
		 modify some of the sound parameters and then call ISound::setPaused(false);
		 Note: You need to call ISound::drop() when setting this parameter to true and you don't need the ISound
		 object anymore. See 'return' for details.
		 \param track Makes it possible to track the sound. Causes the method to return an ISound interface. See 'return' for details.
		 \param enableSoundEffects Makes it possible to use sound effects such as chorus, distortions, echo, 
		 reverb and similar for this sound. Sound effects can then be controlled via ISound::getSoundEffectControl().
		 Only enable if necessary. 
		 \return Only returns a pointer to an ISound if the parameters 'track', 'startPaused' or 
		 'enableSoundEffects' have been	 set to true. Note: if this method returns an ISound as result, 
		 you HAVE to call ISound::drop() after you don't need the ISound interface anymore. Otherwise this 
		 will cause memory waste. This method also may return 0 although 'track', 'startPaused' or 
		 'enableSoundEffects' have been set to true, if the sound could not be played.*/
		virtual ISound* play3D(ISoundSource* source, vec3df pos,
							   bool playLooped = false, 
							   bool startPaused = false, 
							   bool track = false,
							   bool enableSoundEffects = false) = 0;

		//! Stops all currently playing sounds.
		virtual void stopAllSounds() = 0;

        //! Pauses or unpauses all currently playing sounds.
		virtual void setAllSoundsPaused( bool bPaused = true ) = 0;

		//! Gets a sound source by sound name. Adds the sound source as file into the sound engine if not loaded already.
		/** Please note: For performance reasons most ISoundEngine implementations will
		not try to load the sound when calling this method, but only when play() is called
		with this sound source as parameter. 
		\param addIfNotFound if 'true' adds the sound source to the list and returns the interface to it
		if it cannot be found in the sound source list. If 'false', returns 0 if the sound
		source is not in the list and does not modify the list. Default value: true.
		\return Returns the sound source or 0 if not available.
		Note: Don't call drop() to this pointer, it will be managed by irrKlang and
		exist as long as you don't delete irrKlang or call removeSoundSource(). However,
		you are free to call grab() if you want and drop() it then later of course. */
		virtual ISoundSource* getSoundSource(const ik_c8* soundName, bool addIfNotFound=true) = 0;

		//! Returns a sound source by index.
		/** \param idx: Index of the loaded sound source, must by smaller than getSoundSourceCount().
		\return Returns the sound source or 0 if not available.
		Note: Don't call drop() to this pointer, it will be managed by irrKlang and
		exist as long as you don't delete irrKlang or call removeSoundSource(). However,
		you are free to call grab() if you want and drop() it then later of course. */	
		virtual ISoundSource* getSoundSource(ik_s32 index) = 0;

		//! Returns amount of loaded sound sources.
		virtual ik_s32 getSoundSourceCount() = 0;

		//! Adds sound source into the sound engine as file.
		/** \param fileName Name of the sound file (e.g. "sounds/something.mp3"). You can also use this
		name when calling play3D() or play2D().
		\param mode Streaming mode for this sound source
		\param preload If this flag is set to false (which is default) the sound engine will
		not try to load the sound file when calling this method, but only when play() is called
		with this sound source as parameter. Otherwise the sound will be preloaded.
		\return Returns the pointer to the added sound source or 0 if not successful because for
		example a sound already existed with that name. If not successful, the reason will be printed
		into the log. Note: Don't call drop() to this pointer, it will be managed by irrKlang and
		exist as long as you don't delete irrKlang or call removeSoundSource(). However,
		you are free to call grab() if you want and drop() it then later of course. */	
		virtual ISoundSource* addSoundSourceFromFile(const ik_c8* fileName, E_STREAM_MODE mode=ESM_AUTO_DETECT,
			                                         bool preload=false) = 0;

		//! Adds a sound source into the sound engine as memory source.
		/** Note: This method only accepts a file (.wav, .ogg, etc) which is totally loaded into memory.
		If you want to add a sound source from decoded plain PCM data in memory, use addSoundSourceFromPCMData() instead.
		\param memory Pointer to the memory to be treated as loaded sound file.
		\param sizeInBytes Size of the memory chunk, in bytes.
		\param soundName Name of the virtual sound file (e.g. "sounds/something.mp3"). You can also use this
		name when calling play3D() or play2D(). Hint: If you include the extension of the original file
		like .ogg, .mp3 or .wav at the end of the filename, irrKlang will be able to decide better what
		file format it is and might be able to start playback faster.
		\param copyMemory If set to true which is default, the memory block is copied 
		and stored in the engine, after	calling addSoundSourceFromMemory() the memory pointer can be deleted
		savely. If set to false, the memory is not copied and the user takes the responsibility that 
		the memory block pointed to remains there as long as the sound engine or at least this sound
		source exists.
		\return Returns the pointer to the added sound source or 0 if not successful because for example a sound already
		existed with that name. If not successful, the reason will be printed into the log. 
		Note: Don't call drop() to this pointer, it will be managed by irrKlang and exist as long as you don't 
		delete irrKlang or call removeSoundSource(). However, you are free to call grab() if you
		want and drop() it then later of course. */
		virtual ISoundSource* addSoundSourceFromMemory(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName,
											               bool copyMemory=true) = 0;


		//! Adds a sound source into the sound engine from plain PCM data in memory.
		/** \param memory Pointer to the memory to be treated as loaded sound file.
		\param sizeInBytes Size of the memory chunk, in bytes. 
		\param soundName Name of the virtual sound file (e.g. "sounds/something.mp3"). You can also use this
		name when calling play3D() or play2D(). 
		\param copyMemory If set to true which is default, the memory block is copied 
		and stored in the engine, after	calling addSoundSourceFromPCMData() the memory pointer can be deleted
		savely. If set to true, the memory is not copied and the user takes the responsibility that 
		the memory block pointed to remains there as long as the sound engine or at least this sound
		source exists. 
		\return Returns the pointer to the added sound source or 0 if not successful because for
		example a sound already existed with that name. If not successful, the reason will be printed
		into the log. */
		virtual ISoundSource* addSoundSourceFromPCMData(void* memory, ik_s32 sizeInBytes, 
			                                            const ik_c8* soundName, SAudioStreamFormat format,
														bool copyMemory=true) = 0;

		//! Adds a sound source as alias for an existing sound source, but with a different name or optional different default settings.
		/** This is useful if you want to play multiple sounds but each sound isn't necessarily one single file.
		Also useful if you want to or play the same sound using different names, volumes or min and max 3D distances.
		\param baseSource The sound source where this sound source should be based on. This sound
		source will use the baseSource as base to access the file and similar, but it will have its
		own name and its own default settings.
		\param soundName Name of the new sound source to be added.
		\return Returns the pointer to the added sound source or 0 if not successful because for
		example a sound already existed with that name. If not successful, the reason will be printed
		into the log.*/
		virtual ISoundSource* addSoundSourceAlias(ISoundSource* baseSource, const ik_c8* soundName) = 0;

		//! Removes a sound source from the engine, freeing the memory it occupies.
		/** This will also cause all currently playing sounds of this source to be stopped. 
		Also note that if the source has been removed successfully, the value returned 
		by getSoundSourceCount() will have been decreased by one. 
		Removing sound sources is only necessary if you know you won't use a lot of non-streamed
		sounds again. Sound sources of streamed sounds do not cost a lot of memory.*/
		virtual void removeSoundSource(ISoundSource* source) = 0;

		//! Removes a sound source from the engine, freeing the memory it occupies.
		/** This will also cause all currently playing sounds of this source to be stopped. 
		Also note that if the source has been removed successfully, the value returned 
		by getSoundSourceCount() will have been decreased by one. 
		Removing sound sources is only necessary if you know you won't use a lot of non-streamed
		sounds again. Sound sources of streamed sounds do not cost a lot of memory. */
		virtual void removeSoundSource(const ik_c8* name) = 0;

		//! Removes all sound sources from the engine
		/** This will also cause all sounds to be stopped. 
		Removing sound sources is only necessary if you know you won't use a lot of non-streamed
		sounds again. Sound sources of streamed sounds do not cost a lot of memory. */
		virtual void removeAllSoundSources() = 0;

		//! Sets master sound volume. This value is multiplied with all sounds played.
		/** \param volume 0 (silent) to 1.0f (full volume) */
		virtual void setSoundVolume(ik_f32 volume) = 0;

		//! Returns master sound volume.
		/* A value between 0.0 and 1.0. Default is 1.0. Can be changed using setSoundVolume(). */
		virtual ik_f32 getSoundVolume() = 0;

		//! Sets the current listener 3d position.
		/** When playing sounds in 3D, updating the position of the listener every frame should be
		done using this function.
		\param pos Position of the camera or listener.
		\param lookdir Direction vector where the camera or listener is looking into. If you have a 
		camera position and a target 3d point where it is looking at, this would be cam->getTarget() - cam->getAbsolutePosition().
		\param velPerSecond The velocity per second describes the speed of the listener and 
		is only needed for doppler effects.
		\param upvector Vector pointing 'up', so the engine can decide where is left and right. 
		This vector is usually (0,1,0).*/
		virtual void setListenerPosition(const vec3df& pos,
			const vec3df& lookdir,
			const vec3df& velPerSecond = vec3df(0,0,0),
			const vec3df& upVector = vec3df(0,1,0)) = 0;

		//! Updates the audio engine. This should be called several times per frame if irrKlang was started in single thread mode.
		/** This updates the 3d positions of the sounds as well as their volumes, effects,
		streams and other stuff. Call this several times per frame (the more the better) if you
		specified irrKlang to run single threaded. Otherwise it is not necessary to use this method.
		This method is being called by the scene manager automatically if you are using one, so
		you might want to ignore this. */
		virtual void update() = 0;

		//! Returns if a sound with the specified name is currently playing.
		virtual bool isCurrentlyPlaying(const char* soundName) = 0;

		//! Returns if a sound with the specified source is currently playing.
		virtual bool isCurrentlyPlaying(ISoundSource* source) = 0;

		//! Stops all sounds of a specific sound source
		virtual void stopAllSoundsOfSoundSource(ISoundSource* source) = 0;

		//! Registers a new audio stream loader in the sound engine.
		/** Use this to enhance the audio engine to support other or new file formats.
		To do this, implement your own IAudioStreamLoader interface and register it
		with this method */
		virtual void registerAudioStreamLoader(IAudioStreamLoader* loader) = 0;

		//! Returns if irrKlang is running in the same thread as the application or is using multithreading.
		/** This basically returns the flag set by the user when creating the sound engine.*/
		virtual bool isMultiThreaded() const = 0;

		//! Adds a file factory to the sound engine, making it possible to override file access of the sound engine.
		/** Derive your own class from IFileFactory, overwrite the createFileReader()
		method and return your own implemented IFileReader to overwrite file access of irrKlang. */
		virtual void addFileFactory(IFileFactory* fileFactory) = 0;

		//! Sets the default minimal distance for 3D sounds.
		/**  This value influences how loud a sound is heard based on its distance.
		See ISound::setMinDistance() for details about what the min distance is.
		It is also possible to influence this default value for every sound file 
		using ISoundSource::setDefaultMinDistance().
		This method only influences the initial distance value of sounds. For changing the
		distance after the sound has been started to play, use ISound::setMinDistance() and ISound::setMaxDistance().
		\param minDistance Default minimal distance for 3d sounds. The default value is 1.0f.*/
		virtual void setDefault3DSoundMinDistance(ik_f32 minDistance) = 0;

		//! Returns the default minimal distance for 3D sounds.
		/**  This value influences how loud a sound is heard based on its distance.
		You can change it using setDefault3DSoundMinDistance().
		See ISound::setMinDistance() for details about what the min distance is.
		It is also possible to influence this default value for every sound file 
		using ISoundSource::setDefaultMinDistance().
		\return Default minimal distance for 3d sounds. The default value is 1.0f. */
		virtual ik_f32 getDefault3DSoundMinDistance() = 0;

		//! Sets the default maximal distance for 3D sounds.
		/** Changing this value is usually not necessary. Use setDefault3DSoundMinDistance() instead.
		Don't change this value if you don't know what you are doing: This value causes the sound
		to stop attenuating after it reaches the max distance. Most people think that this sets the
		volume of the sound to 0 after this distance, but this is not true. Only change the
		minimal distance (using for example setDefault3DSoundMinDistance()) to influence this.
		See ISound::setMaxDistance() for details about what the max distance is.
		It is also possible to influence this default value for every sound file 
		using ISoundSource::setDefaultMaxDistance().
		This method only influences the initial distance value of sounds. For changing the
		distance after the sound has been started to play, use ISound::setMinDistance() and ISound::setMaxDistance().
		\param maxDistance Default maximal distance for 3d sounds. The default value is 1000000000.0f. */
		virtual void setDefault3DSoundMaxDistance(ik_f32 maxDistance) = 0;

		//! Returns the default maximal distance for 3D sounds.
		/**  This value influences how loud a sound is heard based on its distance.
		You can change it using setDefault3DSoundmaxDistance(), but 
		changing this value is usually not necessary. This value causes the sound
		to stop attenuating after it reaches the max distance. Most people think that this sets the
		volume of the sound to 0 after this distance, but this is not true. Only change the
		minimal distance (using for example setDefault3DSoundMinDistance()) to influence this.
		See ISound::setMaxDistance() for details about what the max distance is.
		It is also possible to influence this default value for every sound file 
		using ISoundSource::setDefaultMaxDistance().
		\return Default maximal distance for 3d sounds. The default value is 1000000000.0f. */
		virtual ik_f32 getDefault3DSoundMaxDistance() = 0;

		//! Sets a rolloff factor which influences the amount of attenuation that is applied to 3D sounds.
		/** The rolloff factor can range from 0.0 to 10.0, where 0 is no rolloff. 1.0 is the default 
		rolloff factor set, the value which we also experience in the real world. A value of 2 would mean
		twice the real-world rolloff. */
		virtual void setRolloffFactor(ik_f32 rolloff) = 0;

		//! Sets parameters affecting the doppler effect.
		/** \param dopplerFactor is a value between 0 and 10 which multiplies the doppler 
		effect. Default value is 1.0, which is the real world doppler effect, and 10.0f 
		would be ten times the real world doppler effect.
		\param distanceFactor is the number of meters in a vector unit. The default value
		is 1.0. Doppler effects are calculated in meters per second, with this parameter,
		this can be changed, all velocities and positions are influenced by this. If
		the measurement should be in foot instead of meters, set this value to 0.3048f
		for example.*/
		virtual void setDopplerEffectParameters(ik_f32 dopplerFactor=1.0f, ik_f32 distanceFactor=1.0f) = 0;

		//! Loads irrKlang plugins from a custom path.
		/** Plugins usually are .dll, .so or .dylib
		files named for example ikpMP3.dll (= short for irrKlangPluginMP3) which
		make it possible to play back mp3 files. Plugins are being 
		loaded from the current working directory at startup of the sound engine
		if the parameter ESEO_LOAD_PLUGINS is set (which it is by default), but
		using this method, it is possible to load plugins from a custom path in addition. 
		\param path Path to the plugin directory, like "C:\games\somegamegame\irrklangplugins".
		\return returns true if successful or false if not, for example because the path could 
		not be found. */
		virtual bool loadPlugins(const ik_c8* path) = 0;

		//! Returns a pointer to internal sound engine pointers, like the DirectSound interface.
		/** Use this with caution. This is only exposed to make it possible for other libraries
		such as Video playback packages to extend or use the sound driver irrklang uses. */
		virtual const SInternalAudioInterface& getInternalAudioInterface() = 0;		

		//! Sets the OutputMixedDataReceiver, so you can receive the pure mixed output audio data while it is being played.
		/** This can be used to store the sound output as .wav file or for creating a Oscillograph or similar.
		This works only with software based audio drivers, that is ESOD_WIN_MM, ESOD_ALSA, and ESOD_CORE_AUDIO. 
		Returns true if successful and false if the current audio driver doesn't support this feature. Set this to null
		again once you don't need it anymore. */
		virtual bool setMixedDataOutputReceiver(ISoundMixedOutputReceiver* receiver) = 0;
	};


	//! structure for returning pointers to the internal audio interface. 
	/** Use ISoundEngine::getInternalAudioInterface() to get this. */
	struct SInternalAudioInterface
	{
		//! IDirectSound interface, this is not null when using the ESOD_DIRECT_SOUND audio driver
		void* pIDirectSound;

		//! IDirectSound8 interface, this is not null when using the ESOD_DIRECT_SOUND8 audio driver
		void* pIDirectSound8;

		//! HWaveout interface, this is not null when using the ESOD_WIN_MM audio driver
		void* pWinMM_HWaveOut;

		//! ALSA PCM Handle interface, this is not null when using the ESOD_ALSA audio driver
		void* pALSA_SND_PCM;

		//! AudioDeviceID handle, this is not null when using the ESOD_CORE_AUDIO audio driver
		ik_u32 pCoreAudioDeviceID;
	};



} // end namespace irrklang


#endif
