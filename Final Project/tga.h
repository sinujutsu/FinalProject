/*
  Copyright (C) 1999
  For non-commercial use only.

    File  : tga.h
  Date  : 05/05/1999
  Author  : Nate Miller
  Contact : vandals1@home.com
*/

// Header guard:

#ifndef TGA_INC_H
#define TGA_INC_H

#include <stdio.h>

class Tga {
public:
	// Error Codes
	static const int TGA_FILE_NOT_FOUND = 13; /* file was not found */
	static const int TGA_BAD_IMAGE_TYPE = 14; /* color mapped image or image is not uncompressed */
	static const int TGA_BAD_DIMENSION = 15;  /* dimension is not a power of 2 */
	static const int TGA_BAD_BITS = 16;		  /* image bits is not 8, 24 or 32 */
	static const int TGA_BAD_DATA = 17;		  /* image data could not be loaded */

	/** 
	 *
	 * @param name is the filename to load the texture from
	 *
	 * @param id is the gl texture to bind to
	 *
	 * @param build_mipmaps If build_mipmaps is 1, the loader uses gluBuildMipmaps to build
	 * a mipmap set for the texture.  This is a bit slower but generally
	 * allows files of any size to be loaded.
	 *
	 * @return 0 if all is well, otherwise returns an error code
	 */

    static int loadTGA (const char *name, int id, int build_mipmaps=0); 

private:

	static int checkSize (int x);
	static unsigned char *getRGBA (FILE *s, int size);
	static unsigned char *getRGB (FILE *s, int size);
	static unsigned char *getGray (FILE *s, int size);
	static unsigned char *getData (FILE *s, int sz, int iBits);
	static int returnError (FILE *s, int error);
};

#endif
