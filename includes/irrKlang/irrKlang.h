/* irrKlang.h -- interface of the 'irrKlang' library

  Copyright (C) 2002-2018 Nikolaus Gebhardt

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.
*/

#ifndef __IRR_KLANG_H_INCLUDED__
#define __IRR_KLANG_H_INCLUDED__

#include "ik_irrKlangTypes.h"
#include "ik_vec3d.h"

#include "ik_IRefCounted.h"
#include "ik_IVirtualRefCounted.h"

#include "ik_ESoundOutputDrivers.h"
#include "ik_ESoundEngineOptions.h"
#include "ik_EStreamModes.h"
#include "ik_SAudioStreamFormat.h"
#include "ik_ISoundEngine.h"
#include "ik_ISoundSource.h"
#include "ik_ISound.h"
#include "ik_IAudioStream.h"
#include "ik_IAudioStreamLoader.h"
#include "ik_ISoundEffectControl.h"
#include "ik_ISoundStopEventReceiver.h"
#include "ik_IFileFactory.h"
#include "ik_IFileReader.h"
#include "ik_ISoundDeviceList.h"
#include "ik_IAudioRecorder.h"
#include "ik_ISoundMixedOutputReceiver.h"

//! irrKlang Version
#define IRR_KLANG_VERSION "1.6.0"

