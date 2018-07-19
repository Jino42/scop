#include "scop.h"

typedef struct s_tga
{
    unsigned char imageTypeCode;
    short int imageWidth;
    short int imageHeight;
    unsigned char bitCount;
    unsigned char *imageData;
}				t_tga;

unsigned char *LoadTGAFile(t_texture *texture, const char *filename)
{
	t_tga *tgaFile = ft_memalloc(sizeof(t_tga));
    FILE *filePtr;
    unsigned char ucharBad;
    short int sintBad;
    long imageSize;
    int colorMode;
    unsigned char colorSwap;

    // Open the TGA file.
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
    {
        return (NULL);
    }

    // Read the two first bytes we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Which type of image gets stored in imageTypeCode.
    fread(&tgaFile->imageTypeCode, sizeof(unsigned char), 1, filePtr);

    // For our purposes, the type code should be 2 (uncompressed RGB image)
    // or 3 (uncompressed black-and-white images).
    if (tgaFile->imageTypeCode != 2 && tgaFile->imageTypeCode != 3)
    {
		ft_printf("Image type : %i\n", tgaFile->imageTypeCode );
        fclose(filePtr);
        return (NULL);
    }

    // Read 13 bytes of data we don't need.
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);
    fread(&sintBad, sizeof(short int), 1, filePtr);

    // Read the image's width and height.
    fread(&tgaFile->imageWidth, sizeof(short int), 1, filePtr);
    fread(&tgaFile->imageHeight, sizeof(short int), 1, filePtr);

    // Read the bit depth.
    fread(&tgaFile->bitCount, sizeof(unsigned char), 1, filePtr);

    // Read one byte of data we don't need.
    fread(&ucharBad, sizeof(unsigned char), 1, filePtr);

    // Color mode -> 3 = BGR, 4 = BGRA.
    colorMode = tgaFile->bitCount / 8;
    imageSize = tgaFile->imageWidth * tgaFile->imageHeight * colorMode;

    // Allocate memory for the image data.
	printf("%li\n", imageSize);
    if (!(tgaFile->imageData = (unsigned char*)ft_memalloc(sizeof(unsigned char)*imageSize)))
	{
		ft_printf("Rip\n");
		exit(0);
	}
    // Read the image data.
    fread(tgaFile->imageData, sizeof(unsigned char), imageSize, filePtr);

    // Change from BGR to RGB so OpenGL can read the image data.
    for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
    {
        colorSwap = tgaFile->imageData[imageIdx];
        tgaFile->imageData[imageIdx] = tgaFile->imageData[imageIdx + 2];
        tgaFile->imageData[imageIdx + 2] = colorSwap;
    }

    fclose(filePtr);
	texture->width = tgaFile->imageWidth;
	texture->height = tgaFile->imageHeight;
    return (tgaFile->imageData);
}

t_texture		*texture_construct(const char *path, const int type)
{
	t_texture		*texture;
	unsigned char	*data_texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (NULL);
	texture->name = strdup(path);
	texture->flag |= type;
	if (!(data_texture = LoadTGAFile(texture, path)))
		return (texture_destruct(&texture));
	texture->name = strdup(path);
	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
								texture->width,
								texture->height,
								0, GL_BGRA, GL_UNSIGNED_BYTE,
								data_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	ft_memdel((void *)&data_texture);
	return (texture);
}

void		*texture_destruct(t_texture **texture)
{
	if (texture && *texture)
	{
		ft_memdel((void **)(&(*texture)->name));
		ft_memdel((void **)texture);
	}
	return (NULL);
}
