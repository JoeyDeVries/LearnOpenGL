// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_EFFECT_CONTROL_H_INCLUDED__
#define __I_IRRKLANG_SOUND_EFFECT_CONTROL_H_INCLUDED__

#include "ik_IVirtualRefCounted.h"
#include "ik_vec3d.h"


namespace irrklang
{
	//! Interface to control the active sound effects (echo, reverb,...) of an ISound object, a playing sound.
	/** Sound effects such as chorus, distorsions, echo, reverb and similar can
	be controlled using this. An instance of this interface can be obtained via
	ISound::getSoundEffectControl(). The sound containing this interface has to be started via 
	ISoundEngine::play2D() or ISoundEngine::play3D() with the flag enableSoundEffects=true, 
	otherwise no acccess to this interface will be available.
	For the DirectSound driver, these are effects available since DirectSound8. For most 
	effects, sounds should have a sample rate of 44 khz and should be at least
	150 milli seconds long for optimal quality when using the DirectSound driver.
	Note that the interface pointer is only valid as long as
	the ISound pointer is valid. If the ISound pointer gets dropped (IVirtualRefCounted::drop()),
	the ISoundEffects may not be used any more. */
	class ISoundEffectControl
	{
	public:

		//! Disables all active sound effects
		virtual void disableAllEffects() = 0;

		//! Enables the chorus sound effect or adjusts its values.
		/** Chorus is a voice-doubling effect created by echoing the
		original sound with a slight delay and slightly modulating the delay of the echo. 
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fWetDryMix Ratio of wet (processed) signal to dry (unprocessed) signal. Minimal Value:0, Maximal Value:100.0f;
		\param fDepth Percentage by which the delay time is modulated by the low-frequency oscillator, in hundredths of a percentage point. Minimal Value:0, Maximal Value:100.0f;
		\param fFeedback Percentage of output signal to feed back into the effect's input. Minimal Value:-99, Maximal Value:99.0f;
		\param fFrequency Frequency of the LFO. Minimal Value:0, Maximal Value:10.0f;
		\param sinusWaveForm True for sinus wave form, false for triangle.
		\param fDelay Number of milliseconds the input is delayed before it is played back. Minimal Value:0, Maximal Value:20.0f;
		\param lPhase Phase differential between left and right LFOs. Possible values:
			-180, -90, 0, 90, 180
		\return Returns true if successful. */
		virtual bool enableChorusSoundEffect(ik_f32 fWetDryMix = 50,
											ik_f32 fDepth = 10,
											ik_f32 fFeedback = 25,
											ik_f32 fFrequency = 1.1,
											bool sinusWaveForm = true,
											ik_f32 fDelay = 16,
											ik_s32 lPhase = 90) = 0;

		//! removes the sound effect from the sound
		virtual void disableChorusSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isChorusSoundEffectEnabled() = 0;

		//! Enables the Compressor sound effect or adjusts its values.
		/** Compressor is a reduction in the fluctuation of a signal above a certain amplitude. 
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fGain Output gain of signal after Compressor. Minimal Value:-60, Maximal Value:60.0f;
		\param fAttack Time before Compressor reaches its full value. Minimal Value:0.01, Maximal Value:500.0f;
		\param fRelease Speed at which Compressor is stopped after input drops below fThreshold. Minimal Value:50, Maximal Value:3000.0f;
		\param fThreshold Point at which Compressor begins, in decibels. Minimal Value:-60, Maximal Value:0.0f;
		\param fRatio Compressor ratio. Minimal Value:1, Maximal Value:100.0f;
		\param fPredelay Time after lThreshold is reached before attack phase is started, in milliseconds. Minimal Value:0, Maximal Value:4.0f;
		\return Returns true if successful. */
		virtual bool enableCompressorSoundEffect( ik_f32 fGain = 0,
												ik_f32 fAttack = 10,
												ik_f32 fRelease = 200,
												ik_f32 fThreshold = -20,
												ik_f32 fRatio = 3,
												ik_f32 fPredelay = 4) = 0;

		//! removes the sound effect from the sound
		virtual void disableCompressorSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isCompressorSoundEffectEnabled() = 0;

