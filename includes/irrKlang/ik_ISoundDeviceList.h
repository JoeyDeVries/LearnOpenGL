// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_SOUND_DEVICE_LIST_H_INCLUDED__
#define __I_IRRKLANG_SOUND_DEVICE_LIST_H_INCLUDED__

#include "ik_IRefCounted.h"

namespace irrklang
{

//!	A list of sound devices for a sound driver. Use irrklang::createSoundDeviceList() to create this list.
/** The function createIrrKlangDevice() has a parameter 'deviceID' which takes the value returned by
ISoundDeviceList::getDeviceID() and uses that device then. 
The list of devices in ISoundDeviceList usually also includes the default device which is the first
entry and has an empty deviceID string ("") and the description "default device". 
There is some example code on how to use the ISoundDeviceList in @ref enumeratingDevices.*/
class ISoundDeviceList : public IRefCounted
{
public:

	//! Returns amount of enumerated devices in the list.
	virtual ik_s32 getDeviceCount() = 0;

	//! Returns the ID of the device. Use this string to identify this device in createIrrKlangDevice().
	/** \param index Index of the device, a value between 0 and ISoundDeviceList::getDeviceCount()-1. 
	\return Returns a pointer to a string identifying the device. The string will only as long valid 
	as long as the ISoundDeviceList exists. */
	virtual const char* getDeviceID(ik_s32 index) = 0;

	//! Returns description of the device.
	/** \param index Index of the device, a value between 0 and ISoundDeviceList::getDeviceCount()-1. */
	virtual const char* getDeviceDescription(ik_s32 index) = 0;
};


} // end namespace irrklang

#endif

