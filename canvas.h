#ifndef CANVAS_H_
#define CANVAS_H_

#include <string>

#include "cell.h"
#include "player.h"
#include "chamber.h"
#include "factory.h"
#include "display.h"

namespace game {

class Canvas {
 public:
  ~Canvas();
  void clear();
  void initialize();
  void init_cells();
  void init_object_in_cells(const std::string board[]);
  void init_object_in_cells_from_file(const std::string& filename);
  void init_chambers();
  void generate_board();
  void init_board_random();
  void init_board_from_file();
  void dele_cells();
  void delete_objects();
  void delete_cells();
  void spawn_player(int ch);
  void spawn_player(int ch, int i, int j);
  void spawn_stair();
  void spawn_item();
  void spawn_enemies();
  void move();

  int get_width() const { return width_; }
  int get_height() const { return height_; }
  int get_level() const { return level_; }
  Cell** get_cell() { return cells_; }
  void set_player(Player* p) { player_ = p; }
  Player* get_player() { return player_; }
  std::string get_layout() const { return layout_; }
  void set_layout(std::string filename) { layout_ = filename; }
  Display* get_display() { return display_; }
  void set_level(int level) { level_ = level; }
  int get_level() { return level_; }
  void set_turn(int turn) { turn_ = turn; }
  int get_turn() { return turn_; }
  void set_stopwander(bool b) { stopwander_ = b; }
  bool get_stopwander() { return stopwander_; }
  void set_stopdeath(bool b) { stopdeath_ = b; }
  bool get_stopdeath() { return stopdeath_; }
  int get_player_type() { return player_type_; }
  void set_player_type(int type) { player_type_ = type; }

  void print();

  static Canvas* GetInstance();

 private:
  Canvas(int x, int y);

  int width_;
  int height_;
  Chamber chamber_[5];

  int level_;
  Cell** cells_;
  std::string layout_;
  Player* player_;
  Factory* factory_;
  Display* display_;
  int turn_;
  bool stopwander_;
  bool stopdeath_;
  int chamber_player_;
  int player_type_;;
  int player_x_;
  int player_y_;
  std::string board_[25];
  static Canvas* canvas_;
};

} //namespace game

#endif //CANVAS_H_
