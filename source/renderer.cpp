#include <stdlib.h>

internal void
clear_screen(SDL_Color color)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderClear(renderer);
}

internal void
render_texture(SDL_Texture* texture, int x, int y, int w, int h)
{
  SDL_Rect dst = { x, y, w, h };
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

internal void
draw_rect(SDL_Rect rect, SDL_Color color, bool shoud_fill = false)
{
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  if (shoud_fill) {
    SDL_RenderFillRect(renderer, &rect);
  } else {
    SDL_RenderDrawRect(renderer, &rect);
  }
}

internal void
draw_text(const char* text, TTF_Font* font, int x, int y, SDL_Color color)
{
  // char buf[1024];
  // wcstombs_s(buf, text, 1024);
  auto surface = TTF_RenderUTF8_Blended(font, text, color);
  if (!surface) {
    printf("TTF_RenderUTF8_Solid: %s\n", TTF_GetError());
    return;
  }

  auto texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!texture) {
    printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
    return;
  }

  // Render texture.
  {
    int w, h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    render_texture(texture, x, y, w, h);
  }

  // Clear resources.
  {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
  }
}