#ifndef GAME_H
#define GAME_H

class Game {
 public:
  virtual void pause() = 0;
  virtual void unpause() = 0;
  virtual void quit() = 0;
  virtual void restart() = 0;
};

#endif //GAME_H
