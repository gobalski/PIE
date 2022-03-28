#include "GreatBin.hpp"


// Constructors

GreatBin::GreatBin(int val)
  :DIGIT_NO_(1), digits_({val}){}

GreatBin::GreatBin(long val)
  :DIGIT_NO_(), digits_({}){
  long base = (long) std::numeric_limits<int>::max() + 1;
  int digit;
  while (val!=0){
    digit = val % base;
    val = val/base;
    digits_.push_back(digit);
  }
  DIGIT_NO_ = digits_.size();
}

GreatBin::GreatBin(std::vector<int> digits_)
  :DIGIT_NO_(digits_.size()), digits_(digits_){}


// print stuff

void GreatBin::print_digits(){
  for ( int digit : this->digits_ ) {
    std::cout << digit << "  ";
  }
  std::cout << std::endl;
}

std::string dec_string(){
  return "NOT IMPLEMENTED";
}


// utils

void GreatBin::delete_leading_zeros(){
  int count {0};
  // loop over digits and count zeros. reset count if non-zero is found.
  for (int digit : this->digits_) {
    if (digit == 0) {
      count++;
    } else {
      count = 0;
    }
  }
  // delete the last count entries of digit_
  if (count!=0){
    std::vector<int>::iterator it1, it2;
    it2 = this->digits_.end();
    it1 = it2 - count;
    // don't delete all zeros!
    if (count == this->getDigitNo()) {it2-- ;};
    this->digits_.erase(it1, it2);
  }
  this->setDigitNo(this->digits_.size());
}

bool GreatBin::iszero(){
  for ( int digit : this->digits_ ) {
    if (digit != 0) { return false; }
  }
  return true;
}

bool GreatBin::less(GreatBin bin){
  if (this->DIGIT_NO_ < bin.getDigitNo()) { return true; }
  if (this->DIGIT_NO_ > bin.getDigitNo()) { return false; }
  for ( int i=this->DIGIT_NO_-1; i>-1; i--) {
    if (this->digits_[i] < bin.digits_[i]){ return true; }
    else if (this->digits_[i] == bin.digits_[i]){ continue; }
    else { return false; }
  }
  return false;
}


// arithmetics

GreatBin GreatBin::gb_and(GreatBin other){
  // build digits_ for return, s.t. its length coresponds to the longer operand
  int res_digit_no {longest_no_of_digits(*this, other)}, this_digit, other_digit;
  std::vector <int> res_digits(res_digit_no);
  // loop over digits and compare them via &
  for (int i=0; i<res_digit_no; i++){
    // append if necessary leading zeros
    i>=this->DIGIT_NO_ ? this_digit = 0 : this_digit = this->digits_[i];
    i>=other.getDigitNo() ? other_digit = 0 : other_digit = other.digits_[i];
    res_digits[i] = (this_digit&other_digit);
  }
  return {res_digits};
}

GreatBin GreatBin::gb_xor(GreatBin other){
  // build digits_ for return, s.t. its length coresponds to the longer operand
  int res_digit_no {longest_no_of_digits(*this, other)}, this_digit, other_digit;
  std::vector <int> res_digits(res_digit_no);
  // loop over digits and compare them via ^
  for (int i=0; i<res_digit_no; i++){
    // append if necessary leading zeros
    i>=this->DIGIT_NO_ ? this_digit = 0 : this_digit = this->digits_[i];
    i>=other.getDigitNo() ? other_digit = 0 : other_digit = other.digits_[i];
    res_digits[i] = (this_digit^other_digit);
  }
  return {res_digits};
}

GreatBin GreatBin::bitshift(){
  int res_digit_no {this->getDigitNo()};
  std::vector <int> res_digits(res_digit_no);
  bool msb {0}, prev_msb {0};
  unsigned int tmp, digit;
  int min {std::numeric_limits<int>::min()};
  unsigned int max {std::numeric_limits<int>::max()};
  // loop over digits
  for (int i=0; i<this->getDigitNo(); i++){
    digit = (unsigned int) this->digits_[i];
    tmp = digit << 1; // bitshift digit
    // if overflow aka sign bit becomes 1
    if (tmp > max){
      msb = 1;
      // sign bit of tmp flippen
      tmp = tmp^min;
    } else {
      msb = 0;
    }
    // if prev digit caused overflow. add one to current digit.
    // This cannot cause overflow, since the last bit is 0, because of the shift
    if (prev_msb) {tmp++;}
    res_digits[i] = (int) tmp;
    prev_msb = msb;
  }
  if (prev_msb) {res_digits.push_back((int) 1);}
  return {res_digits};
}

// GreatBin GreatBin::bitshift_overflow(){
//   int res_digit_no {this->getDigitNo()};
//   std::vector <int> res_digits(res_digit_no);
//   bool msb {0}, prev_msb {0};
//   unsigned int tmp, digit;
//   int min {std::numeric_limits<int>::min()};
//   unsigned int max {std::numeric_limits<int>::max()};
//   // loop over digits
//   for (int i=0; i<this->getDigitNo(); i++){
//     digit = (unsigned int) this->digits_[i];
//     // if overflow aka sign bit becomes 1
//     if (tmp > max){
//       msb = 1;
//     } else {
//       msb = 0;
//     }
//     tmp = digit << 1; // bitshift digit
//     // if prev digit caused overflow. add one to current digit.
//     // This cannot cause overflow, since the last bit is 0, because of the shift
//     if (prev_msb) {tmp++;}
//     res_digits[i] = (int) tmp;
//     prev_msb = msb;
//   }
//   return {res_digits};
// }

