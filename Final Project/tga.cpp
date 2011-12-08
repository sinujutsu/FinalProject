/*
    Copyright (C) 1999
    For non-commercial use only.

    File	: tga.c
    Date	: 05/05/1999
    Author	: Nate Miller
    Contact	: vandals1@home.com
*/

#include "tga.h"
#include "cs315.h"

#include <stdlib.h>
#include <string.h>
//#include <GL/glut.h>

GLenum texFormat;

/*
=============
checkSize

Make sure this number a power of 2.
=============
*/
int Tga::checkSize (int x)
{
    if (x == 2	 || x == 4    || 
        x == 8	 || x == 16   || 
        x == 32  || x == 64   ||
        x == 128 || x == 256  || 
        x == 512 || x == 1024 ||
        x == 2048)
        return 1;
    else return 0;
}


/*
=============
getRGBA

Reads in RGBA data for a 32bit image. 
=============
*/
unsigned char *Tga::getRGBA (FILE *s, int size)
{
    unsigned char *rgba;
    unsigned char temp;
    int bread;
    int i;

    rgba = (unsigned char *) malloc (size * 4); 

    if (rgba == NULL)
        return 0;

    bread = fread (rgba, sizeof (unsigned char), size * 4, s); 

    /* TGA is stored in BGRA, make it RGBA */
    if (bread != size * 4)
    {
        free (rgba);
        return 0;
    }

    for (i = 0; i < size * 4; i += 4 )
    {
        temp = rgba[i];
        rgba[i] = rgba[i + 2];
        rgba[i + 2] = temp;
    }

    texFormat = GL_RGBA;
    return rgba;
}


/*
=============
getRGB

Reads in RGB data for a 24bit image. 
=============
*/
unsigned char *Tga::getRGB (FILE *s, int size)
{
    unsigned char *rgb;
    unsigned char temp;
    int bread;
    int i;

    rgb = (unsigned char *) malloc (size * 3); 

    if (rgb == NULL)
        return 0;
    
    bread = fread (rgb, sizeof (unsigned char), size * 3, s);

    if (bread != size * 3)
    {
        free (rgb);
        return 0;
    }

    /* TGA is stored in BGR, make it RGB */
    for (i = 0; i < size * 3; i += 3)
    {
        temp = rgb[i];
        rgb[i] = rgb[i + 2];
        rgb[i + 2] = temp;
    }

    texFormat = GL_RGB;

    return rgb;
}


/*
=============
getGray

Gets the grayscale image data.
=============
*/
unsigned char *Tga::getGray (FILE *s, int size)
{
    unsigned char *grayData;
    int bread;

    grayData = (unsigned char *) malloc (size);

    if (grayData == NULL)
        return 0;

    bread = fread (grayData, sizeof (unsigned char), size, s);

    if (bread != size)
    {
        free (grayData);
        return 0;
    }

    texFormat = GL_LUMINANCE;

    return grayData;
}


/*
=============
getData

Gets the image data for the specified bit depth.
=============
*/
unsigned char *Tga::getData (FILE *s, int sz, int iBits)
{
    if (iBits == 32)
        return getRGBA (s, sz);
    else if (iBits == 24)
        return getRGB (s, sz);	
    else if (iBits == 8)
        return getGray (s, sz);
    return NULL;    
}


/*
=============
returnError
=============
Called when there is an error loading the .tga file.
*/
int Tga::returnError (FILE *s, int error)
{
    fclose (s);
    return error;
}


/*
=============
loadTGA

Loads up a targa file.  Supported types are 8,24 and 32 uncompressed images.  
id is the texture ID to bind to.
=============
*/
int Tga::loadTGA (const char *name, int id, int build_mipmaps)
{
    unsigned char type[4];
    unsigned char info[7];
    unsigned char *imageData = NULL;
    int imageWidth, imageHeight;
    int imageBits, size;
    FILE *s;

    if (!(s = fopen (name, "rb"))){
    	printf("file not found\n");
        return TGA_FILE_NOT_FOUND;
    }    
 
    int bread;

    bread = fread (&type, sizeof (char), 3, s); // read in colormap info and image type, byte 0 ignored
    fseek (s, 12, SEEK_SET);			// seek past the header and useless info
    bread = fread (&info, sizeof (char), 6, s);

    if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
        return returnError (s, TGA_BAD_IMAGE_TYPE);

    imageWidth = info[0] + info[1] * 256; 
    imageHeight = info[2] + info[3] * 256;
    imageBits =	info[4]; 

    size = imageWidth * imageHeight; 

    if (build_mipmaps == 0) {
      /* make sure dimension is a power of 2 */
      if (!checkSize (imageWidth) || !checkSize (imageHeight))
          return returnError (s, TGA_BAD_DIMENSION);
    }  
  
    /* make sure we are loading a supported type */
    if (imageBits != 32 && imageBits != 24 && imageBits != 8)
        return returnError (s, TGA_BAD_BITS);

    imageData = getData (s, size, imageBits);

    /* no image data */
    if (imageData == NULL)
        return returnError (s, TGA_BAD_DATA);

    fclose (s);

    // Set up some default texture parameters
    glBindTexture (GL_TEXTURE_2D, id);
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if (build_mipmaps == 0) {
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    
    }
    else {
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    if (build_mipmaps == 0) {   
      glTexImage2D (GL_TEXTURE_2D, 0, texFormat, imageWidth,
        imageHeight, 0, texFormat, GL_UNSIGNED_BYTE, imageData);
    }
  
    else {    
      int components = 3;
      if (texFormat == GL_RGBA) components = 4;
      else if (texFormat == GL_ALPHA || texFormat == GL_LUMINANCE) components = 1;
      gluBuild2DMipmaps(GL_TEXTURE_2D, components, imageWidth, imageHeight, texFormat, GL_UNSIGNED_BYTE, imageData);
    }

    /* release data, its been uploaded */
    free (imageData);

    return 0;
}

