#include "bigint.hpp"
#include <stdexcept>
#include <algorithm>

// O(n)
bigint::bigint(long int value){
  isNegative_ = value < 0;
  if (value == 0){
    num_.push_back(0);
  }
  isNegative_ = value < 0;
  for(; value != 0; value /= 10){
    int digit = std::abs(value % 10);
    num_.push_back(digit);
  }      
}

// O(n)
bigint::bigint(const std::string& str){
  if(str.empty())
    throw std::invalid_argument("String is empty");
  auto it = str.begin();
  isNegative_ = *it == '-';
  if (isNegative_)
    ++it;
  for(; it != str.end(); ++it){
    if(*it < '0' || *it > '9')
      throw std::invalid_argument("Error, invalid numbers!");
    num_.push_back(*it - '0');
  }
  std::reverse(num_.begin(), num_.end());
}

// O(n)
bigint::bigint(const char* str){
  int i = 0;
  if (*str == '-'){
    isNegative_ = true;
    ++i;
  }
  for(; *(str + i) != '\0'; ++i){
    if(*(str+i) < '0' || *(str+i) > '9')
      throw std::invalid_argument("Error, invalid number!");
    num_.push_back(*(str + i) - 48);
  }
  std::reverse(num_.begin(), num_.end());
}

// O(n)
std::ostream& operator<<(std::ostream& ostr, const bigint& obj){
  if (obj.isNegative_)
    ostr << '-';
  for(auto it = obj.num_.rbegin(); it != obj.num_.rend(); ++it){
    ostr << *it;
  }
  return ostr;
}

// O(n)
std::istream& operator>>(std::istream& istr, bigint& obj){
  std::string str;
  istr >> str;
  if(str[0] != '-' && ( str[0] < '0' || str[0] > '9'))
    throw std::invalid_argument("Error, invalid input");

  if(str[0] == '-' && str.size() < 2)
    throw std::invalid_argument("Error, invalid input");

  for(auto it = ++str.begin(); it != str.end(); ++it){
    if(*it > '9' || *it < '0')
      throw std::invalid_argument("Error, invalid input!");
  }

  bigint newObj(str);
  obj = newObj;
  return istr;
}

// O(n)
bool bigint::operator==(const bigint& other) const{
  if((isNegative_ != other.isNegative_) || (num_.size() != other.num_.size()))
    return false;
  for(int i = 0; i < num_.size(); ++i){
    if(num_[i] != other.num_[i])
      return false;
  }
  return true;
}

// O(n)
bool bigint::operator<(const bigint& other) const{
  if(isNegative_ && !other.isNegative_)
    return true;
  else if (!isNegative_ && other.isNegative_)
    return false;
  if(isNegative_){
    if(num_.size() != other.num_.size())
      return num_.size() > other.num_.size();
    for(int i = num_.size()-1; i >= 0; --i){
      if(num_[i] != other.num_[i])
        return num_[i] > other.num_[i];
    }
  }
  else {
    if(num_.size() != other.num_.size())
      return num_.size() < other.num_.size();
    for(int i = num_.size()-1; i >= 0; --i){
      if(num_[i] != other.num_[i])
        return num_[i] < other.num_[i];
    }
  }
  return false;
}

// O(n)
bigint bigint::operator+(const bigint& other) const{
  bigint result;
  int carry = 0;
  int digit = 0;
  int sum;

  auto temp1 = *this;
  auto temp2 = other;
  temp1.isNegative_ = false;
  temp2.isNegative_ = false;

  const bigint& bigger = (temp1 < temp2) ? other : *this;
  const bigint& smaller = (temp1 < temp2) ? *this : other;

  result.isNegative_ = (temp1 < temp2) ? other.isNegative_ : isNegative_;

  if(isNegative_ == other.isNegative_){
    for(auto i = 0; i < bigger.num_.size(); ++i){
      sum = bigger.num_[i] + carry;
      if(i < smaller.num_.size())
        sum += smaller.num_[i];
      carry = sum / 10;
      digit = sum % 10;
      result.num_.push_back(digit);
    }
    if(carry)
      result.num_.push_back(carry);
  }
  else{
    for(auto i = 0; i < bigger.num_.size(); ++i){
      sum = bigger.num_[i] - carry;
      if(i < smaller.num_.size())
        sum -= smaller.num_[i];
      if (sum < 0){
        digit = 10 + sum;
        carry = 1;
      }
      else{
        digit = sum;
        carry = 0;
      }
      result.num_.push_back(digit);
    }
  }
  while(result.num_.size() > 1 && result.num_.back() == 0)
    result.num_.pop_back();
  if(result.num_.size() == 1 && result.num_[0] == 0)
    result.isNegative_ = false;
  return result;
}

// O(n^2)
bigint bigint::operator*(const bigint& other) const {
  bigint resultmult;
  bigint result;
  int carry = 0;
  int mult;
  for(size_t i = 0; i < num_.size(); ++i){
    carry = 0;
    for(int k = 0; k < i; ++k)
      resultmult.num_.push_back(0);
    for(size_t j = 0; j < other.num_.size(); ++j){
      mult = num_[i] * other.num_[j] + carry;
      carry = mult / 10;
      resultmult.num_.push_back(mult % 10);
    }
    if(carry)
      resultmult.num_.push_back(carry);
    result = result + resultmult;
    resultmult.num_.clear();
  }
  auto isZero = (result.num_.size() == 1) && result.num_[0] == 0;
  result.isNegative_ = (isNegative_ != other.isNegative_) && !isZero;
  return result;
}

// O(n)
bigint bigint::operator/(const bigint& other) const {
  bigint count((long)0);
  bigint result((long) 0);
  if(other == bigint((long)0))
    throw std::domain_error("Error, division by 0");

  bigint thisCopy = *this;
  bigint otherCopy = other;

  thisCopy.isNegative_ = false;
  otherCopy.isNegative_ = false;

  if(thisCopy < otherCopy)
    return result;
  while(result + otherCopy <= thisCopy){
    result = result + otherCopy;
    count = count + bigint("1");
  }
  count.isNegative_ = (isNegative_ != other.isNegative_) && result != bigint((long) 0);
  return count;
}

// O(n)
bigint bigint::operator%(const bigint& other) const {
  bigint division;
  bigint thisCopy = *this;
  bigint otherCopy = other;

  thisCopy.isNegative_ = false;
  otherCopy.isNegative_ = false;

  division = thisCopy / otherCopy;
  bigint remainder = thisCopy - (division * otherCopy);
  remainder.isNegative_ = isNegative_ && remainder != bigint((long) 0);  
  return remainder;


}

