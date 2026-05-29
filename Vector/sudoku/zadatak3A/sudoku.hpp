#pragma once
#include <vector>
#include <string>

class sudoku {
  public:
    sudoku(const std::string& fileName); // O(1)
    void displayBoard() const; // O(1)
    bool insert(const unsigned& x, const unsigned& y, const unsigned& num); // O(1)
    void setCollisions(const unsigned& x, const unsigned& y, const unsigned& num); // O(1)
    bool isWon() const; // O(1)
 private:
    class cell {
      public:
        cell(unsigned number, bool userInput) : number_(number), userInput_(userInput) {}; // O(1)
        unsigned& number() { return number_;} // O(1)
        unsigned number() const {return number_;} // O(1)
        bool isUserInput() const {return userInput_;} // O(1)
        bool isInCollision() const {return inCollision_;} // O(1)
        void setCollision() {inCollision_ = inCollisionSub_ || inCollisionRow_ || inCollisionCol_;} // O(1)
        void setCollisionRow(const bool& v) {inCollisionRow_ = v;} // O(1)
        void setCollisionCol(const bool& v) {inCollisionCol_ = v;} // O(1)
        void setCollisionSub(const bool& v) {inCollisionSub_ = v;} // O(1)
      private:
        unsigned number_;
        bool userInput_;
        bool inCollision_ = false;
        bool inCollisionRow_ = false;
        bool inCollisionCol_ = false;
        bool inCollisionSub_ = false;
    };
    std::vector<cell> board;

    


};

