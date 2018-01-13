
#include "canvas.h"

#include <stddef.h>

#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "common.h"
#include "dragon.h"
#include "dragon_hoard.h"
#include "merchant.h"
#include "item.h"
#include "stairway.h"

namespace game {

Canvas::Canvas(int x, int y)
  : width_(x), height_(y), player_(NULL), factory_(new Factory()),
  level_(0), cells_(NULL), layout_("floor.txt"),
  display_(new Display(x, y)), turn_(1),
  stopwander_(false), stopdeath_(false) {}

Canvas::~Canvas() {
  delete factory_;
  delete display_;
}

Canvas* Canvas::canvas_ = NULL;

Canvas* Canvas::GetInstance() {
  if (canvas_ == NULL) {
    canvas_ = new Canvas(kDisplayWidth, kDisplayHeight);
    return canvas_;
  }
  return canvas_;
}

void Canvas::delete_objects() {
  for (int i=0; i<height_; ++i)
  {
    for (int j=0; j!=width_; ++j) {
      if (cells_[i][j].get_object()) {
        delete cells_[i][j].get_object();
        cells_[i][j].set_object(NULL);
      }
    }
  }
}

void Canvas::delete_cells() {
  for (int i=0; i<height_; ++i)
  {
    delete [] cells_[i];
  }
  delete [] cells_;
}

void Canvas::clear() {
  for (std::size_t i=0; i<5; ++i)
  {
    chamber_[i].clear();
  }
  if (player_) {
    cells_[player_->get_x()][player_->get_y()].set_object(NULL);
  }
  delete_objects();
  delete_cells();
}

void Canvas::init_cells() {
  cells_ = new Cell* [height_];
  for (int i=0; i<height_; ++i) {
    cells_[i] = new Cell[width_];
    for (int j=0; j<width_; ++j) {
      cells_[i][j].set_position(i, j);
      cells_[i][j].set_object(NULL);
    }
  }
}

void Canvas::init_object_in_cells(const std::string board[]) {
  for (int i=0; i<height_; ++i) {
    std::string temp = board[i];
    for (int j=0; j<width_; ++j) {
      if ('.' == temp[j]) {
        cells_[i][j].set_status(false);
        FloorUnit* tmp = factory_->create_floorunit(kGround);
        cells_[i][j].set_object(tmp);
      } else if ('|' == temp[j]) {
        cells_[i][j].set_status(true);
        FloorUnit* tmp = factory_->create_floorunit(kVerticalWall);
        cells_[i][j].set_object(tmp);
      } else if ('-' == temp[j]) {
        cells_[i][j].set_status(true);
        FloorUnit* tmp = factory_->create_floorunit(kHorizontalWall);
        cells_[i][j].set_object(tmp);
      } else if ('+' == temp[j]) {
        cells_[i][j].set_status(true);
        FloorUnit* tmp = factory_->create_floorunit(kDoor);
        cells_[i][j].set_object(tmp);
      } else if ('#' == temp[j]) {
        cells_[i][j].set_status(true);
        FloorUnit* tmp = factory_->create_floorunit(kPassage);
        cells_[i][j].set_object(tmp);
      } else if ('g' == temp[j]) {
        cells_[i][j].set_status(true);
        Enemy* tmp = factory_->create_enemy(kEnemyGoblin);
        cells_[i][j].set_object(tmp);
        tmp->set_position(i, j);
      } else if ('M' == temp[j]) {
        cells_[i][j].set_status(true);
        Enemy* tmp = factory_->create_enemy(kEnemyMerchant);
        cells_[i][j].set_object(tmp);
        tmp->set_position(i, j);
      } else if ('O' == temp[j]) {
        cells_[i][j].set_status(true);
        Enemy* tmp = factory_->create_enemy(kEnemyOrc);
        cells_[i][j].set_object(tmp);
        tmp->set_position(i, j);
      } else if ('D' == temp[j]) {
        cells_[i][j].set_status(true);
        Enemy* tmp = factory_->create_enemy(kEnemyDragon);
        cells_[i][j].set_object(tmp);
        tmp->set_position(i, j);
      } else if ('X' == temp[j]) {
        cells_[i][j].set_status(true);
        Enemy* tmp = factory_->create_enemy(kEnemyGridBug);
        cells_[i][j].set_object(tmp);
        tmp->set_position(i, j);
      } else if ('0' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionRH);
        cells_[i][j].set_object(tmp);
      } else if ('1' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionBA);
        cells_[i][j].set_object(tmp);
      } else if ('2' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionBD);
        cells_[i][j].set_object(tmp);
      } else if ('3' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionPH);
        cells_[i][j].set_object(tmp);
      } else if ('4' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionWA);
        cells_[i][j].set_object(tmp);
      } else if ('5' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kPotionWD);
        cells_[i][j].set_object(tmp);
      } else if ('6' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kTreasureGoldPile);
        cells_[i][j].set_object(tmp);
      } else if ('7' == temp[j]) {
        cells_[i][j].set_status(true);
        Item* tmp = factory_->create_item(kTreasureDragonHoard);
        cells_[i][j].set_object(tmp);
      } else if ('>' == temp[j]) {
        cells_[i][j].set_status(true);
        FloorUnit* tmp = factory_->create_floorunit(kStairway);
        cells_[i][j].set_object(tmp);
      } else if ('@' == temp[j]) {
        player_x_ = i;
        player_y_ = j;
      }
    }
  }
}

