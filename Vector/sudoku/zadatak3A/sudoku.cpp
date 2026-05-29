#include "sudoku.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <map>
// O(1)
sudoku::sudoku(const std::string& fileName){
  std::ifstream input(fileName);
  if(!input.is_open())
    throw std::invalid_argument("Error, can't find file!");

  for(unsigned i; input >> i;){
    cell polje(i, i == 0);
    board.push_back(polje);
  }

  if(board.size() != 81)
    throw std::invalid_argument("Error, invalid board size!");
  input.close();
}
// O(1)
void sudoku::displayBoard() const{
  for(int i = 0; i < 81;){
    if(i != 0 && i % 27 == 0)
      std::cout << "+---+---+---++---+---+---++---+---+---+\n+---+---+---++---+---+---++---+---+---+\n";
    else
      std::cout << "+---+---+---++---+---+---++---+---+---+\n";
    for(int j = 0; j < 9; ++j, ++i){
      const auto& cell = board[i];
      char collisionCharacter = cell.isInCollision() ? '*' : ' ';
      if(j != 0 && j % 3 == 0)
        std::cout << "|| ";
      else 
        std::cout << "| ";
      std::cout << collisionCharacter << " " ;
    }
    i -= 9;
    std::cout << "|" << std::endl;
    for(int j = 0; j < 9; ++j, ++i){
      const auto& cell = board[i];
      if (j != 0 && j % 3 == 0)
        std::cout << "||";
      else
        std::cout << "|";
      std::string userInputFormat; 

      if(cell.number() == 0)
        userInputFormat = "   ";
      else if(cell.isUserInput())
        userInputFormat = "(" + std::to_string(cell.number()) + ")";
      else
        userInputFormat = " " + std::to_string(cell.number()) + " ";
      std::cout << userInputFormat;
    }
    std::cout << "|" << std::endl; 
  }
  std::cout << "+---+---+---++---+---+---++---+---+---+\n";
}

// O(1)
void sudoku::setCollisions(const unsigned& x, const unsigned& y, const unsigned& num){
  unsigned row = (x-1)*9;
  std::map<int, int> sameNums;
  for(int i = row; i < row + 9; ++i){
    const auto& polje = board[i];
    const auto& broj = polje.number();
    if(broj != 0)
      sameNums[broj] += 1;
  }
  for(int i = row; i < row + 9; ++i){
    auto& polje = board[i];
    const auto& broj = polje.number();
    if(broj != 0 && sameNums[broj] > 1)
       polje.setCollisionRow(true);
    else 
      polje.setCollisionRow(false);
  }

  sameNums.clear();
  for(int i = y-1; i < 81; i += 9){
    const auto& polje = board[i];
    const auto& broj = polje.number();
    if(broj != 0)
      sameNums[broj] += 1;
  } 
  for(int i = y-1; i < 81; i += 9){
    auto& polje = board[i];
    const auto& broj = polje.number();
    if(broj != 0 && sameNums[broj] > 1)
      polje.setCollisionCol(true);
    else
      polje.setCollisionCol(false);
  }
  sameNums.clear();
  
  auto subX = ((x-1) / 3) * 3;
  auto subY = ((y-1) / 3) * 3;

  unsigned position = subX * 9 + subY;
  
  for(int i = 0; i < 3; ++i){
    int j = position + i * 9;
    for(int k = j; k < j+3; ++k){
      auto& polje = board[k];
      if(polje.number() != 0)
        sameNums[polje.number()] += 1;
    }
  }
  for(int i = 0; i < 3; ++i){ 
    int j = position + i * 9;
    for(int k = j; k < j+3; ++k){
      auto& polje = board[k];
      if(polje.number() != 0 && sameNums[polje.number()] > 1)
        polje.setCollisionSub(true);
      else
        polje.setCollisionSub(false);
    }
  }
  for(auto& polje: board)
    polje.setCollision();
}

// O(1)
bool sudoku::insert(const unsigned& x, const unsigned& y, const unsigned& num){
  if(x < 1 || x > 9 || y < 1 || y > 9 || num > 9 || num < 0)
    return false;
  cell& field = board[(x-1)*9 + (y-1)];
  if(!field.isUserInput())
    return false;
  field.number() = num;
  setCollisions(x, y, num);
  return true;

}

// O(1)
bool sudoku::isWon() const{
  for(int i = 0; i < 81; ++i){
    const auto& polje = board[i];
    const auto& broj = polje.number();
    if(broj == 0)
      return false;
    if(polje.isInCollision())
      return false;
  }
  return true;
}
