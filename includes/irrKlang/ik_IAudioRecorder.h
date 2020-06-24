// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_AUDIO_RECORDER_H_INCLUDED__
#define __I_IRRKLANG_AUDIO_RECORDER_H_INCLUDED__

#include "ik_IRefCounted.h"
#include "ik_ISoundSource.h"


namespace irrklang
{
	class ICapturedAudioDataReceiver;

	//! Interface to an audio recorder. Create it using the createIrrKlangAudioRecorder() function.
	/** It creates sound sources into an ISoundEngine which then can be played there. 
	See @ref recordingAudio for an example on how to use this. */
	class IAudioRecorder : public virtual IRefCounted
	{
	public:

		//! Starts recording audio. 
		/** Clears all possibly previously recorded buffered audio data and starts to record. 
		When finished recording audio data, call stopRecordingAudio(). 
		All recorded audio data gets stored into an internal audio buffer, which
		can then be accessed for example using addSoundSourceFromRecordedAudio() or
		getRecordedAudioData(). For recording audio data not into an internal audio
		buffer, use startRecordingCustomHandledAudio().
		\param sampleRate: Sample rate of the recorded audio.
		\param sampleFormat: Sample format of the recorded audio.
		\param channelCount: Amount of audio channels.
		\return Returns true if successfully started recording and false if not.*/
		virtual bool startRecordingBufferedAudio(ik_s32 sampleRate=22000, 
		                                         ESampleFormat sampleFormat=ESF_S16,
												 ik_s32 channelCount=1) = 0;

		//! Starts recording audio. 
		/** Clears all possibly previously recorded buffered audio data and starts to record 
		audio data, which is delivered to a custom user callback interface. 
		When finished recording audio data, call stopRecordingAudio(). If instead of 
		recording the data to the receiver interface recording into a managed buffer
		is wished, use startRecordingBufferedAudio() instead.
		\param receiver: Interface to be implemented by the user, gets called once for each
		captured audio data chunk. 
		\param sampleRate: Sample rate of the recorded audio.
		\param sampleFormat: Sample format of the recorded audio.
		\param channelCount: Amount of audio channels.
		\return Returns true if successfully started recording and false if not. */
		virtual bool startRecordingCustomHandledAudio(ICapturedAudioDataReceiver* receiver,
			                                          ik_s32 sampleRate=22000,
													  ESampleFormat sampleFormat=ESF_S16,
													  ik_s32 channelCount=1) = 0;

		//! Stops recording audio.
		virtual void stopRecordingAudio() = 0;

		//! Creates a sound source for the recorded audio data.
		/** The returned sound source pointer then can be used to play back the recorded audio data
		using ISoundEngine::play2D(). This method only will succeed if the audio was recorded using
		startRecordingBufferedAudio() and audio recording is currently stopped.
		\param soundName Name of the virtual sound file (e.g. "someRecordedAudio"). You can also use this
		name when calling play3D() or play2D().  */
		virtual ISoundSource* addSoundSourceFromRecordedAudio(const char* soundName) = 0;

		//! Clears recorded audio data buffer, freeing memory.
		/** This method will only succeed if audio recording is currently stopped. */
		virtual void clearRecordedAudioDataBuffer() = 0;

		//! Returns if the recorder is currently recording audio.
		virtual bool isRecording() = 0;

		//! Returns the audio format of the recorded audio data. 
		/** Also contains informations about the length of the recorded audio stream. */
		virtual SAudioStreamFormat getAudioFormat() = 0;

		//! Returns a pointer to the recorded audio data.
		/** This method will only succeed if audio recording is currently stopped and
		something was recorded previously using startRecordingBufferedAudio(). 
		The lenght of the buffer can be retrieved using 
		getAudioFormat().getSampleDataSize(). Note that the pointer is only valid
		as long as not clearRecordedAudioDataBuffer() is called or another sample is
		recorded.*/
		virtual void* getRecordedAudioData() = 0;

		//! returns the name of the sound driver, like 'ALSA' for the alsa device.
		/** Possible returned strings are "NULL", "ALSA", "CoreAudio", "winMM", 
		"DirectSound" and "DirectSound8". */
		virtual const char* getDriverName() = 0;
	};


	//! Interface to be implemented by the user if access to the recorded audio data is needed.
	/** Is used as parameter in IAudioRecorder::startRecordingCustomHandledAudio. */
	class ICapturedAudioDataReceiver : public IRefCounted
	{
	public:

		//! Gets called once for each captured audio data chunk.
		/** See IAudioRecorder::startRecordingCustomHandledAudio for details.
		\param audioData: Pointer to a part of the recorded audio data
		\param lengthInBytes: Amount of bytes in the audioData buffer.*/
		virtual void OnReceiveAudioDataStreamChunk(unsigned char* audioData, unsigned long lengthInBytes) = 0;
	};


} // end namespace irrklang


#endif