void Canvas::init_object_in_cells_from_file(const std::string& filename) {
  std::ifstream ifs(filename.c_str());
  for (int i=0; i!=height_; ++i) {
    std::string temp;
    getline(ifs, temp);
    board_[i] = temp;
  }
  init_object_in_cells(board_);
}

void Canvas::init_chambers() {
  //chamber_[0].clear();
  for(int i = 3; i < 7; i++) {
    for(int j = 3; j < 29; j++) {
      chamber_[0].push_back(&cells_[i][j]);
    }
  }

  //chamber_[1].set_count(1);
  for(int i = 15; i < 22; i++) {
    for(int j = 4; j < 25; j++) {
      chamber_[1].push_back(&cells_[i][j]);
    }
  }

  //chamber_[2].set_count(2);
  for(int i = 10; i < 13; i++) {
    for(int j = 38; j < 50; j++) {
      chamber_[2].push_back(&cells_[i][j]);
    }
  }

  //chamber_[3].set_count(3);
  for(int i = 19; i < 22; i++) {
    for(int j = 37; j < 65; j++) {
      chamber_[3].push_back(&cells_[i][j]);
    }
  }

  for(int i = 16; i < 22; i++) {
    for(int j = 65; j < 76; j++) {
      chamber_[3].push_back(&cells_[i][j]);
    }
  }

  //chamber_[4].set_count(4);
  for(int i = 3; i < 7; i++) {
    for(int j = 39; j < 61; j++) {
      chamber_[4].push_back(&cells_[i][j]);
    }
  }

  for(int i = 6; i < 13; i++) {
    for(int j = 70; j < 73; j++) {
      chamber_[4].push_back(&cells_[i][j]);
    }
  }

  for(int i = 7; i < 13; i++) {
    for (int j = 73; j < 76;j++) {
      chamber_[4].push_back(&cells_[i][j]);
    }
  }

  for(int i = 5; i < 13; i++) {
    for(int j = 62; j < 70; j++) {
      chamber_[4].push_back(&cells_[i][j]);
    }
  }

  for (int i = 3; i < 13; i++) {
    chamber_[4].push_back(&cells_[i][61]);
  }
}

void Canvas::generate_board() {
  board_[0] = "|-----------------------------------------------------------------------------|";
  board_[1] = "|                                                                             |";
  board_[2] = "| |--------------------------|        |-----------------------|               |";
  board_[3] = "| |..........................|        |.......................|               |";
  board_[4] = "| |..........................+########+.......................|-------|       |";
  board_[5] = "| |..........................|   #    |...............................|--|    |";
  board_[6] = "| |..........................|   #    |..................................|--| |";
  board_[7] = "| |----------+---------------|   #    |----+----------------|...............| |";
  board_[8] = "|            #                 #############                |...............| |";
  board_[9] = "|            #                 #     |-----+------|         |...............| |";
  board_[10] = "|            #                 #     |............|         |...............| |";
  board_[11] = "|            ###################     |............|   ######+...............| |";
  board_[12] = "|            #                 #     |............|   #     |...............| |";
  board_[13] = "|            #                 #     |-----+------|   #     |--------+------| |";
  board_[14] = "|  |---------+-----------|     #           #          #              #        |";
  board_[15] = "|  |.....................|     #           #          #         |----+------| |";
  board_[16] = "|  |.....................|     ########################         |...........| |";
  board_[17] = "|  |.....................|     #           #                    |...........| |";
  board_[18] = "|  |.....................|     #    |------+--------------------|...........| |";
  board_[19] = "|  |.....................|     #    |.......................................| |";
  board_[20] = "|  |.....................+##########+.......................................| |";
  board_[21] = "|  |.....................|          |.......................................| |";
  board_[22] = "|  |---------------------|          |---------------------------------------| |";
  board_[23] = "|                                                                             |";
  board_[24] = "|-----------------------------------------------------------------------------|";
}

