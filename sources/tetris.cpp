#include <iostream>
#include <tetris.h>

Tetris::Tetris(int fps, EngineWrapper::Engine *engine) : fps(fps), engine(engine) {
  drop_time = engine->get_ticks();
  load_a_tetromino();
}

void Tetris::handle_keys(EngineWrapper::Key key) {
  static EngineWrapper::Key pressed_key = EngineWrapper::Key::UNKNOWN;
  std::unique_ptr<Tetromino> copy;
  switch (key) {
  case EngineWrapper::Key::DOWN: {
    copy = tetromino->clone();
    copy->move(0, 1);
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case EngineWrapper::Key::RIGHT: {
    copy = tetromino->clone();
    copy->move(1, 0);
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case EngineWrapper::Key::LEFT: {
    copy = tetromino->clone();
    copy->move(-1, 0);
    if (!well.is_collision(copy.get()))
      tetromino = std::move(copy);
    break;
  }
  case EngineWrapper::Key::UP: {
    if (key != pressed_key) {
      copy = tetromino->clone();
      copy->rotate(Rotation::CCW);
      if (!well.is_collision(copy.get()))
        tetromino = std::move(copy);
    }
    break;
  }
  default:break;
  }
  pressed_key = key;
}

void Tetris::update() {
  static int last_level = -1;
  static int delay;
  if (last_level != score.get_level()) {
    last_level = score.get_level();
    delay = get_speed_ms();
  }

  if (!is_game_over && !is_pause && ((engine->get_ticks() > drop_time))) {
    drop_time += delay;
    check_drop();
  }
}

void Tetris::render(TetrisDrawer *drawer) {
  drawer->draw(&well);
  drawer->draw(tetromino.get());
  drawer->draw(&score);
  drawer->draw(&bag);
}

void Tetris::restart() {
  well.clear();
  tetromino = bag.next();
  score.restart();
  drop_time = engine->get_ticks() + 1000;
  is_game_over = false;
  is_pause = false;
}

void Tetris::check_drop() {
  std::unique_ptr<Tetromino> copy = tetromino->clone();
  copy->move(0, 1);
  if (!well.is_collision(copy.get()))
    tetromino = std::move(copy);
  else {
    well.add_to_well(tetromino.get());
    score.update(well.clear_lines());
    load_a_tetromino();
  }
}

void Tetris::check_game_over() {
  is_game_over = (tetromino->ypos() == 0);
}

void Tetris::load_a_tetromino() {
  tetromino = bag.next();
  while (!is_game_over && well.is_collision(tetromino.get())) {
    tetromino->move(0, -1);
    check_game_over();
  }
}

int Tetris::get_speed_ms() {
  return (1000 * frame_per_row[std::min(score.get_level(), ScoreLvl::MAX_SPEED_LEVEL - 1)] / fps);
}