		//! Enables the Distortion sound effect or adjusts its values.
		/** Distortion is achieved by adding harmonics to the signal in such a way that,
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		as the level increases, the top of the waveform becomes squared off or clipped.
		\param fGain Amount of signal change after distortion. Minimal Value:-60, Maximal Value:0;
		\param fEdge Percentage of distortion intensity. Minimal Value:0, Maximal Value:100;
		\param fPostEQCenterFrequency Center frequency of harmonic content addition. Minimal Value:100, Maximal Value:8000;
		\param fPostEQBandwidth Width of frequency band that determines range of harmonic content addition. Minimal Value:100, Maximal Value:8000;
		\param fPreLowpassCutoff Filter cutoff for high-frequency harmonics attenuation. Minimal Value:100, Maximal Value:8000;
		\return Returns true if successful. */
		virtual bool enableDistortionSoundEffect(ik_f32 fGain = -18,
												ik_f32 fEdge = 15,
												ik_f32 fPostEQCenterFrequency = 2400,
												ik_f32 fPostEQBandwidth = 2400,
												ik_f32 fPreLowpassCutoff = 8000) = 0;

		//! removes the sound effect from the sound
		virtual void disableDistortionSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isDistortionSoundEffectEnabled() = 0;

		//! Enables the Echo sound effect or adjusts its values.
		/** An echo effect causes an entire sound to be repeated after a fixed delay.
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fWetDryMix Ratio of wet (processed) signal to dry (unprocessed) signal. Minimal Value:0, Maximal Value:100.0f;
		\param fFeedback Percentage of output fed back into input. Minimal Value:0, Maximal Value:100.0f;
		\param fLeftDelay Delay for left channel, in milliseconds. Minimal Value:1, Maximal Value:2000.0f;
		\param fRightDelay Delay for right channel, in milliseconds. Minimal Value:1, Maximal Value:2000.0f;
		\param lPanDelay Value that specifies whether to swap left and right delays with each successive echo. Minimal Value:0, Maximal Value:1;
		\return Returns true if successful. */
		virtual bool enableEchoSoundEffect(ik_f32 fWetDryMix = 50,
											ik_f32 fFeedback = 50,
											ik_f32 fLeftDelay = 500,
											ik_f32 fRightDelay = 500,
											ik_s32 lPanDelay = 0) = 0;

		//! removes the sound effect from the sound
		virtual void disableEchoSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isEchoSoundEffectEnabled() = 0;

		//! Enables the Flanger sound effect or adjusts its values.
		/** Flange is an echo effect in which the delay between the original 
		signal and its echo is very short and varies over time. The result is 
		sometimes referred to as a sweeping sound. The term flange originated
		with the practice of grabbing the flanges of a tape reel to change the speed. 
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fWetDryMix Ratio of wet (processed) signal to dry (unprocessed) signal. Minimal Value:0, Maximal Value:100.0f;
		\param fDepth Percentage by which the delay time is modulated by the low-frequency oscillator, in hundredths of a percentage point. Minimal Value:0, Maximal Value:100.0f;
		\param fFeedback Percentage of output signal to feed back into the effect's input. Minimal Value:-99, Maximal Value:99.0f;
		\param fFrequency Frequency of the LFO. Minimal Value:0, Maximal Value:10.0f;
		\param triangleWaveForm True for triangle wave form, false for square.
		\param fDelay Number of milliseconds the input is delayed before it is played back. Minimal Value:0, Maximal Value:20.0f;
		\param lPhase Phase differential between left and right LFOs. Possible values:
			-180, -90, 0, 90, 180
		\return Returns true if successful. */
		virtual bool enableFlangerSoundEffect(ik_f32 fWetDryMix = 50,
											ik_f32 fDepth = 100,
											ik_f32 fFeedback = -50,
											ik_f32 fFrequency = 0.25f,
											bool triangleWaveForm = true,
											ik_f32 fDelay = 2,
											ik_s32 lPhase = 0) = 0;

		//! removes the sound effect from the sound
		virtual void disableFlangerSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isFlangerSoundEffectEnabled() = 0;

		//! Enables the Gargle sound effect or adjusts its values.
		/** The gargle effect modulates the amplitude of the signal. 
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param rateHz Rate of modulation, in Hertz. Minimal Value:1, Maximal Value:1000
		\param sinusWaveForm True for sinus wave form, false for triangle.
		\return Returns true if successful. */
		virtual bool enableGargleSoundEffect(ik_s32 rateHz = 20, bool sinusWaveForm = true) = 0;

		//! removes the sound effect from the sound
		virtual void disableGargleSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isGargleSoundEffectEnabled() = 0;