void Canvas::initialize() {
  init_cells();
  init_object_in_cells_from_file(layout_);
  init_chambers();
}

void Canvas::init_board_random() {
  init_cells();
  generate_board();
  init_object_in_cells(board_);
  init_chambers();
  spawn_player(player_type_);
  spawn_item();
  spawn_enemies();

  set_turn(1);
  set_level(0);
}

void Canvas::init_board_from_file() {
  init_cells();
  init_object_in_cells_from_file(layout_);
  init_chambers();
  spawn_player(player_type_, player_x_, player_y_);

  set_turn(1);
  set_level(0);
}

void Canvas::spawn_player(int type) {
  int number = rand() % 5;
  int num_tile = rand() % chamber_[number].get_size();
  int i = chamber_[number].get_cell(num_tile)->get_x();
  int j = chamber_[number].get_cell(num_tile)->get_y();
  spawn_player(type, i, j);
  chamber_player_ = num_tile;
}

void Canvas::spawn_player(int type, int i, int j) {
  if (cells_[i][j].get_object()) {
    if ((cells_[i][j].get_object()->get_type() & kMaskPlayer)  == kPlayer)
      player_ = NULL;
    delete cells_[i][j].get_object();
    cells_[i][j].set_object(NULL);
  }

  if (!player_) {
    Player* tmp = factory_->create_player(type);
    player_ = tmp;
  }
  player_->set_position(i, j);
  cells_[i][j].set_object(player_);
  cells_[i][j].set_status(true);
  cells_[i][j].notify_display(*display_);
}

void Canvas::spawn_stair() {
  int number = rand() % 5;
  int num_tile = rand() % chamber_[number].get_size();
  int i = chamber_[number].get_cell(num_tile)->get_x();
  int j = chamber_[number].get_cell(num_tile)->get_y();
  if (cells_[i][j].get_status() || chamber_player_ == number) {
    spawn_stair();
  } else {
    if (cells_[i][j].get_object()) {
      delete cells_[i][j].get_object();
    }
    cells_[i][j].set_object(NULL);
    FloorUnit* tmp = factory_->create_floorunit(kStairway);
    cells_[i][j].set_object(tmp);
    cells_[i][j].set_status(true);
    cells_[i][j].notify_display(*display_);
  }
}

void Canvas::spawn_item() {
  std::map<int, int> mp;
  mp[0] = kPotionRH;
  mp[1] = kPotionBA;
  mp[2] = kPotionBD;
  mp[3] = kPotionPH;
  mp[4] = kPotionWA;
  mp[5] = kPotionWD;

  mp[10] = kTreasureGoldPile;
  mp[11] = kTreasureGoldPile;
  mp[12] = kTreasureGoldPile;
  mp[13] = kTreasureGoldPile;
  mp[14] = kTreasureGoldPile;
  mp[15] = kTreasureGoldPile;
  mp[16] = kTreasureGoldPile;
  mp[17] = kTreasureDragonHoard;

  int type;
  for (int i=0; i<kCountPotion; ++i) {
    type = rand() % 6;
    int number = rand() % 5;
    int num_tile = rand() % chamber_[number].get_size();
    int x = chamber_[number].get_cell(num_tile)->get_x();
    int y = chamber_[number].get_cell(num_tile)->get_y();

    if (cells_[x][y].get_status()) {
      --i;
    } else {
      if (cells_[x][y].get_object()) {
        delete cells_[x][y].get_object();
      }
      cells_[x][y].set_object(NULL);
      Item* tmp = factory_->create_item(mp[type]);
      cells_[x][y].set_object(tmp);
      cells_[x][y].set_status(true);
    }
  }

  for (int i=0; i<kCountGold; ++i) {
    type = rand() % 8;
    int number = rand() % 5;
    int num_tile = rand() % chamber_[number].get_size();
    int x = chamber_[number].get_cell(num_tile)->get_x();
    int y = chamber_[number].get_cell(num_tile)->get_y();

    if (kTreasureDragonHoard == mp[type + 10]) {
      int tmp_x, tmp_y;
      bool status = false;
      std::vector<int> vec;
      for (int j=0; j<8; ++j) {
        vec.push_back(j);
      }
      bool flag = false;

      while (vec.size()) {
        int dire = rand() % vec.size();
        switch (dire) {
          case 0 : tmp_x = x - 1; tmp_y = y;
                   break;
          case 1 : tmp_x = x + 1; tmp_y = y;
                   break;
          case 2 : tmp_x = x; tmp_y = y + 1;
                   break;
          case 3 : tmp_x = x; tmp_y = y - 1;
                   break;
          case 4 : tmp_x = x - 1; tmp_y = y + 1;
                   break;
          case 5 : tmp_x = x - 1; tmp_y = y - 1;
                   break;
          case 6 : tmp_x = x + 1; tmp_y = y + 1;
                   break;
          case 7 : tmp_x = x + 1; tmp_y = y - 1;
                   break;
        }
        if (cells_[tmp_x][tmp_y].get_status() == false) {
          flag = true;
          break;
        }
        vec.erase(vec.begin() + dire);
      }

      if (flag == false) {
        --i;
        continue;
      } else {
        Item* tmp = NULL;
        tmp = factory_->create_item(kTreasureDragonHoard);
        if (cells_[x][y].get_object()) {
          delete cells_[x][y].get_object();
        }
        cells_[x][y].set_object(NULL);
        cells_[x][y].set_object(tmp);

        DragonHoard* drgh = dynamic_cast<DragonHoard*>(tmp);
        drgh->set_cell(&cells_[tmp_x][tmp_y]);
        cells_[x][y].set_status(true);
        cells_[x][y].notify_display(*display_);

        Enemy* dragon = NULL;
        dragon = factory_->create_enemy(kEnemyDragon);
        if (cells_[tmp_x][tmp_y].get_object()) {
          delete cells_[tmp_x][tmp_y].get_object();
        }
        cells_[tmp_x][tmp_y].set_object(NULL);

        Dragon* drg = dynamic_cast<Dragon*>(dragon);
        cells_[tmp_x][tmp_y].set_object(drg);
        drg->set_cell(&cells_[x][y]);
        cells_[tmp_x][tmp_y].set_status(true);
        cells_[tmp_x][tmp_y].notify_display(*display_);
      }
    } else {
      if (cells_[x][y].get_object()) {
        delete cells_[x][y].get_object();
      }
      cells_[x][y].set_object(NULL);
      Item* tmp = factory_->create_item(mp[10+type]);
      cells_[x][y].set_object(tmp);
      cells_[x][y].set_status(true);
      cells_[x][y].notify_display(*display_);
    }
  }
}