GreatBin GreatBin::digitshift(int N){
  std::vector<int> digits { this->digits_ };
  for (int i = 0; i < N; i++) {
    digits.insert(digits.begin(),0);
  }
  return digits;
}

// Uses bitwise operations to implement addition.
GreatBin GreatBin::add(GreatBin summand){
  GreatBin res { this->gb_xor(summand) };
  GreatBin carry { this->gb_and(summand) };
  GreatBin tmp {res};
  while( !carry.iszero() ) {
    carry = carry.bitshift();
    res = tmp.gb_xor(carry);
    carry = tmp.gb_and(carry);
    tmp = res;
  }
  return res;
}

GreatBin GreatBin::sub(GreatBin other){
  // crude error. no negative numbers allowed!
  if (this -> less(other)) { return {-1}; }
  int this_digit_no = this->DIGIT_NO_;
  int tmp;
  bool carry {0};
  const int MAX { std::numeric_limits<int>::max() };
  std::vector<int> res;
  for (int i = 0; i < this_digit_no; i++) {
    tmp = this->digits_[i] - other.digits_[i] - carry;
    if (tmp < 0){
      tmp = MAX + tmp;
      carry = 1;
    } else{
      carry = 0;
    }
    res.push_back(tmp);
  }
  GreatBin finished = {res};
  finished.delete_leading_zeros();
  return finished;
}

// GreatBin GreatBin::add_overflow(GreatBin summand){
//   GreatBin res { this->gb_xor(summand) };
//   GreatBin carry { this->gb_and(summand) };
//   // std::cout << "initial carry \n";
//   // carry.print_digits();
//   GreatBin tmp {res};
//   // std::cout << "initial tmp \n";
//   // tmp.print_digits();
//   carry = carry.bitshift_overflow();
//   while( !carry.iszero() ) {
//     res = tmp.gb_xor(carry);
//     carry = tmp.gb_and(carry);
//     tmp = res;
//     carry = carry.bitshift_overflow();
//     // std::cout << "tmp \n";
//     // tmp.print_digits();
//     // std::cout << "carry \n";
//     // carry.print_digits();
//    }
//   return res;
// }

// // negative numbers
// GreatBin GreatBin::neg(){
//   std::vector<int> digits { this->digits_ };
//   for (int i = 0; i < this->getDigitNo(); i++) {
//     digits[i] = ~digits[i];
//   }
//   GreatBin res {digits};
//   res = res.add(one(this->getDigitNo()));
//   return res;
// }

// Uses the usual multiplication algorithm.
GreatBin GreatBin::mul(GreatBin& factor){
  int factor1_digit_no = this->DIGIT_NO_;
  int factor2_digit_no = factor.getDigitNo();
  GreatBin res = zero(factor1_digit_no + factor2_digit_no);
  long tmp;

  for (int digit1 = 0; digit1 < factor1_digit_no; digit1++) {
    for (int digit2 = 0; digit2 < factor2_digit_no; digit2++) {
      tmp = (long) this->digits_[digit1] * factor.digits_[digit2];
      GreatBin summand {tmp};
      summand.digitshift(digit1 + digit2);
      res = res.add(summand);
    }
  }
  res.delete_leading_zeros();
  return res;
}

// a naive implementation of integer division
std::pair<GreatBin,GreatBin> GreatBin::div_naive(GreatBin& divisor){
  // if (this->equals(divisor)) { return {1}; }
  if (this->less(divisor))   { return {zero(), *this}; }
  GreatBin remainder {*this}, result {1}, tmp {0}, remainder_tmp {remainder};
  bool done {false};
  while (!done) {
    tmp = divisor.mul(result);
    remainder_tmp = this->sub(tmp);
    if (remainder_tmp.less(zero())){
      done = true;
    } else {
      remainder = remainder_tmp;
      result = result.add(one());
    }
  }
  return {result.sub(one()), remainder};
}

// division algorithm: https://en.wikipedia.org/wiki/Long_division#Algorithm_for_arbitrary_base
std::pair<GreatBin,GreatBin> GreatBin::div(GreatBin& divisor){
  long base {(long) std::numeric_limits<int>::max() + 1};
  int no_of_digits_N = this->getDigitNo();
  int no_of_digits_D = divisor.getDigitNo();
}

int longest_no_of_digits(GreatBin bin1, GreatBin bin2){
  int bin1_DigitNo {bin1.getDigitNo()}, bin2_DigitNo {bin2.getDigitNo()};
  if (bin1_DigitNo > bin2_DigitNo) {
    return bin1_DigitNo;
  } else {
    return bin2_DigitNo;
  }
}

GreatBin one(int N){
  std::vector<int> digits = { 1 };
  for (int i = 1; i < N; i++) {
    digits.push_back(0);
  }
  return { digits };
}
