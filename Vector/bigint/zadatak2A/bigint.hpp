#pragma once
#include <vector>
#include <string>
#include <ostream>

class bigint {
  public:
    bigint(long int value); // O(n)
    bigint(const std::string& str); // O(n)
    bigint(const char* str); // O(n)
    bigint(const bigint& other)= default; // O(n)
    bigint& operator=(const bigint& other) = default; // O(n)
      


    friend std::ostream& operator<<(std::ostream& ostr, const bigint& obj); // O(n)
    friend std::istream& operator>>(std::istream& istr, bigint& obj); // O(n)
    bool operator==(const bigint& other) const; // O(n)
    bool operator<(const bigint& other) const; // O(n)
    bool operator>(const bigint& other) const{ // O(n)
      return other < *this; 
    }
    bool operator<=(const bigint& other) const{ // O(n)
      return *this < other || *this == other;
    }
    bool operator>=(const bigint& other) const{ // O(n)
      return *this > other || *this == other;
    }
    bool operator!=(const bigint& other) const{ // O(n)
      return !(*this == other);
    }

    // O(1)
    bigint& operator++(){
      *this += bigint("1"); 
      return *this;
    }
    // O(1)
    bigint operator++(int){
      bigint copy = *this;
      *this += bigint("1");
      return copy;
    }

    // O(1)
    bigint& operator--(){
      *this -= bigint("1");
      return *this;
    }

    // O(1)
    bigint operator--(int){
      bigint copy = *this;
      *this -= bigint("1");
      return copy;
    }
    bigint operator+(const bigint& other) const; // O(n)
    bigint& operator+=(const bigint& other) { // O(n)
      *this = *this + other;
      return *this;
    }

    // O(n)
    bigint operator-() const {
      if(num_.size() == 1 && num_[0] == 0)
        return *this;
      bigint copy = *this;
      copy.isNegative_ = !copy.isNegative_;
      return copy;
    }
    // O(n)
    bigint operator-(const bigint& other) const {
      return *this + (-other);
    } 
    // O(n)
    bigint& operator-=(const bigint& other) {
      *this = *this - other;
      return *this;
    }
    // O(n^2)
    bigint operator*(const bigint& other) const;
    // O(n^2)
    bigint& operator*=(const bigint& other) {
      *this = *this * other;
      return *this;
    }
    // O(n)
    bigint operator/(const bigint& other) const;
    // O(n)
    bigint& operator/=(const bigint& other) {
      *this = *this / other;
      return *this;
    }
    // O(n)
    bigint operator%(const bigint& other) const;
    // O(n)
    bigint& operator%=(const bigint& other) {
      *this = *this % other;
      return *this;
    }


    friend bigint operator+(bigint a, bigint b);

  private:
    bigint() = default;
    bool isNegative_ = false; 
    std::vector<int> num_;
};
bigint operator+(bigint a, bigint b){
  int carry = 0;
  int result = 0;

  bigint& bigger = a > b ? a : b;
  bigint& smaller = b > a  ? a : b;

  if(a.isNegative_ != b.isNegative_){
    for(int i = 0; i < bigger.num_.size(); ++i)
    {
      if(i > smaller.num_.size())
        result = bigger.num_[i] + carry;
      else
        result = bigger.num_[i] + smaller.num_[i] + carry;
      carry = result / 10;
      bigger.num_[i] = result % 10;
    }
    if(carry)
      bigger.num_.push_back(carry);
  }
  else{
    for(int i = 0; i < bigger.num_.size(); ++i){
      if(i > smaller.num_.size())
        result = bigger.num_[i] - carry;
      else 
        result = bigger.num_[i] - smaller.num_[i] - carry;

      if(result < 0 ){
        result += 10;
        carry = 1;
      }
      bigger.num_[i] = result;



    }

  }

}
