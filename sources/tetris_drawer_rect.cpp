
#include <tetris_drawer_rect.h>

constexpr SDL_Color TetrisDrawerRect::textColor;

TetrisDrawerRect::TetrisDrawerRect(TTF_Font *font, SDL_Renderer *renderer) : font(font), renderer(renderer) {
  if (font != nullptr) {
    //Render text
    if (!score_header.loadFromRenderedText(renderer, font, "Score", textColor))
      printf("Failed to render \"score header\" texture!\n");
    if (!level_header.loadFromRenderedText(renderer, font, "Level", textColor))
      printf("Failed to render \"level header\" texture!\n");
  }
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
  static const int WIDTH = 8;
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
  draw(bag->preview().get(), Well::WIDTH+1, 9);
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
