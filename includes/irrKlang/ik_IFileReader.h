// Copyright (C) 2002-2018 Nikolaus Gebhardt
// This file is part of the "irrKlang" library.
// For conditions of distribution and use, see copyright notice in irrKlang.h

#ifndef __I_IRRKLANG_READ_FILE_H_INCLUDED__
#define __I_IRRKLANG_READ_FILE_H_INCLUDED__

#include "ik_IRefCounted.h"

namespace irrklang
{

	//! Interface providing read access to a file.
	class IFileReader : public virtual IRefCounted
	{
	public:

		virtual ~IFileReader() {};

		//! Reads an amount of bytes from the file.
		//! \param buffer: Pointer to buffer where to read bytes will be written to.
		//! \param sizeToRead: Amount of bytes to read from the file.
		//! \return Returns how much bytes were read.
		virtual ik_s32 read(void* buffer, ik_u32 sizeToRead) = 0;

		//! Changes position in file, returns true if successful.
		//! \param finalPos: Destination position in the file.
		//! \param relativeMovement: If set to true, the position in the file is
		//! changed relative to current position. Otherwise the position is changed 
		//! from beginning of file.
		//! \return Returns true if successful, otherwise false.
		virtual bool seek(ik_s32 finalPos, bool relativeMovement = false) = 0;

		//! Returns size of file.
		//! \return Returns the size of the file in bytes.
		virtual ik_s32 getSize() = 0;

		//! Returns the current position in the file.
		//! \return Returns the current position in the file in bytes.
		virtual ik_s32 getPos() = 0;

		//! Returns name of file.
		//! \return Returns the file name as zero terminated character string.
		virtual const ik_c8* getFileName() = 0;
	};

} // end namespace irrklang

#endif