		//! Enables the Interactive 3D Level 2 reverb sound effect or adjusts its values.
		/** An implementation of the listener properties in the I3DL2 specification. Source properties are not supported.
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param lRoom Attenuation of the room effect, in millibels (mB). Interval: [-10000, 0] Default: -1000 mB
		\param lRoomHF Attenuation of the room high-frequency effect. Interval: [-10000, 0]      default: 0 mB
		\param flRoomRolloffFactor Rolloff factor for the reflected signals. Interval: [0.0, 10.0]      default: 0.0
		\param flDecayTime Decay time, in seconds. Interval: [0.1, 20.0]      default: 1.49s
		\param flDecayHFRatio Ratio of the decay time at high frequencies to the decay time at low frequencies. Interval: [0.1, 2.0]       default: 0.83
		\param lReflections Attenuation of early reflections relative to lRoom. Interval: [-10000, 1000]   default: -2602 mB
		\param flReflectionsDelay Delay time of the first reflection relative to the direct path in seconds. Interval: [0.0, 0.3]       default: 0.007 s
		\param lReverb Attenuation of late reverberation relative to lRoom, in mB. Interval: [-10000, 2000]   default: 200 mB
		\param flReverbDelay Time limit between the early reflections and the late reverberation relative to the time of the first reflection. Interval: [0.0, 0.1]       default: 0.011 s
		\param flDiffusion Echo density in the late reverberation decay in percent. Interval: [0.0, 100.0]     default: 100.0 %
		\param flDensity Modal density in the late reverberation decay, in percent. Interval: [0.0, 100.0]     default: 100.0 %
		\param flHFReference Reference high frequency, in hertz. Interval: [20.0, 20000.0]  default: 5000.0 Hz 
		\return Returns true if successful. */
		virtual bool enableI3DL2ReverbSoundEffect(ik_s32 lRoom = -1000,
												ik_s32 lRoomHF = -100,
												ik_f32 flRoomRolloffFactor = 0,
												ik_f32 flDecayTime = 1.49f,
												ik_f32 flDecayHFRatio = 0.83f,
												ik_s32 lReflections = -2602,
												ik_f32 flReflectionsDelay = 0.007f,
												ik_s32 lReverb = 200,
												ik_f32 flReverbDelay = 0.011f,
												ik_f32 flDiffusion = 100.0f,
												ik_f32 flDensity = 100.0f,
												ik_f32 flHFReference = 5000.0f ) = 0;

		//! removes the sound effect from the sound
		virtual void disableI3DL2ReverbSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isI3DL2ReverbSoundEffectEnabled() = 0;

		//! Enables the ParamEq sound effect or adjusts its values.
		/** Parametric equalizer amplifies or attenuates signals of a given frequency. 
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fCenter Center frequency, in hertz, The default value is 8000. Minimal Value:80, Maximal Value:16000.0f
		\param fBandwidth Bandwidth, in semitones, The default value is 12. Minimal Value:1.0f, Maximal Value:36.0f
		\param fGain Gain, default value is 0. Minimal Value:-15.0f, Maximal Value:15.0f
		\return Returns true if successful. */
		virtual bool enableParamEqSoundEffect(ik_f32 fCenter = 8000,
											ik_f32 fBandwidth = 12,
											ik_f32 fGain = 0) = 0;

		//! removes the sound effect from the sound
		virtual void disableParamEqSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isParamEqSoundEffectEnabled() = 0;

		//! Enables the Waves Reverb sound effect or adjusts its values.
		/** \param fInGain Input gain of signal, in decibels (dB). Min/Max: [-96.0,0.0] Default: 0.0 dB.
		If this sound effect is already enabled, calling this only modifies the parameters of the active effect.
		\param fReverbMix Reverb mix, in dB. Min/Max: [-96.0,0.0] Default: 0.0 dB
		\param fReverbTime Reverb time, in milliseconds. Min/Max: [0.001,3000.0] Default: 1000.0 ms
		\param fHighFreqRTRatio High-frequency reverb time ratio. Min/Max: [0.001,0.999] Default: 0.001 
		\return Returns true if successful. */
		virtual bool enableWavesReverbSoundEffect(ik_f32 fInGain = 0,
											ik_f32 fReverbMix = 0,
											ik_f32 fReverbTime = 1000,
											ik_f32 fHighFreqRTRatio = 0.001f) = 0;

		//! removes the sound effect from the sound
		virtual void disableWavesReverbSoundEffect() = 0;

		//! returns if the sound effect is active on the sound
		virtual bool isWavesReverbSoundEffectEnabled() = 0;
	};

} // end namespace irrklang


#endif
