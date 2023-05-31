#include "texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GLuint load_texture(char* filename)
{
    SDL_Surface* surface;
    GLuint texture_name;

    surface = IMG_Load(filename);
    // The glGenTextures function generates texture names. Parameters: n The number of texture names to be generated.
    // textures: A pointer to the first element of an array in which the generated texture names are stored.
    glGenTextures(1, &texture_name);
    // The glBindTexture function enables the creation of a named texture that is bound to a texture target.
    // Parameters: target The target to which the texture is bound. Must have the value GL_TEXTURE_1D or GL_TEXTURE_2D.
    // texture The name of a texture; the texture name cannot currently be in use.
    glBindTexture(GL_TEXTURE_2D, texture_name);
    // The glTexImage2D function specifies a two-dimensional texture image.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)(surface->pixels));
    // Sets texture parameters.
    // Parameters: target The target texture, which must be either GL_TEXTURE_1D or GL_TEXTURE_2D.
    // pname The symbolic name of a single valued texture parameter. The following symbols are accepted in pname.
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture_name;
}
