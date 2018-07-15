#ifndef TETRIS_TEXTURE_H
#define TETRIS_TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class Texture
{
public:
  //Initializes variables
  Texture();

  //Deallocates memory
  ~Texture();

  //Loads image at specified path
  bool loadFromFile(SDL_Renderer *renderer, std::string path );

  //Creates image from font string
  bool loadFromRenderedText(SDL_Renderer *renderer, TTF_Font *font, std::string textureText, SDL_Color textColor );

  //Deallocates texture
  void free();

  //Set color modulation
  void setColor( Uint8 red, Uint8 green, Uint8 blue );

  //Set blending
  void setBlendMode( SDL_BlendMode blending );

  //Set alpha modulation
  void setAlpha( Uint8 alpha );

  //Renders texture at given point
  void render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

  //Gets image dimensions
  int getWidth();
  int getHeight();

private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  //Image dimensions
  int mWidth;
  int mHeight;
};

#endif //TETRIS_TEXTURE_H
