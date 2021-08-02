#include "boot.cpp"
#include "gui.cpp"

enum Game_Mode
{
  GM_BOOT,
  GM_DESKTOP,
  GM_GAMEPLAY,
  GM_MENU,
};

Game_Mode game_mode = GM_DESKTOP;

internal void
change_game_mode(Game_Mode new_game_mode);

internal void
update_game(f32 dt)
{
  if (!boot_state.is_initialized) {
    game_mode = GM_BOOT;
    update_boot(dt);
    return;
  }

  if (game_mode == GM_DESKTOP) {
    clear_screen(SDL_Color{ 0x73, 0x9A, 0xAE });

    SDL_Rect rect = { 0, 0, CLIENT_WIDTH, 15 };
    draw_rect(rect, SDL_Color{ 0xFF, 0xF8, 0xEF }, true);

    /*char buf[32];
    sprintf_s(buf, "fps = %.2f", 1.f / dt);
    draw_text(buf, desktop_font, CLIENT_WIDTH / 2, CLIENT_HEIGHT / 2, SDL_Color{
    0x0A, 0x0A, 0x0A });*/
  } else {
    clear_screen(SDL_Color{ 0x00, 0x00, 0x00 });
  }
}

internal void
change_game_mode(Game_Mode new_game_mode)
{
  game_mode = new_game_mode;
}