void Canvas::spawn_enemies() {
  for (int i=0; i<kCountEnemy; ++i) {
    std::map<int, int> mp;
    mp[0] = kEnemyGridBug;
    mp[1] = kEnemyGridBug;
    mp[2] = kEnemyGoblin;
    mp[3] = kEnemyGoblin;
    mp[4] = kEnemyOrc;
    mp[5] = kEnemyMerchant;

    int type = rand() % mp.size();

    int number = rand() % 5;
    int num_tile = rand() % chamber_[number].get_size();
    int x = chamber_[number].get_cell(num_tile)->get_x();
    int y = chamber_[number].get_cell(num_tile)->get_y();
    if (cells_[x][y].get_status()) {
      --i;
    } else {
      if (cells_[x][y].get_object()) {
        delete cells_[x][y].get_object();
      }
      cells_[x][y].set_object(NULL);
      Enemy* tmp = factory_->create_enemy(mp[type]);
      tmp->set_position(x, y);
      cells_[x][y].set_object(tmp);
      cells_[x][y].set_status(true);
      cells_[x][y].notify_display(*display_);
    }
  }
}

void Canvas::move() {
  std::vector<Enemy*> vec_en;
  for (int i=0; i<height_; ++i) {
    for (int j=0; j<width_; ++j) {
      if (cells_[i][j].get_object()) {
        int type = cells_[i][j].get_object()->get_type();
        if (type == kEnemyGoblin
            || type == kEnemyGridBug
            || type == kEnemyMerchant
            || type == kEnemyOrc
           ) {
          Enemy* tmp = dynamic_cast<Enemy*>(cells_[i][j].get_object());
          vec_en.push_back(tmp);
        }
      }
    }
  }

  std::vector<int> vec_tmp;
  for (int i=0; i<8; ++i) {
    vec_tmp.push_back(i);
  }
  int cur_x, cur_y;
  bool is_fight = false;

  for (std::size_t i=0; i<vec_en.size(); ++i) {
    cur_x = vec_en[i]->get_x();
    cur_y = vec_en[i]->get_y();
    int next_x = cur_x;
    int next_y = cur_y;;
    for (int j=0; j<8; ++j) {
      switch (j) {
        case 0 : next_x = cur_x - 1; next_y = cur_y;
                 break;
        case 1 : next_x = cur_x + 1; next_y = cur_y;
                 break;
        case 2 : next_x = cur_x; next_y = cur_y + 1;
                 break;
        case 3 : next_x = cur_x; next_y = cur_y - 1;
                 break;
        case 4 : next_x = cur_x - 1; next_y = cur_y + 1;
                 break;
        case 5 : next_x = cur_x - 1; next_y = cur_y - 1;
                 break;
        case 6 : next_x = cur_x + 1; next_y = cur_y + 1;
                 break;
        case 7 : next_x = cur_x + 1; next_y = cur_y - 1;
                 break;
      }

      Object* obj_def = cells_[next_x][next_y].get_object();
      if (obj_def) {
        if ((obj_def->get_type() & kMaskPlayer) == kPlayer) {
          Player* p = dynamic_cast<Player*>(cells_[next_x][next_y].get_object());
          std::string result = vec_en[i]->attack(next_x, next_y);
          if (result.length() != 0)
            std::cout << result << std::endl;
          is_fight = true;
          break;
        }
      }
    }

    bool is_found = false;
    std::vector<int> direc;
    for (int j=0; j<8; ++j) {
      direc.push_back(j);
    }
    while (direc.size()) {
      size_t direction = rand() % 8;
      if (direction >= direc.size()) {
        continue;
      }
      if(direction == 0) { next_x = cur_x - 1; next_y = cur_y;  }
      else if(direction == 1) { next_x = cur_x + 1; next_y = cur_y;  }
      else if(direction == 2) { next_x = cur_x; next_y = cur_y + 1; }
      else if(direction == 3) { next_x = cur_x; next_y = cur_y - 1; }
      else if(direction == 4) { next_x = cur_x - 1; next_y = cur_y + 1;  }
      else if(direction == 5) { next_x = cur_x - 1; next_y = cur_y - 1;  }
      else if(direction == 6) { next_x = cur_x + 1; next_y = cur_y + 1;  }
      else if(direction == 7) { next_x = cur_x + 1; next_y = cur_y - 1;  }
      if (cells_[next_x][next_y].get_object()) {
        if (cells_[next_x][next_y].get_object()->get_type() == kGround) {
          is_found = true;
          break;
        }
      }
      direc.erase(direc.begin() + direction);
    }
    if (is_found && ! is_fight) {
      Object* obj;
      obj = cells_[cur_x][cur_y].get_object();
      cells_[cur_x][cur_y].set_status(false);
      FloorUnit* floor = NULL;
      floor = factory_->create_floorunit(kGround);
      cells_[cur_x][cur_y].set_object(floor);

      delete cells_[next_x][next_y].get_object();
      cells_[next_x][next_y].set_object(NULL);
      cells_[next_x][next_y].set_status(true);
      cells_[next_x][next_y].set_object(obj);
      vec_en[i]->set_position(next_x, next_y);
      cells_[cur_x][cur_y].notify_display(*display_);
      cells_[next_x][next_y].notify_display(*display_);
    }
  }
}