/*! \mainpage irrKlang 1.6.0 API documentation
 *
 * <div align="center"><img src="logobig.png" ></div>

 * \section contents Contents
 * General:<br/>
 * @ref intro <br/>
 * @ref features <br/>
 * @ref links <br/>
 * @ref tipsandtricks <br/>
 * <br/>
 * Programming irrKlang:<br/>
 * @ref concept <br/>
 * @ref playingSounds <br/>
 * @ref changingSounds <br/>
 * @ref soundSources <br/>
 * @ref sound3d <br/>
 * @ref removingSounds <br/>
 * @ref events <br/>
 * @ref memoryPlayback <br/>
 * @ref effects <br/>
 * @ref fileOverriding <br/>
 * @ref audioDecoders <br/>
 * @ref plugins <br/>
 * @ref staticLib <br/>
 * @ref enumeratingDevices <br/>
 * @ref recordingAudio <br/>
 * @ref unicode <br/>
 * <br/>
 * Short full examples:<br/>
 * @ref quickstartexample <br/>
 * @ref quickstartexample2 <br/>
 * <br/>
 * <br/>
 *
 * \section intro Introduction
 *
 * Welcome to the irrKlang API documentation. This page should give you a short overview 
 * over irrKlang, the high level audio library. 
 * In this documentation files you'll find any information you'll need to develop applications with
 * irrKlang using C++. If you are looking for a tutorial on how to start, you'll
 * find some on the homepage of irrKlang at
 * <A HREF="http://www.ambiera.com/irrklang" >http://www.ambiera.com/irrklang</A>
 * or inside the SDK in the directory \examples.
 *
 * The irrKlang library is intended to be an easy-to-use 3d and 2d sound engine, so
 * this documentation is an important part of it. If you have any questions or
 * suggestions, please take a look into the ambiera.com forum or just send a mail.
 *
 * <br/>
 * <br/>
 *
 *
 * \section features Features of irrKlang
 *
 * irrKlang is a high level 2D and 3D 
 * cross platform sound engine and audio library.
 * It has a very simply object orientated interface and was designed to be used
 * in games, scientific simulations, architectural visualizations and similar.
 * irrKlang plays several file formats such as
 * <ul>
 *               <li>RIFF WAVE (*.wav)</li>
 *               <li>Ogg Vorbis (*.ogg)</li>
 *               <li>MPEG-1 Audio Layer 3 (*.mp3)</li>
 *               <li>Free Lossless Audio Codec (*.flac)</li>
 *               <li>Amiga Modules (*.mod)</li>
 *               <li>Impulse Tracker (*.it)</li>
 *               <li>Scream Tracker 3 (*.s3d)</li>
 *               <li>Fast Tracker 2 (*.xm)</li>        
 * </ul>
 * It is also able to run on different operating systems and use several output drivers:
 *<ul>
 *       <li>Windows 98, ME, NT 4, 2000, XP, Vista, Windows 7, Windows 8</li>
 *	<ul>
 *       <li>DirectSound</li>
 *       <li>DirectSound8</li>
 *       <li>WinMM</li>
 *	</ul>
 *       <li>Linux / *nix</li>	
 *	<ul>
 *       <li>ALSA</li>
 *	</ul>
 *  <li>Mac OS X (x86 and PPC)</li>
 *	<ul>
 *       <li>CoreAudio</li>
 *	</ul>
 * </ul>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section links Links into the API documentation
 *
 * irrklang::ISoundEngine: The main class of irrKlang.<br/>
 * <A HREF="annotated.html">Class list</A>: List of all classes with descriptions.<BR/>
 * <A HREF="functions.html">Class members</A>: Good place to find forgotten features.<BR/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
  * \section tipsandtricks Tips and Tricks
 *
 * This section lists a few tips you might consider when implementing the sound part of your application
 * using irrKlang:
 *
 * <ul>
 *               <li>If you can choose which audio file format is the primary one for your application,
 *					 use .OGG files, instead of for example .MP3 files. irrKlang uses a lot less memory
 *                   and CPU power when playing .OGGs.</li>
 *               <li>To keep your application simple, each time you play a sound, you can use for example
 *                   play2D("filename.mp3") and let irrKlang handle the rest. There is no need to implement
 *                   a preloading/caching/file management system for the audio playback. irrKlang will handle
 *                   all this by itself and will never load a file twice. </li>
 *               <li>irrKlang is crashing in your application? This should not happen, irrKlang is pretty stable,
 *                   and in most cases, this is a problem in your code: In a lot of cases the reason is simply
 *                   a wrong call to irrklang::IRefCounted::drop(). Be sure you are doing it correctly. (If you are unsure,
 *                   temporarily remove all calls to irrklang::IRefCounted::drop() and see if this helps.)</li>
 * </ul>
 *
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section concept Starting up the Engine
 *
 * irrKlang is designed so that it is very easy to achieve everything, its interface should
 * be very simple to use. The @ref quickstartexample shows how to play and mp3 file, and there
 * is another example, @ref quickstartexample2, showing some few more details.<br/>
 * To start up the sound engine, you simply need to call createIrrKlangDevice(). To shut it down,
 * call IRefCounted::drop():
 *
 * \code
 * #include <irrKlang.h>
 *
 * // ...
 *
 * // start up the engine
 * irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
 *	
 * // ...
 * 
 * // after finished,
 * // close the engine again, similar as calling 'delete'
 * engine->drop(); 
 * \endcode
 *
 * The createIrrKlangDevice() function also accepts several parameters, so that you can 
 * specify which sound driver should be used, if plugins should be used, if irrKlang
 * should run in multithreaded mode, and similar.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section playingSounds Playing Sounds
 *
 * Once you have irrKlang running (like in @ref concept), you can start playing sounds:
 *
 * \code
 * engine->play2D("someSoundFile.wav"); 
 * \endcode
 *
 * This works with all supported file types. You can replace "someSoundFile.wav" with
 * "someSoundFile.mp3", or "someSoundFile.ogg", for example.<br/>
 * To play a sound looped, set the second parameter to 'true':
 *
 * \code
 * engine->play2D("myMusic.mp3", true); 
 * \endcode 
 *
 * To stop this looping sound again, use engine->\link irrklang::ISoundEngine::stopAllSounds stopAllSounds()\endlink to stop all sounds, or
 * irrklang::ISound::stop() if you only want to stop that single sound. @ref changingSounds
 * shows how to get to that ISound interface.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 * \section changingSounds Influencing Sounds during Playback
 * To influence parameters of the sound such as pan, volume or playback speed during runtime, 
 * to get the play position or stop playback of single playing sounds,
 * you can use the irrklang::ISound interface. 
 * irrklang::ISoundEngine::play2D (but also play3D) returns
 * a pointer to this interface when its third ('startPaused') or fourth ('track') parameter
 * was set to true:
 *
 * \code
 * irrklang::ISound* snd = engine->play2D("myMusic.mp3", true, false, true); 
 *
 * // ...
 *
 * if (snd)
 *     snd->setVolume(someNewValue);
 * 
 * // ...
 * 
 * if (snd)
 * {
 *     snd->drop(); // don't forget to release the pointer once it is no longer needed by you
 *     snd = 0;
 * }
 * \endcode
 *
 * The irrklang::ISound interface can also be used to test if the sound has been finished, 
 * set event receivers, pause and unpause sounds and similar. 
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 * \section soundSources Using Sound Sources
 *
 * To be more flexible playing back sounds, irrKlang uses the concept of sound sources. 
 * A sound source can be simply the name of a sound file, such as "sound.wav". It is possible
 * to add "sound.wav" as sound source to irrKlang, and play it using the sound source pointer:
 *
 * \code
 * irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("shoot.wav"); 
 *
 * engine->play2D(shootSound);
 *
 * // note: you don't need to drop() the shootSound if you don't use it anymore
 * \endcode
 *
 * The advantage of using irrklang::ISoundSource is that it is possible to set 
 * default values for this source, such
 * as volume or distances if it should be used as 3D sound:
 *
 * \code
 * irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("shoot.wav"); 
 *
 * shootSound->setDefaultVolume(0.5f);
 *
 * // shootSound will now be played with half its sound volume by default:
 * engine->play2D(shootSound);
 * \endcode
 *
 * It is also possible to have multiple settings for the same sound file:
 *
 * \code
 * irrklang::ISoundSource* shootSound = engine->addSoundSourceFromFile("shoot.wav"); 
 * irrklang::ISoundSource* shootSound2 = engine->addSoundSourceAlias(shootSound, "silentShoot"); 
 *
 * shootSound2->setDefaultVolume(0.1f);
 *
 * // shootSound will now be played with 100% of its sound volume by default,
 * // shootSound2 will now be played 10% of its sound volume by default. It is 
 * //  also possible to play it using engine->play("silentShoot"), now.
 * \endcode
 *
 * Using addSoundSourceFromMemory(), it is also possible to play sounds back directly from memory,
 * without files.
 * Of course, it is not necessary to use sound sources. Using irrklang::ISound, it is
 * possible to change the settings of all sounds, too. But using sound sources, it is
 * not necessary to do this every time a sound is played.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section sound3d 3D Sound
 *
 * There is nothing difficult in playing sounds in 3D using irrKlang: Instead of using 
 * irrklang::ISoundEngine::play2D(), just use irrklang::ISoundEngine::play3D(), which
 * takes a 3D position as additional parameter:
 *
 * \code
 * irrklang::vec3df position(23,70,90);
 * engine->play3D("yourSound.wav", position);
 * \endcode
 *
 * But to make it sound realistic, you need to set a minimal sound
 * distance: If your sound is caused by a bee, it will usually have a smaller
 * sound radius than for example a jet engine. You can set default values using sound sources
 * (see @ref soundSources) or set these values after you have started the sound paused:
 *
 * \code
 * irrklang::vec3df position(23,70,90);
 *
 * // start the sound paused:
 * irrklang::ISound* snd = engine->play3D("yourSound.wav", position, false, true);
 *
 * if (snd)
 * {
 *    snd->setMinDistance(30.0f); // a loud sound
 *    snd->setIsPaused(false); // unpause the sound
 * }
 * \endcode
 * 
 * There is also the possibility to change the maxDistance, but it is only necessary to change this
 * in very rare circumstances.
 * If the sound moves, it is also a good idea to update its position from time to time:
 * 
 * \code
 * if (snd)
 *    snd->setPosition(newPosition);
 * \endcode
 *
 * And don't forget to drop() the sound after you don't need it anymore. If you do, it's 
 * nothing severe because irrKlang will still clean up the sounds resources after it has
 * finished, but you still would waste some few bytes of memory:
 * 
 * \code
 * if (snd)
 * {
 *    snd->drop();
 *    snd = 0;
 * }
 * \endcode
 *
 * To update the position of yourself, the listener of the 3D sounds, use this from
 * time to time:
 *
 * \code
 * irrklang::vec3df position(0,0,0);        // position of the listener
 * irrklang::vec3df lookDirection(10,0,10); // the direction the listener looks into
 * irrklang::vec3df velPerSecond(0,0,0);    // only relevant for doppler effects
 * irrklang::vec3df upVector(0,1,0);        // where 'up' is in your 3D scene
 *
 * engine->setListenerPosition(position, lookDirection, velPerSecond, upVector);
 * \endcode
 *
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 * \section removingSounds Removing Sounds
 *
 * irrKlang manages the memory usage of sounds by itself, so usually, you don't have
 * to care about memory management. But if you know you need to reduce the
 * amount of used memory at a certain point in your program, you can do this:
 *
 * \code
 * engine->removeAllSoundSources(); 
 * \endcode
 *
 * This will remove all sounds and also cause all sounds to be stopped. To remove single
 * sounds from the engine, use:
 *
 * \code
 * engine->removeSoundSource(pointerToSomeSoundSource); 
 * // or:
 * engine->removeSoundSource("nameOfASoundFile.wav"); 
 * \endcode
 *
 * Note: Only removing buffered sounds will reduce the amount of memory used by irrKlang, streamed
 * sounds don't occupy a lot of memory when they are not played.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section events Using Sound Events
 *
 * In order to wait for a sound to be finished, it is simply possible to 
 * poll irrklang::ISound::isFinished(). Another way would be to constantly use 
 * irrklang::ISoundEngine::isCurrentlyPlaying to test wether a sound with that name or source
 * is currently playing. But of course, an event based approach is a lot nicer. That's why irrKlang
 * supports sound events.<br/>
 * The key to sound events is the method 
 * \link irrklang::ISound::setSoundStopEventReceiver setSoundStopEventReceiver \endlink
 * of the irrklang::ISound interface
 * (See @ref changingSounds on how to get the ISound interface):
 *
 * \code
 * irrklang::ISound* snd = engine->play2D("speech.mp3", false, false, true); 
 * if (snd)
 *    snd->setSoundStopEventReceiver(yourEventReceiver, 0);
 * \endcode
 * 
 * The optional second parameter of setSoundStopEventReceiver is a user pointer, set it to whatever you like.
 * 'yourEventReceiver' must be an implementation of the irrklang::ISoundStopEventReceiver interface.<br/>
 * A whole implementation could look like this:
 *
 * \code
 * class MySoundEndReceiver : public irrklang::ISoundStopEventReceiver
 * {
 *   public:
 *     virtual void OnSoundStopped (irrklang::ISound* sound, irrklang::E_STOP_EVENT_CAUSE reason, void* userData)
 *     {
 *        // called when the sound has ended playing
 *        printf("sound has ended");
 *     }
 * }
 *
 * // ...
 *
 * MySoundEndReceiver* myReceiver = new MySoundEndReceiver();
 * irrklang::ISound* snd = engine->play2D("speech.mp3", false, false, true); 
 * if (snd)
 *    snd->setSoundStopEventReceiver(myReceiver);
 *
 * myReceiver->drop(); // similar to delete
 * \endcode
 * 
 * The irrklang::ISoundStopEventReceiver::OnSoundStopped() method is guaranteed to be called when a sound or sound stream has stopped,
 * either because the sound reached its playback end, its sound source was removed,
 * ISoundEngine::stopAllSounds() has been called or the whole engine was deleted.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section memoryPlayback Memory Playback
 *
 * Using irrKlang, it is easily possible to play sounds directly from memory instead out of 
 * files. There is an example project showing this: In the SDK, in /examples/03.MemoryPlayback.
 * But in short, it simply works by adding the memory as sound source (See @ref soundSources for 
 * details about sound sources):
 *
 * \code
 * engine->addSoundSourceFromMemory(pointerToMemory, memorySize, "nameforthesound.wav");
 * 
 * // play sound now
 * engine->play2D("nameforthesound.wav");
 * \endcode
 *
 * Or using a sound source pointer:
 *
 * \code
 * irrklang::ISoundSource* snd = 
 *   engine->addSoundSourceFromMemory(pointerToMemory, memorySize, "nameforthesound.wav");
 * 
 * // play sound now
 * engine->play2D(snd);
 * \endcode
 *
 * Note: It is also possible to overwrite the file access directly, don't use this Memory Playback
 * feature for this. See @ref fileOverriding for details.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section effects Sound Effects
 *
 * irrKlang supports the effects Chorus, Compressor, Distortion, Echo, Flanger
 * Gargle, 3DL2Reverb, ParamEq and WavesReverb, when using the sound driver 
 * irrklang::ESOD_DIRECT_SOUND_8, which selected by default when using Windows.<br/>
 *
 * Using the irrklang::ISound interface, you can obtain the irrklang::ISoundEffectControl
 * interface if the sound device supports sound effects and the last parameter ('enableSoundEffects')
 * was set to true when calling play2D():
 *
 * \code
 * irrklang::ISound* snd = engine->play2D("sound.wav", true, false, true, ESM_AUTO_DETECT, true);
 *
 * if (snd)
 * {
 *    irrklang::ISoundEffectControl* fx = snd->getSoundEffectControl();
 *    if (fx)
 *    {
 *        // enable the echo sound effect for this sound
 *        fx->enableEchoSoundEffect();
 *    }
 * }
 * 
 * snd->drop();
 * \endcode
 *
 * This enabled the echo sound effect for this sound. The method also supports a lot of 
 * parameters, and can be called multiple times to change those parameters over time if wished.
 * There are a lot of other sound effects, see irrklang::ISoundEffectControl for details.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section fileOverriding Overriding File Access
 *
 * It is possible to let irrKlang use your own file access functions.
 * This is useful if you want to read sounds from other sources than
 * just files, for example from custom internet streams or 
 * an own encrypted archive format. There is an example in the SDK in 
 * examples/04.OverrideFileAccess which shows this as well.<br/>
 *
 * The only thing to do for this is to implement your own  irrklang::IFileFactory,
 * and set it in irrKlang using irrklang::ISoundEngine::addFileFactory():
 *
 * \code
 * // a class implementing the IFileFactory interface to override irrklang file access
 * class CMyFileFactory : public irrklang::IFileFactory
 * {
 *   public:
 *
 *   // Opens a file for read access. Simply return 0 if file not found.
 *   virtual irrklang::IFileReader* createFileReader(const ik_c8* filename)
 *   {
 *     // return your own irrklang::IFileReader implementation here, for example like that:
 *     return new CMyReadFile(filename);
 *   }
 * };
 * 
 * // ...
 *
 * CMyFileFactory* myFactory = new CMyFileFactory();
 * engine->addFileFactory(myFactory);
 * myFactory->drop();
 * \endcode
 *
 * For a full example implementation, just take a look into the SDK in examples/04.OverrideFileAccess.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section audioDecoders Adding Audio Decoders
 *
 * To add support for new file formats, it is possible to add new audio decoders
 * to irrKlang. 
 * The only thing to do for this is to implement your own  irrklang::IAudioStreamLoader,
 * and irrklang::IAudioStream, and set it in irrKlang using 
 * irrklang::ISoundEngine::registerAudioStreamLoader():
 *
 * \code
 * class NewAudioStreamLoader : public irrklang::IAudioStreamLoader
 * {
 *   // ... returns NewAudioDecoder and the used file name suffices.
 * };
 *
 * class NewAudioDecoder : public irrklang::IAudioStream
 * {
 *   public:
 *     // ... decodes the new file format
 * };
 *
 * // ...
 *
 * NewAudioDecoder* loader = new NewAudioDecoder();
 * engine->registerAudioStreamLoader(loader);
 * loader->drop();
 * \endcode
 * 
 * There is an example audio decoder and loader with full source in plugins/ikpMP3, which
 * adds MP3 audio decoding capabilities to irrKlang.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section plugins Creating irrKlang Plugins
 *
 * irrKlang plugins are ikp*.dll (Windows), ikp*.so (Unix) or ikp*.dylib (MacOS) 
 * files which are loaded by irrKlang at startup when the 
 * irrklang::ESEO_LOAD_PLUGINS was set (which is default) or
 * irrklang::ISoundEngine::loadPlugins() was called. <br/>
 *
 * The plugin only needs to contain the following function which will be called by irrKlang:
 *
 * \code
 * #ifdef WIN32
 * // Windows version
 * __declspec(dllexport) void __stdcall irrKlangPluginInit(ISoundEngine* engine, const char* version)
 * #else
 * // Linux and Mac OS version
 * void irrKlangPluginInit(ISoundEngine* engine, const char* version)
 * #endif
 * {
 *   // your implementation here
 * }
 * \endcode
 *
 * In there, it is for example possible to extend irrKlang with new audio decoders,
 * see @ref audioDecoders for details. <br/>
 * 
 * There is an example plugin with full source in plugins/ikpMP3, which
 * adds MP3 audio decoding capabilities to irrKlang.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section staticLib Using irrKlang as static Lib
 *
 * If you don't want to use the irrKlang.DLL file and link irrKlang statically, you can do this
 * by simply linking to the irrKlang.lib in the bin/win32-visualstudio_lib folder. This folder
 * will only available in the pro versions of irrKlang, which you get when purchasing an irrKlang
 * license.
 *
 * To use irrKlang in this way, just define IRRKLANG_STATIC before including irrklang.h, like this:
 *
 * \code
 * #define IRRKLANG_STATIC
 * #include <irrKlang.h>
 * \endcode
 *
 * Of course, IRRKLANG_STATIC can also simply be defined in the project/compiler settings instead of
 * in the source file.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section enumeratingDevices Enumerating sound devices
 *
 * irrKlang uses the default sound device when playing sound when started without parameters. But if you want
 * irrKlang to playback sound on one specific sound device, you may want to enumerate the available
 * sound devices on your system and select one of them. Use irrklang::createSoundDeviceList() for this. 
 * This example code shows how to print a list of all available sound devices on the current system and lets
 * the user choose one of them: 
 *
 * \code
 * int main(int argc, const char** argv)
 * {
 *	// enumerate devices
 * 
 * 	irrklang::ISoundDeviceList* deviceList = createSoundDeviceList();
 * 
 * 	// ask user for a sound device
 * 
 * 	printf("Devices available:\n\n");
 * 
 * 	for (int i=0; i<deviceList->getDeviceCount(); ++i)
 * 		printf("%d: %s\n", i, deviceList->getDeviceDescription(i));
 * 
 * 	printf("\nselect a device using the number (or press any key to use default):\n\n");
 * 	int deviceNumber = getch() - '0';
 * 
 * 	// create device with the selected driver
 * 
 * 	const char* deviceID = deviceList->getDeviceID(deviceNumber);
 * 		
 * 	ISoundEngine* engine = createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, 
 * 	                                            irrklang::ESEO_DEFAULT_OPTIONS,
 * 	                                            deviceID);
 * 
 * 	deviceList->drop(); // delete device list
 *
 *  // ... use engine now
 * } 
 * \endcode
 *
 * In this way, it is also possible to play back sound using two devices at the same time: Simply 
 * create two irrKlang devices with each a different deviceID.<br/>
 * Note: createSoundDeviceList() takes a driver type parameter (such as irrklang::ESOD_DIRECT_SOUND8), which you
 * have to set to the same value as the first parameter you want to use with createIrrKlangDevice(), if it is 
 * other than irrklang::ESOD_AUTO_DETECT.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section recordingAudio Recording Audio
 *
 * irrKlang is able to record audio from sound capturing devices such as microphones (currently only 
 * supported in windows). Use the irrklang::IAudioRecorder interface to do this. The following example shows how
 * to record some audio and play it back again using the engine: 
 *
 * \code
 * int main(int argc, const char** argv)
 * {
 *	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
 *	irrklang::IAudioRecorder* recorder = irrklang::createIrrKlangAudioRecorder(engine);
 *
 *	if (!engine || !recorder)
 *	{
 *		printf("Could not create audio engine or audio recorder\n");
 *		return 1;
 *	}
 *
 *	printf("\nPress any key to start recording audio...\n");
 *	getch();
 *
 *	// record some audio
 *
 *	recorder->startRecordingBufferedAudio();
 *
 *	printf("\nRECORDING. Press any key to stop...\n");
 *	getch();
 *
 *	recorder->stopRecordingAudio();
 *
 *	printf("\nRecording done, recorded %dms of audio.\n", 
 *		recorder->getAudioFormat().FrameCount * 1000 / recorder->getAudioFormat().SampleRate );
 *	printf("Press any key to play back recorded audio...\n");
 *	getch();
 *
 *	// play the recorded audio
 *	recorder->addSoundSourceFromRecordedAudio("myRecordedVoice");
 *	engine->play2D("myRecordedVoice", true);
 *
 *	// wait until user presses a key
 *	printf("\nPress any key to quit...");
 *	getch();
 *
 *	recorder->drop();
 *	engine->drop(); // delete engine
 *
 *	return 0;
 * } 
 * \endcode
 *
 * In order to select a specific audio capturing device for recording, it is necessary to enumerate
 * the available devices. Simply replace the first to lines of code of the example above with code
 * like this to list all devices and select one:
 *
 * \code
 *  // enumerate recording devices and ask user to select one
 * 
 *  irrklang::ISoundDeviceList* deviceList = irrklang::createAudioRecorderDeviceList();
 *
 *  printf("Devices available:\n\n");
 *
 *  for (int i=0; i<deviceList->getDeviceCount(); ++i)
 *           printf("%d: %s\n", i, deviceList->getDeviceDescription(i));
 *
 *  printf("\nselect a device using the number (or press any key to use default):\n\n");
 *  int deviceNumber = getch() - '0';
 *
 *  // create recording device with the selected driver
 *
 *  const char* deviceID = deviceList->getDeviceID(deviceNumber);
 *  irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
 *  irrklang::IAudioRecorder* recorder = 
 *     irrklang::createIrrKlangAudioRecorder(engine, irrklang::ESOD_AUTO_DETECT, deviceID);
 *
 * \endcode
 *
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 * \section unicode Unicode support
 *
 * irrKlang supports unicode on all operating systems. Internally, it uses UTF8, and all functions accepting strings
 * and file names take UTF8 strings. If you are running irrKlang on Windows, and are using the UNICODE define or using
 * wchar_t* strings directly, you can do this as well. Use the irrKlang provided function makeUTF8fromUTF16string() to 
 * convert your wchar_t* string to a char* string.
 *
 * This example shows how:
 *
 * \code
 * const wchar_t* yourFilename = L"SomeUnicodeFilename.wav"; // assuming this is the file name you get from some of your functions
 *
 * const int nBufferSize = 2048; // large enough, but best would be wcslen(yourFilename)*3.
 * char strBuffer[nBufferSize]; 
 * irrklang::makeUTF8fromUTF16string(yourFilename, strBuffer, nBufferSize);
 *
 * // now the converted file name is in strBuffer. We can play it for example now:
 * engine->play2D(strBuffer);
 * \endcode
 *
 * Of course, you can use any other unicode conversion function for this. makeUTF8fromUTF16string() is only provided
 * for convenience.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 *
 *
 * \section quickstartexample Quick Start Example
 *
 * To simply start the engine and play a mp3 file, use code like this:
 *
 * \code
 * #include <iostream>
 * #include <irrKlang.h>
 * #pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
 *
 * int main(int argc, const char** argv)
 * {
 *	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
 *	if (!engine) return 1; // could not start engine
 *
 *	engine->play2D("someMusic.mp3", true); // play some mp3 file, looped
 * 
 *	std::cin.get(); // wait until user presses a key
 * 
 *	engine->drop(); // delete engine
 *	return 0;
 * } 
 * \endcode
 *
 * A mp3 file is being played until the user presses enter in this example. 
 * As you can see, irrKlang uses <A HREF="namespaces.html">namespaces</A>, all of
 * the classes are located in the namespace irrklang. If you don't want to write 
 * this in front of every class and function you are using, simply write 
 *
 * \code
 * using namespace irrklang;
 * \endcode
 * in front of your code, as also shown in the next example.
 * <br/>
 * <br/>
 * <br/>
 * <br/>
 *
 *
 *
 * \section quickstartexample2 Quick Start Example 2
 *
 * The following is a simple interactive application, starting up the sound engine and 
 * playing some streaming .ogg music file and a .wav sound effect every time the user
 * presses a key.
 *
 * \code
 * #include <iostream>
 * #include <irrKlang.h>
 * using namespace irrklang;
 *
 * #pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
 *
 *
 * int main(int argc, const char** argv)
 * {
 * 	// start the sound engine with default parameters
 * 	ISoundEngine* engine = createIrrKlangDevice();
 *
 * 	if (!engine)
 * 		return 0; // error starting up the engine
 *
 * 	// play some sound stream, looped
 * 	engine->play2D("../../media/helltroopers.ogg", true);
 *
 * 	std::cout << "\nHello World!\n";
 *
 * 	char i = 0;
 *
 * 	while(i != 'q')
 * 	{
 * 		std::cout << "Press any key to play some sound, press 'q' to quit.\n";
 *
 * 		// play a single sound
 * 		engine->play2D("../../media/bell.wav");
 *
 * 		std::cin >> i; // wait for user to press some key
 * 	}
 *
 * 	engine->drop(); // delete engine
 * 	return 0;
 * }
 *
 * \endcode
 */

