#include <iostream>
#include <tetris.h>

constexpr int Tetris::frame_per_row[];

Tetris::Tetris(int xpos, int ypos, int width, int height) : width(width), height(height) {

  this->width = width;
  this->height = height;

  drop_time = engine->get_ticks();

  load_a_tetromino();

}

void Tetris::handle_events() {
  EngineWrapper::Event event;
  while (engine->poll_event(event) != 0) {
    switch (event.type) {
    case EngineWrapper::EventType::KEYDOWN: {
      if (!is_game_over)
        handle_keys(event.key);
      else {
        restart();
      }
      break;
    }
    case EngineWrapper::EventType::KEYUP: {
      pressed_key = EngineWrapper::Key::UNKNOWN;
      break;
    }
    default:break;
    }
  }
}

void Tetris::handle_keys(EngineWrapper::Key key) {w
  if (!menu_stack.empty())
    menu_stack.top()->handle_keys(key);
  else {
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
    case EngineWrapper::Key::ESCAPE: {
      pause();
    }
    default:break;
    }
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

  if (!is_game_over && menu_stack.empty() && ((engine->get_ticks() > drop_time))) {
    drop_time += delay;
    check_drop();
  }
}

void Tetris::render() {
  drawer->clear();

  drawer->draw(&well);
  drawer->draw(tetromino.get());
  drawer->draw(&score);
  drawer->draw(&bag);

  if (!menu_stack.empty())
    drawer->draw(dynamic_cast<MenuPause *>(menu_stack.top()));

  if (is_game_over)
    drawer->draw_game_over();

  drawer->render();
}

void Tetris::clean() {
  engine->clean();
  std::cout << "Tetris Cleaned!" << std::endl;
}

void Tetris::restart() {
  well.clear();
  tetromino = bag.next();
  score.restart();
  drop_time = engine->get_ticks() + 1000;
  is_game_over = false;
  menu_stack.pop();
}

void Tetris::pause() {
  menu_stack.push(pause_menu.get());
}

void Tetris::unpause() {
  menu_stack.pop();
  drop_time = SDL_GetTicks() + 500;
}

void Tetris::title_screen() {

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