void Canvas::print() {
  for (int i =0; i<height_; ++i) {
    for (int j=0; j<width_; ++j) {
      Object * obj = cells_[i][j].get_object();
      if (obj) {
        int type = cells_[i][j].get_object()->get_type();
        if ( type == kVerticalWall ) {
          std::cout << '|';
        } else if ( type == kHorizontalWall ) {
          std::cout << '-';
        } else if ( type == kDoor ) {
          std::cout << '+';
        } else if ( type == kPassage) {
          std::cout << '#';
        } else if (type == kGround) {
          std::cout << '.';
        } else if ((type & kMaskPlayer) == kPlayer) {
          std::cout << '@';
        } else if (type == kStairway) {
          std::cout << '>';
        } else if (type == kEnemyGridBug) {
          std::cout << 'X';
        } else if (type == kEnemyGoblin) {
          std::cout << 'g';
        } else if (type == kEnemyMerchant) {
          std::cout << 'M';
        } else if (type == kEnemyOrc) {
          std::cout << 'O';
        } else if (type == kEnemyDragon) {
          std::cout << 'D';
        } else if ((type & kMaskPotion) == kPotion) {
          std::cout << '!';
        } else if ((type & kMaskTreasure) == kTreasure) {
          std::cout << '$';
        } else {
          std::cout << 'T';
        }
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
  if (player_) {
    printf("\tClass: %s\tGP: %d\t\tFloor %d\n\tHP: %d/%d\tAtk: %d\t\tDef: %d%%\tTurn: %d\n",
        get_name(player_->get_type()).c_str(),
        player_->get_wallet(),
        level_ + 1,
        player_->get_HP(),
        player_->get_HP_max(),
        player_->get_attack(),
        player_->get_defense(),
        turn_);
    printf("\nWhat will you do?\n");
  }
}

} //namespace game