#if defined(IRRKLANG_STATIC)
    #define IRRKLANG_API
#else
    #if (defined(WIN32) || defined(WIN64) || defined(_MSC_VER))
        #ifdef IRRKLANG_EXPORTS
        #define IRRKLANG_API __declspec(dllexport)
        #else
        #define IRRKLANG_API __declspec(dllimport)
        #endif // IRRKLANG_EXPORT
    #else
        #define IRRKLANG_API __attribute__((visibility("default")))
    #endif // defined(WIN32) || defined(WIN64)
#endif // IRRKLANG_STATIC

#if defined(_STDCALL_SUPPORTED)
#define IRRKLANGCALLCONV __stdcall  // Declare the calling convention.
#else
#define IRRKLANGCALLCONV
#endif // STDCALL_SUPPORTED

//! Everything in the irrKlang Sound Engine can be found in this namespace.
namespace irrklang
{
	//! Creates an irrKlang device. The irrKlang device is the root object for using the sound engine.
	/** \param driver The sound output driver to be used for sound output. Use irrklang::ESOD_AUTO_DETECT
	to let irrKlang decide which driver will be best.
	\param options A combination of irrklang::E_SOUND_ENGINE_OPTIONS literals. Default value is 
	irrklang::ESEO_DEFAULT_OPTIONS.
	\param deviceID Some additional optional deviceID for the audio driver. If not needed, simple
	set this to 0. 
	This can be used for example to set a specific ALSA output pcm device for output
	("default" or "hw", for example). For most driver types, available deviceIDs can be 
	enumerated using createSoundDeviceList().
	See @ref enumeratingDevices for an example or ISoundDeviceList or details.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns pointer to the created irrKlang device or null if the
	device could not be created. If you don't need the device, use ISoundEngine::drop() to
	delete it. See IRefCounted::drop() for details.
	*/
	IRRKLANG_API ISoundEngine* IRRKLANGCALLCONV createIrrKlangDevice(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		int options = ESEO_DEFAULT_OPTIONS,
		const char* deviceID = 0,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Creates a list of available sound devices for the driver type. 
	/** The device IDs in this list can be used as parameter to createIrrKlangDevice() to
	make irrKlang use a special sound device. See @ref enumeratingDevices for an example on how
	to use this.
	\param driver The sound output driver of which the list is generated. Set it irrklang::ESOD_AUTO_DETECT
	to let this function use the same device as createIrrKlangDevice() would choose.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns a pointer to the list of enumerated sound devices for the selected sound driver.
	The device IDs in this list can be used as parameter to createIrrKlangDevice() to
	make irrKlang use a special sound device. 
	After you don't need the list anymore, call ISoundDeviceList::drop() in order to free its memory. */
	IRRKLANG_API ISoundDeviceList* IRRKLANGCALLCONV createSoundDeviceList(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Creates an irrKlang audio recording device. The IAudioRecorder is the root object for recording audio.
	/** If you want to play back recorded audio as well, create the ISoundEngine first using
	createIrrKlangDevice() and then the IAudioRecorder using createIrrKlangAudioRecorder(), where
	you set the ISoundEngine as first parameter. See @ref recordingAudio for an example on how to use this.
	Note: audio recording is a very new feature a still beta in irrKlang. It currently only works in Windows
	and with DirectSound (subject to change).
	\param irrKlangDeviceForPlayback A pointer to the already existing sound device used for playback
	of audio. Sound sources recorded with the IAudioRecorder will be added into that device so that
	they can be played back there.
	\param driver The sound output driver to be used for recording audio. Use irrklang::ESOD_AUTO_DETECT
	to let irrKlang decide which driver will be best.
	\param deviceID Some additional optional deviceID for the audio driver. If not needed, simple
	set this to 0. Use createAudioRecorderDeviceList() to get a list of all deviceIDs.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns pointer to the created irrKlang device or null if the
	device could not be created. If you don't need the device, use ISoundEngine::drop() to
	delete it. See IRefCounted::drop() for details.
	*/
	IRRKLANG_API IAudioRecorder* IRRKLANGCALLCONV createIrrKlangAudioRecorder(
		ISoundEngine* irrKlangDeviceForPlayback,
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* deviceID = 0,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);

	//! Creates a list of available recording devices for the driver type. 
	/** The device IDs in this list can be used as parameter to createIrrKlangAudioRecorder() to
	make irrKlang use a special recording device. 
	\param driver The sound output driver of which the list is generated. Set it irrklang::ESOD_AUTO_DETECT
	to let this function use the same device as createIrrKlangDevice() would choose.
	\param sdk_version_do_not_use Don't use or change this parameter. Always set it to
	IRRKLANG_SDK_VERSION, which is done by default. This is needed for sdk version checks.
	\return Returns a pointer to the list of enumerated recording devices for the selected sound driver.
	The device IDs in this list can be used as parameter to createIrrKlangAudioRecorder() to
	make irrKlang use a special sound device. 
	After you don't need the list anymore, call ISoundDeviceList::drop() in order to free its memory. */
	IRRKLANG_API ISoundDeviceList* IRRKLANGCALLCONV createAudioRecorderDeviceList(
		E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
		const char* sdk_version_do_not_use = IRR_KLANG_VERSION);


	//! Converts a wchar_t string to an utf8 string, useful when using Windows in unicode mode. 
	/** irrKlang works with unicode file names, and accepts char* strings as parameters for names and filenames.
	If you are running irrKlang in Windows, and working with wchar_t* pointers instead of char* ones, 
	you can use this function to create a char* (UTF8) representation of your wchar_t* (UTF16) string.
	Works for filenames and other strings.
	\param pInputString zero terminated input string.
	\param pOutputBuffer the buffer where the converted string is written to. Be sure that this buffer
	has a big enough size. A good size would be three times the string length of your input buffer, like
	wcslen(yourInputBuffer)*3. Because each wchar_t can be represented by up to 3 chars.
	\param outputBufferSize size of your output buffer.
	\return Returns true if successful, and false if not. If 'false' is returned, maybe your buffer was too small. */
	IRRKLANG_API bool IRRKLANGCALLCONV makeUTF8fromUTF16string(
		const wchar_t* pInputString, char* pOutputBuffer, int outputBufferSize);


} // end namespace irrklang


/*! \file irrKlang.h
    \brief Main header file of the irrKlang sound library, the only file needed to include.
*/

#endif

