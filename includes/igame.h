#ifndef IGAME_H
#define IGAME_H

class IGame {
public:
  virtual void pause() = 0;
  virtual void close_menu() = 0;
  virtual void quit() = 0;
  virtual void restart() = 0;
  virtual void show_title_screen() = 0;
};

#endif //IGAME_H
