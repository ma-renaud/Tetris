
#include <menu.h>

const Color Menu::FRAME_COLOR = {0, 0, 0};
const Color Menu::BACKGROUD_COLOR = {255, 255, 255};

Menu::Menu(int xpos, int ypos) : background{xpos + FRAME_THIKCNESS, ypos + FRAME_THIKCNESS, WIDTH, HEIGHT},
                                 frame{xpos, ypos, WIDTH + FRAME_THIKCNESS * 2, HEIGHT + FRAME_THIKCNESS * 2} {
  options[0] = "Resume";
  options[1] = "Exit";
}

void Menu::handle_events() {

}

void Menu::handle_keys(SDL_Keycode key) {

}

void Menu::update() {

}

void Menu::render(SDL_Renderer *renderer) {
  draw_rect(renderer, &frame, FRAME_COLOR);
  draw_rect(renderer, &background, BACKGROUD_COLOR);
}

void Menu::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color) {
  SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(), color.alpha());
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect border color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}
