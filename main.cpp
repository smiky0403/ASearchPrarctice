#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::abs;
using std::sort;

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinished};
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(const string &path) {
  ifstream myfile(path);
  //if (myfile){cout <<"File exist" <<"\n";}else{cout <<"File not exist" <<"\n";}
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

// TODO: Write function to compare the f-value of two nodes here

bool Compare(vector<int> a, vector<int> b){
  int f1 = a[2] + a[3]; // f1 = g1 + h1
  int f2 = b[2] + b[3]; // f2 = g2 + h2
  return f1 > f2; 
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

// TODO: Write the Heuristic function here.
int Heuristic(int x1, int y1, int x2, int y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

/** 
 * Add a node to the open list and mark it as open. 
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &openlist, vector<vector<State>> &grid) {
  // Add node to open vector, and mark grid cell as closed.
  openlist.push_back(vector<int>{x, y, g, h});
  grid[x][y] = State::kClosed;
}

/** 
 * Check that a cell is valid: on the grid, not an obstacle, and clear. 
 */
bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
  if(x >= 0 && x < grid.size() && y>= 0 && y < grid[0].size() && grid[x][y] == State::kEmpty){
    return true;} else{return false;}
}

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */
void ExpandNeighbors(vector<int> &current, int goal[2], vector<vector<int>> &openlist, vector<vector<State>> &grid){
  int x = current[0];
  int y = current[1];
  int g = current[2];
  // Loop through current node's potential neighbors.
  for (int i = 0; i < 4; i++) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
    if (CheckValidCell(x2, y2, grid)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = Heuristic(x2, y2, goal[0], goal[1]);
      AddToOpen(x2, y2, g2, h2, openlist, grid);
    }
  }
}


// TODO: Write the Search function stub here.
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2] ){

    vector<vector<int>> open{};
    int x = init[0];
    int y = init[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);

    AddToOpen(x, y, g, h, open, grid);

    while(open.size()>0){
      CellSort(&open);
      auto current = open.back();  //type: vector<int>
      open.pop_back();
      x = current[0];
      y = current[1];
      cout<<x << "    "<<y<<"\n";
      grid[x][y] = State::kPath;

      if(x == goal[0] && y == goal[1]){
        grid[init[0]][init[1]]= State::kStart;
        grid[goal[0]][goal[1]]= State::kFinished;
        return grid;
      }else{ExpandNeighbors(current, goal, open, grid);}
    }
    cout << "No patch found" << "\n";
    return vector<vector<State>>{};
}


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinished: return "🏁   "; 
    default: return "0   "; 
  }
}


void PrintBoard(const vector<vector<State>> board) {
  //cout<< board.size() << "\n";
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

#include "test.cpp"
int main() {
  // TODO: Declare "init" and "goal" arrays with values {0, 0} and {4, 5} respectively.
  int init[2] = {0, 0};
  int goal[2] = {4, 5};
  auto board = ReadBoardFile("1.board");

  auto solution = Search(board, init, goal);
  // TODO: Call Search with "board", "init", and "goal". Store the results in the variable "solution".
  // TODO: Change the following line to pass "solution" to PrintBoard.
  PrintBoard(solution);

  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();


}