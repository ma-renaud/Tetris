#ifndef TETRIS_SCORE_LVL_H
#define TETRIS_SCORE_LVL_H

class ScoreLvl {
 public:
  ScoreLvl() = default;
  ~ScoreLvl() = default;

  void update(int nb_lines_cleared);
  void restart();
  int get_score() { return score; }
  int get_level() { return level; }
  int get_xpos() const { return xpos; }
  int get_ypos() const { return ypos; }
  void set_xpos(int pos) { xpos = pos; }
  void set_ypos(int pos) { ypos = pos; }

  static const int MAX_SPEED_LEVEL = 25;

 private:
  int xpos = 0;
  int ypos = 0;

  static constexpr int line_points[4] = {40, 100, 300, 1200};
  static constexpr int line_awards[4] = {1, 3, 5, 8};

  int level = 0;
  int score = 0;
  int line_cleared = 0;

  void update_score(int nb_lines);
  void update_level(int nb_lines);

};

#endif //TETRIS_SCORE_LVL_H
