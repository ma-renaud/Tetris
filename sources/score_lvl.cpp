#include <score_lvl.h>

constexpr int ScoreLvl::line_points[];
constexpr int ScoreLvl::line_awards[];

void ScoreLvl::update(int nb_lines_cleared) {
  if (nb_lines_cleared > 0) {
    update_score(nb_lines_cleared);
    update_level(nb_lines_cleared);
  }
}

void ScoreLvl::restart() {
  score = 0;
  level = 0;
  line_cleared = 0;
}

void ScoreLvl::update_score(int nb_lines) {
  score += ScoreLvl::line_points[nb_lines - 1] * (level + 1);
}

void ScoreLvl::update_level(int nb_lines) {
  line_cleared += ScoreLvl::line_awards[nb_lines - 1];
  if (line_cleared >= (level + 1) * 5) {
    line_cleared = 0;
    level++;
  }
}

