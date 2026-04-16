#pragma once
#include <iostream>
#include <string>

class Player {
  private:
    std::string username;
    int _score;
  public:
    void plusScore(int score);
    void changeUnserName(std::string& username);
    void showScore();

  Player() : username("Player"), _score(0) {}
  Player(const std::string& name, int score) : username(name), _score(score) {}
};

void Player::plusScore(int score) {
  _score += score;
}

void Player::showScore() {


  std::cout << "\t" << username << "'s " << _score << "\n";
}

namespace Score {
 // LeftPlayer RightPlayer
 Player rPlayer("rPlayer", 0);
 Player lPlayer("lPlayer", 0);
 int scoreCount(glm::vec3& r, glm::vec3& l, glm::vec3 circle);
 void win();
 bool isRPlayer;
 void clear();
}

int Score::scoreCount(glm::vec3& r, glm::vec3& l, glm::vec3 sphere) {
  int result = 0;
  if (isRPlayer) {
    result = 10 * (sphere.y - r.y + 1);
    rPlayer.plusScore(result);
  } else {
    result = 10 * (sphere.y - l.y + 1);
    lPlayer.plusScore(result);
  }
  clear();
  rPlayer.showScore();
  lPlayer.showScore();
}
void Score::clear() {
#ifdef _WIN32
  system("cls");
#else 
  system("clear");
#endif
}
