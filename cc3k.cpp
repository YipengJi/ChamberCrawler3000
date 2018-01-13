#include <iostream>

#include <cstdlib>
#include <limits>
#include <cstring>

#include "player.h"
#include "enemy.h"
#include "item.h"
#include "canvas.h"
#include "display.h"

bool is_num(char* str) {
  int length = strlen(str);
  while (length) {
    --length;
    if (str[length] < '0' || str[length] > '9')
      return false;
  }
  return true;
}

int main(int argc, char * argv[]) {
  int seed = time(NULL);
  std::string board = "";
  if (argc != 1) {
    for (int i = 1; i!=argc; ++i) {
      if (is_num(argv[i])) {
        seed = atoi(argv[i]);
      } else {
        board = argv[i];
      }
    }
  }

  srand(static_cast<unsigned int>(seed));

  char input = 'q';
  std::cout << "Welcome to ChamberCrawler3000!" << std::endl;
  std::cout << "What would you like to play as today?" << std::endl;
  std::cout << "w) Wizard" << std::endl;
  std::cout << "k) Knight" << std::endl;
  std::cout << "s) Samurai" << std::endl;
  std::cin >> input;

  game::Canvas* canvas = game::Canvas::GetInstance();
  if (input == 'w') {
    canvas->set_player_type(game::kPlayerWizard);
    std::cout << "You have chosen to play as a Wizard. Good luck." << std::endl;
  }
  else if (input  == 'k') {
    canvas->set_player_type(game::kPlayerKnight);
    std::cout << "You have chosen to play as a Knight. Good luck." << std::endl;
  }
  else {
    canvas->set_player_type(game::kPlayerSamurai);
    std::cout << "You have chosen to play as a Samurai. Good luck." << std::endl;
  }

  std::string result = "";
  if (board.length() == 0) {
    canvas->init_board_random();
  } else {
    canvas->set_layout(board);
    canvas->init_board_from_file();
  }
  canvas->print();
  
  std::string data, temp;;
  data = "";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (1) {
    std::getline(std::cin, data);
    if (data.length() == 0) {
      data = temp;
    } else {
      //temp = data;
    }
    if (data == "q") {
      return 0;
    } else if (data == "r") {
      canvas->clear();
      if (canvas->get_player()) {
        delete canvas->get_player();
      }
      canvas->set_player(NULL);
      canvas->set_turn(1);
      canvas->set_level(0);
      canvas->set_stopwander(false);
      canvas->set_stopdeath(false);
      canvas->initialize();
      std::cout << "Choose player type: k(knight), w(wizard), s(samurai):";
      std::cin >> input;
      canvas->spawn_player(input);
      canvas->spawn_stair();
      canvas->spawn_item();
      canvas->spawn_enemies();
    } else if (data == "no" || data == "so" || data == "ea" || data == "we"
        || data == "ne" || data == "nw" || data == "se" || data == "sw") {
      game::Player* p = canvas->get_player();
      int x = p->get_x();
      result = canvas->get_player()->move(data);
      if (result.compare("upgrade") == 0) {
        if (canvas->get_level() < 4) {
          canvas->set_level(canvas->get_level() + 1);
          canvas->clear();
          canvas->initialize();
          canvas->spawn_player(input);
          canvas->spawn_stair();
          canvas->spawn_item();
          canvas->spawn_enemies();
        } else {
          std::cout << "You finish the game." << std::endl;
          std::cout << "What do you want to do ? " << std::endl;
          std::cout << "r(restart), q(quit)?" << std::endl;
          std::cin >> input;
          if (input == 'q') {
            return 0;
          } else {
            if (canvas->get_player()) {
              delete canvas->get_player();
            }
            canvas->set_player(NULL);
            canvas->set_turn(0);
            canvas->set_level(0);
            canvas->initialize();
            std::cout << "Choose player type: k(knight), w(wizard), s(samurai):";
            std::cin >> input;
            canvas->spawn_player(input);
            canvas->spawn_stair();
            canvas->spawn_item();
            canvas->spawn_enemies();
          }
        }
      } else {
        std::cout << result << std::endl;
      }
    } else if (data == "u no" || data == "u so" || data == "u ea" || data == "u we"
        || data == "u ne" || data == "u nw" || data == "u se" || data == "u sw") {
      int cur_x = canvas->get_player()->get_x();
      int cur_y = canvas->get_player()->get_y();
      int next_y = cur_x;
      int next_x = cur_y;
      if (data == "u no") {
        next_x--;
      } else if (data == "u so") {
        next_x++;
      } else if (data == "u ea") {
        next_y++;
      } else if (data == "u we") {
        next_y--; 
      } else if (data == "u ne") {
        next_y++;
        next_x--;
      } else if (data == "u nw") {
        next_y--;
        next_x--;
      } else if (data == "u se") {
        next_y++;
        next_x++;
      } else if (data == "u sw") {
        next_y--;
        next_x++;
      }
      result = canvas->get_player()->pickup_item(data.substr(2, 2));
      std::cout << result << std::endl;
    } else if (data == "a no" || data == "a so" || data == "a ea" || data == "a we"
        || data == "a ne" || data == "a nw" || data == "a se" || data == "a sw") {
      int next_x = canvas->get_player()->get_x();
      int next_y = canvas->get_player()->get_y();
      result = canvas->get_player()->attack(data.substr(2, 2));
      std::cout << result << std::endl;
    } else if (data == "stopwander") {
      canvas->set_stopwander(true);
    } else if (data == "stopdeath") {
      canvas->set_stopdeath(true);
    }
    if (!canvas->get_stopwander()) {
      canvas->move();
    }
    if (!canvas->get_stopdeath()) {
      if (canvas->get_player()->get_HP() <= 0) {
        std::cout << "You have been bested by the"
          << " Great Cavernous Chambers. Good luck next time!"
          << std::endl;
        std::cout << "You achieved a score of"
          << canvas->get_player()->get_wallet()
          << ".you are dead." << std::endl;
        return 0;
      }
    }
    canvas->set_turn(canvas->get_turn() + 1);
    canvas->get_player()->add_HP(5);
    canvas->print();
  }
  return 0;
}
