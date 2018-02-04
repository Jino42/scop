/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 22:16:06 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/02/04 17:20:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    tgaFile->imageData = (unsigned char*)malloc(sizeof(unsigned char)*imageSize);

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

static bool	size_of_bmp_texture(t_texture *texture, const int fd, uint32_t *size_texture)
{
	read(fd, &texture->width, sizeof(uint32_t));
	read(fd, &texture->height, sizeof(uint32_t));
	*size_texture = texture->width * texture->height * 4;
	if (texture->width > 4996 || texture->height > 4996)
		return (false);
	return (true);
}

unsigned char	*import_texture(t_texture *texture, const char *path)
{
	unsigned char	*data_texture;
	int				fd;
	uint32_t		size_texture;

	if (!(fd = open(path, O_RDONLY)))
		return (NULL);
	if (!size_of_bmp_texture(texture, fd, &size_texture) ||
		!(data_texture = ft_memalloc(size_texture)))
	{
		close(fd);
		return (NULL);
	}
	if ((read(fd, data_texture, size_texture)) != size_texture)
	{
		ft_memdel((void *)&data_texture);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (data_texture);
}

void			*textures_destroy(t_m_textures **textures)
{
	if (!textures || !*textures)
		return (NULL);
	ft_memdel((void *)textures);
	return (NULL);
}

void			*texture_destroy(t_texture **texture)
{
	if (!texture || !*texture)
		return (NULL);
	ft_memdel((void*)texture);
	return (NULL);
}
t_texture			*texture_construct(const char *texture_path)
{
	t_texture			*texture;
	unsigned char	*data_texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
		return (NULL);
	//if (!(data_texture = import_texture(texture, texture_path)))
	if (!(data_texture = LoadTGAFile(texture, texture_path)))
		return (texture_destroy(&texture));
	texture->path = strdup(texture_path);
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

int32_t	texture_already_exist(t_m_textures *textures,
							const char *texture_path)
{
	uint32_t i;

	i = 0;
	while (i < textures->size)
	{
		if (!strcmp(texture_path, textures->texture[i]->path))
			return (i);
		i++;
	}
	return (-1);
}

GLuint	texture_add(t_m_textures *textures,
				const char *texture_path)
{
	int32_t index;
	if (!(textures->texture = realloc(textures->texture, sizeof(t_texture **) * (textures->size + 1))))
		return (0);
	if ((index = texture_already_exist(textures, texture_path)) != -1)
		return (textures->texture[index]->id);
	if (!(textures->texture[textures->size] = texture_construct(texture_path)))
		return (0);
	textures->size++;
	return (textures->texture[textures->size - 1]->id);
}

/*
	void	texture_set(const t_texture *textures,
						const t_mesh *mesh,
						const t_shader *shader,
						const char *name_uniform)
	{
		glUniform1i(glGetUniformLocation(shader->program, name_uniform), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->tex->id);
	}
*/

t_m_textures		*textures_construct()
{
	t_m_textures		*textures;

	if (!(textures = ft_memalloc(sizeof(t_m_textures))))
		return (textures_destroy(&textures));
	textures->add = &texture_add;
	return (textures);
}
