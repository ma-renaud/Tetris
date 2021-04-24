
#include <tetris_drawer_rect.h>

constexpr SDL_Color TetrisDrawerRect::textColor;

static constexpr int OPTION_HEIGHT = 30;
static constexpr int MENU_VERTICAL_PADDING = 60;
static constexpr int ARROW_VERTICAL_OFFSET = -5;

TetrisDrawerRect::TetrisDrawerRect(SDL_engine *engine) : engine(engine) {

  renderer = engine->get_renderer();
  font = engine->get_font();

  if (font != nullptr) {
    //Render text
    if (!score_header.loadFromRenderedText(renderer, font, "Score", textColor))
      printf("Failed to render \"score header\" texture!\n");
    if (!level_header.loadFromRenderedText(renderer, font, "Level", textColor))
      printf("Failed to render \"level header\" texture!\n");
    if (!menu_title.loadFromRenderedText(renderer, font, "Pause", textColor))
      printf("Failed to render \"pause_menu title\" texture!\n");
    if (!game_over.loadFromRenderedText(renderer, font, "Game Over!", textColor))
      printf("Failed to render \"game over\" texture!\n");
  }

  menu_arrow.loadFromFile(renderer, "../../assets/images/arrow.png");
}

void TetrisDrawerRect::clear() {
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);
}

void TetrisDrawerRect::render() {
  SDL_RenderPresent(renderer);
}

void TetrisDrawerRect::draw(Tetromino *tetromino) {
  draw(tetromino, tetromino->xpos(), tetromino->ypos());
}

void TetrisDrawerRect::draw(Well *well) {
  SDL_Rect rect = {0, 0, unit_size, unit_size};

  for (int i = TOP_OFFSET; i < Well::HEIGHT; i++) {
    for (int j = 0; j < Well::WIDTH; j++) {
      if (well->get_tile(i, j) > 0) {
        rect.x = (j) * unit_size;
        rect.y = (i - TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect, get_tetromino_color(well->get_tile(i, j)));
      }
    }
  }
}

void TetrisDrawerRect::draw(ScoreLvl *score) {
  static const int WIDTH = 7;
  static const int HEIGHT = 6;
  static const int XPOS = Well::WIDTH * unit_size;
  static const int SCORE_HEADER_XPOS = XPOS + ((WIDTH - 1) * unit_size - score_header.get_width()) / 2;
  static const int SCORE_HEADER_YPOS = unit_size + 5;
  static const int LEVEL_HEADER_XPOS = XPOS + ((WIDTH - 1) * unit_size - level_header.get_width()) / 2;
  static const int LEVEL_HEADER_YPOS = 3 * unit_size + 5;

  static int last_score = -1;
  if (last_score != score->get_score()) {
    last_score = score->get_score();
    this->score.loadFromRenderedText(renderer, font, std::to_string(last_score), textColor);
  }

  static int last_level = -1;
  if (last_level != score->get_level()) {
    last_level = score->get_level();
    level.loadFromRenderedText(renderer, font, std::to_string(last_level), textColor);
  }

  draw_right_zone(XPOS, 0, WIDTH, HEIGHT);

  score_header.render(renderer, SCORE_HEADER_XPOS, SCORE_HEADER_YPOS);
  level_header.render(renderer, LEVEL_HEADER_XPOS, LEVEL_HEADER_YPOS);
  this->score.render(renderer,
                     XPOS + ((WIDTH - 1) * unit_size - this->score.get_width()) / 2,
                     SCORE_HEADER_YPOS + unit_size);
  level.render(renderer, XPOS + ((WIDTH - 1) * unit_size - level.get_width()) / 2, LEVEL_HEADER_YPOS + unit_size);
}

void TetrisDrawerRect::draw(Bag *bag) {
  static const int XPOS = Well::WIDTH * unit_size;
  static const int YPOS = 5 * unit_size;
  draw_right_zone(XPOS, YPOS, 7, 8);
  draw(bag->preview().get(), Well::WIDTH + 1, 9);
}

