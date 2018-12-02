#include <menu.h>
#include <algorithm>    // std::min

const Color Menu::FRAME_COLOR = {0, 0, 0};
const Color Menu::BACKGROUD_COLOR = {255, 255, 255};

Menu::Menu(int xpos, int ypos, TTF_Font *font, SDL_Renderer *renderer, Game *game) : background{xpos + FRAME_THIKCNESS,
                                                                                                ypos + FRAME_THIKCNESS,
                                                                                                WIDTH,
                                                                                                HEIGHT},
                                                                                     frame{xpos, ypos,
                                                                                           WIDTH + FRAME_THIKCNESS * 2,
                                                                                           HEIGHT
                                                                                               + FRAME_THIKCNESS * 2},
                                                                                     font(font),
                                                                                     renderer(renderer),
                                                                                     xpos(xpos),
                                                                                     ypos(ypos),
                                                                                     game(game) {

  arrow.loadFromFile(renderer, "../assets/images/arrow.png");

  if (font != nullptr) {
    //Render game_over
    SDL_Color textColor = {0, 0, 0};
    if (!title.loadFromRenderedText(renderer, font, "Pause", textColor)) {
      printf("Failed to render \"title\" texture!\n");
    }
    if (!options[0].loadFromRenderedText(renderer, font, "Resume", textColor)) {
      printf("Failed to render \"resume\" texture!\n");
    }
    if (!options[1].loadFromRenderedText(renderer, font, "Restart", textColor)) {
      printf("Failed to render \"exit\" texture!\n");
    }
    if (!options[2].loadFromRenderedText(renderer, font, "Exit", textColor)) {
      printf("Failed to render \"exit\" texture!\n");
    }
  }
}

void Menu::handle_keys(SDL_Keycode key) {
  switch (key) {
    case SDLK_DOWN: {
      selected_index = std::min(++selected_index, static_cast<int>(options.size() - 1));
      break;
    }
    case SDLK_UP: {
      selected_index = std::max(--selected_index, 0);
      break;
    }
    case SDLK_RETURN: {
      exec_option();
      break;
    }
    case SDLK_ESCAPE: {
      game->unpause();
      selected_index = 0;
      break;
    }
    default:break;
  }
}

void Menu::render() {
  draw_rect(renderer, &frame, FRAME_COLOR);
  draw_rect(renderer, &background, BACKGROUD_COLOR);

  arrow.render(renderer, xpos + 30, ypos + 55 + selected_index * 30);
  title.render(renderer, xpos + (WIDTH - title.get_width()) / 2, ypos + 20);

  int i = 0;
  for (auto &option: options) {
    option.render(renderer, xpos + (WIDTH - option.get_width()) / 2, ypos + i + 60);
    i += 30;
  }
}

void Menu::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, Color color) {
  SDL_SetRenderDrawColor(renderer, color.red(), color.green(), color.blue(), color.alpha());
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect border color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}

void Menu::exec_option() {
  switch (selected_index) {
    case 0: {
      game->unpause();
      break;
    }
    case 1: {
      game->restart();
      break;
    }
    case 2: {
      game->quit();
      break;
    }
  }
  selected_index = 0;
}
