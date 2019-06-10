#include <stddef.h>
#include <tiffio.h>

#include "load-textures.h"
#include "texture-count.h"

static void loadTexture(GLuint *textureIdentifierPointer, const char path[])
{
    glGenTextures(1, textureIdentifierPointer);
    glBindTexture(GL_TEXTURE_2D, *textureIdentifierPointer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    TIFF *const image = TIFFOpen(path, "r");
    int imageWidth = 0;
    int imageHeight = 0;
    TIFFGetField(image, TIFFTAG_IMAGEWIDTH, &imageWidth);
    TIFFGetField(image, TIFFTAG_IMAGELENGTH, &imageHeight);
    unsigned int *const raster = _TIFFmalloc(
        imageWidth * imageHeight * sizeof(unsigned int)
    );
    TIFFReadRGBAImage(image, imageWidth, imageHeight, raster, 0);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        imageWidth, 
        imageHeight, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        raster
    );
    _TIFFfree(raster);
    TIFFClose(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void loadTextures(Texture textures[], GLuint textureIdentifiers[])
{
    static const char *const pathsToTextures[textureCount] =
    {
        "./textures/forest.tif",
        "./textures/hills.tif",
        "./textures/pasture.tif",
        "./textures/field.tif",
        "./textures/mountain.tif",
        "./textures/desert.tif"
    };

    for (size_t index = 0; index < textureCount; index += 1)
    {
        textures[index].identifier = textureIdentifiers[index];
        textures[index].unitIndex = index;
        loadTexture(&textures[index].identifier, pathsToTextures[index]);
    }
}