void TetrisDrawerRect::draw(Menu *menu) {
  auto *menu_pause = dynamic_cast<MenuPause *> (menu);
  if (menu_pause)
    draw(menu_pause);

  auto *menu_options = dynamic_cast<MenuOptions *> (menu);
  if (menu_options)
    draw(menu_options);

  auto *title_screen = dynamic_cast<TitleScreen *> (menu);
  if (title_screen)
    draw(title_screen);
}

void TetrisDrawerRect::draw(MenuPause *menu) {
  static const int WIDTH = menu->get_width();
  static const int HEIGHT = menu->get_height();
  static const int FRAME_THIKCNESS = 5;
  static const SDL_Color FRAME_COLOR = {0, 0, 0, 255};
  static const SDL_Color BACKGROUD_COLOR = {255, 255, 255, 255};
  static SDL_Rect frame{0, 0, WIDTH + FRAME_THIKCNESS * 2, HEIGHT + FRAME_THIKCNESS * 2};
  static SDL_Rect background{0, 0, WIDTH, HEIGHT};
  static std::vector<Texture> menu_options;
  static int largest_option = 0;

  if (menu_options.empty())
    largest_option = generate_menu_texture(menu_options, menu);

  frame.x = menu->get_xpos();
  frame.y = menu->get_ypos();
  background.x = frame.x + FRAME_THIKCNESS;
  background.y = frame.y + FRAME_THIKCNESS;

  draw_rect(renderer, &frame, FRAME_COLOR);
  draw_rect(renderer, &background, BACKGROUD_COLOR);

  menu_arrow.render(renderer,
                    frame.x + (WIDTH - largest_option) / 2 - menu_arrow.get_width() - 5,
                    frame.y + MENU_VERTICAL_PADDING + ARROW_VERTICAL_OFFSET + menu->get_selected_option_index() * OPTION_HEIGHT);
  menu_title.render(renderer, frame.x + (WIDTH - menu_title.get_width()) / 2, frame.y + 20);

  int i = 0;
  for (auto &option: menu_options) {
    option.render(renderer, frame.x + (WIDTH - option.get_width()) / 2, frame.y + i + MENU_VERTICAL_PADDING);
    i += OPTION_HEIGHT;
  }
}

void TetrisDrawerRect::draw(MenuOptions *menu) {
  static const int WIDTH = menu->get_width();
  static const int HEIGHT = menu->get_height();
  static const int FRAME_THIKCNESS = 5;
  static const SDL_Color FRAME_COLOR = {0, 0, 0, 255};
  static const SDL_Color BACKGROUD_COLOR = {255, 255, 255, 255};
  static SDL_Rect frame{0, 0, WIDTH + FRAME_THIKCNESS * 2, HEIGHT + FRAME_THIKCNESS * 2};
  static SDL_Rect background{0, 0, WIDTH, HEIGHT};
  static std::vector<Texture> menu_options;
  static int largest_option = 0;

  if (menu_options.empty())
    largest_option = generate_menu_texture(menu_options, menu);

  frame.x = menu->get_xpos();
  frame.y = menu->get_ypos();
  background.x = frame.x + FRAME_THIKCNESS;
  background.y = frame.y + FRAME_THIKCNESS;

  draw_rect(renderer, &frame, FRAME_COLOR);
  draw_rect(renderer, &background, BACKGROUD_COLOR);

  menu_arrow.render(renderer,
                    frame.x + (WIDTH - largest_option) / 2 - menu_arrow.get_width() - 5,
                    frame.y + MENU_VERTICAL_PADDING + ARROW_VERTICAL_OFFSET + menu->get_selected_option_index() * OPTION_HEIGHT);
  menu_title.render(renderer, frame.x + (WIDTH - menu_title.get_width()) / 2, frame.y + 20);

  int i = 0;
  for (auto &option: menu_options) {
    option.render(renderer, frame.x + (WIDTH - option.get_width()) / 2, frame.y + i + MENU_VERTICAL_PADDING);
    i += OPTION_HEIGHT;
  }
}

void TetrisDrawerRect::draw(TitleScreen *menu) {
  static const int WIDTH = menu->get_width();
  static const int HEIGHT = menu->get_height();
  static const int NB_OPTIONS = menu->get_nb_options();
  static const int Y_OFFSET = HEIGHT - NB_OPTIONS * OPTION_HEIGHT - MENU_VERTICAL_PADDING;
  static std::vector<Texture> menu_options;
  static int largest_option = 0;

  if (menu_options.empty())
    largest_option = generate_menu_texture(menu_options, menu);

  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
  SDL_RenderClear(renderer);

  menu_arrow.render(renderer,
                    (WIDTH - largest_option) / 2 - menu_arrow.get_width() - 5,
                    menu->get_selected_option_index() * OPTION_HEIGHT + Y_OFFSET + ARROW_VERTICAL_OFFSET);

  int i = 0;
  for (auto &option: menu_options) {
    option.render(renderer, (WIDTH - option.get_width()) / 2, i + Y_OFFSET);
    i += OPTION_HEIGHT;
  }

  std::ignore = menu;
}

void TetrisDrawerRect::draw(Tetromino *tetromino, int xpos, int ypos) {
  SDL_Rect rect = {xpos * unit_size, ypos * unit_size, unit_size, unit_size};

  for (int i = 0; i < tetromino->matrix_size(); i++) {
    for (int j = 0; j < tetromino->matrix_size(); j++) {
      if (tetromino->is_present(i, j)) {
        rect.x = (xpos + j) * unit_size;
        rect.y = (ypos + i - TOP_OFFSET) * unit_size;
        draw_rect(renderer, &rect, get_tetromino_color(tetromino->get_tile(i, j)));
      }
    }
  }
}

void TetrisDrawerRect::draw_game_over() {
  game_over.render(renderer,
                   (engine->get_window_width() - game_over.get_width()) / 2,
                   (engine->get_window_height() - game_over.get_height() - 10));
}

SDL_Color TetrisDrawerRect::get_tetromino_color(int tile) {
  switch (tile) {
  case 1:
  case 2:
  case 3        :return {49, 199, 239, 255};
  case 4        :return {247, 211, 8, 255};
  case 5        :return {173, 77, 156, 255};
  case 6        :return {66, 182, 66, 255};
  case 7        :return {239, 32, 41, 255};
  case 8        :return {90, 101, 173, 255};
  case 9        :return {239, 121, 33, 255};
  case 42       :return {127, 64, 20, 255};
  default       :return {255, 255, 255, 255};
  }
}

void TetrisDrawerRect::draw_rect(SDL_Renderer *renderer, SDL_Rect *rect, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, rect);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // the rect border color (solid black)
  SDL_RenderDrawRect(renderer, rect);
}

void TetrisDrawerRect::draw_right_zone(int xpos, int ypos, int width, int height) {
  static const int BORDER_TILE = 42;
  SDL_Rect rect = {xpos, ypos, unit_size, unit_size};

  for (int i = 0; i < width; i++) {
    rect.x = xpos + i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }

  for (int i = 1; i < height - 1; i++) {
    rect.y = ypos + i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }

  rect.y += unit_size;
  for (int i = 0; i < width; i++) {
    rect.x = xpos + i * unit_size;
    draw_rect(renderer, &rect, get_tetromino_color(BORDER_TILE));
  }
}

int TetrisDrawerRect::generate_menu_texture(std::vector<Texture> &menu_options, Menu *menu) {
  int largest_width = 0;
  if (font != nullptr) {
    menu_options.reserve(menu->get_nb_options());
    for (auto &option : menu->get_options()) {
      menu_options.emplace_back();
      if (!menu_options.back().loadFromRenderedText(renderer, font, option, textColor))
        printf("%s", std::string("Failed to render \"" + option + "\" texture!\n").c_str());

      if (menu_options.back().get_width() > largest_width)
        largest_width = menu_options.back().get_width();
    }
  }
  return largest_width;
}