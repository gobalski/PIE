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
  for (auto rit = this->digits_.rbegin() ; rit != this->digits_.rend(); ++rit) {
    std::cout << *rit << " ";
  }
  // for ( int digit : this->digits_ ) {
  //   std::cout << digit << "  ";
  // }
  std::cout << std::endl;
}

std::ostream& GreatBin::print_digits(std::ostream& os) {
  std::string str {""};
  for (auto rit = this->digits_.rbegin() ; rit != this->digits_.rend(); ++rit) {
    str += std::to_string(*rit) + " ";
  }
  return os << str;
}

std::vector<short> GreatBin::dec_vector(){
  GreatBin TEN {10};
  std::pair<GreatBin, GreatBin> division_res {this->div(TEN)};
  std::vector<short> dec_digits {(short) division_res.second.digits_[0]};
  while (!division_res.first.iszero()){
    division_res = division_res.first.div(TEN);
    dec_digits.insert(dec_digits.begin(), (short) division_res.second.digits_[0]);
  }
  return dec_digits;
}

std::string GreatBin::dec_string(){
  std::vector<short> dec_digits {this->dec_vector()};
  std::string str {""};
  for (short digit : dec_digits) {
    str += std::to_string(digit);
  }
  return str;
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

bool GreatBin::less(const GreatBin& bin) const{
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

GreatBin GreatBin::gb_and(const GreatBin& other){
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

GreatBin GreatBin::gb_xor(const GreatBin& other){
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

GreatBin GreatBin::strip(int N){
  std::vector<int> digits {};
  for ( int i = 0; i<this->getDigitNo() - N; i++ ){
    digits.push_back(this->digits_.at(i));
  }
  return { digits };
}

// Uses bitwise operations to implement addition.
GreatBin GreatBin::add(const GreatBin& summand){
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

GreatBin GreatBin::sub(const GreatBin& other) const{
  // crude error. no negative numbers allowed!
  if (this -> less(other)) { return {-1}; }
  int this_digit_no {this->DIGIT_NO_}, tmp, other_digit;
  bool carry {0};
  const int MAX { std::numeric_limits<int>::max() };
  std::vector<int> res;
  for (int i = 0; i < this_digit_no; i++) {
    if (other.getDigitNo() > i) {
      other_digit = other.digits_[i];
    } else {
      other_digit = 0;
    }
    tmp = this->digits_[i] - other_digit - carry;
    if (tmp < 0){
      tmp = tmp + MAX + 1;
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
GreatBin GreatBin::mul(const GreatBin& factor) const {
  int factor1_digit_no = this->DIGIT_NO_;
  int factor2_digit_no = factor.getDigitNo();
  GreatBin res = zero(factor1_digit_no + factor2_digit_no);
  long tmp;

  // std::cout << "mul DEBUG \n";
  // std::cout << "f1 digit_no: " << factor1_digit_no << "  f2 digit_no: " << factor2_digit_no << "\n";

  for (int digit1 = 0; digit1 < factor1_digit_no; digit1++) {
    for (int digit2 = 0; digit2 < factor2_digit_no; digit2++) {
      tmp = (long) this->digits_[digit1] * factor.digits_[digit2];
      GreatBin summand {tmp};
      summand = summand.digitshift(digit1 + digit2);
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
  GreatBin ZERO {zero()}, ONE {one()};
  bool done {false};
  while (!done) {
    remainder_tmp = remainder_tmp.sub(divisor);
    if (remainder_tmp.less(ZERO)){
      done = true;
    } else {
      remainder = remainder_tmp;
      result = result.add(ONE);
    }
  }
  return {result.sub(ONE), remainder};
}

GreatBin GreatBin::find_beta(const GreatBin& d, const GreatBin& m, GreatBin* r) const {
  std::string flag {"to_small"};
  int beta_int {0}, inc {std::numeric_limits<int>::max() >> 1};
  GreatBin beta {beta_int}, ZERO {zero()};
  while (flag!="done"){
    GreatBin m_x_beta = m.mul(beta);
    *r = d.sub(m_x_beta);
    if (r->less(ZERO)) {
      // decrease increment if r(beta) >= m in the previous step
      if (flag=="to_small"){
        inc = inc >> 1;
        flag = "to_big";
      }
      beta_int -= inc;
    } else if (!(r->less(m))) {
      // decrease increment if r(beta) < 0 in the previous step
      if (flag=="to_big"){
        inc = inc >> 1;
        flag = "to_small";
      }
      beta_int += inc;
    } else {
      flag = "done";
      return beta;
    }
    beta.digits_[0] = beta_int;
  }
  // error return
  return {-1};
}

// division algorithm: https://en.wikipedia.org/wiki/Long_division#Algorithm_for_arbitrary_base
std::pair<GreatBin,GreatBin> GreatBin::div(const GreatBin& divisor) const {
  GreatBin base {(long) std::numeric_limits<int>::max() + 1}, ZERO {zero()};
  int digits_no_N {this->getDigitNo()}, digits_no_D {divisor.getDigitNo()};
  GreatBin d {0};
  std::vector<int> r_digits { this->digits_ };
  r_digits.erase(r_digits.begin(), r_digits.begin() + digits_no_N - digits_no_D + 1);
  GreatBin q {0},r { r_digits };

  if (r.digits_.size() == 0) { r.digits_.push_back(0); }

  // std::cout << "div DEBUG \n";
  // std::cout << "N no_digits: " << digits_no_N << " D no_digits: " << digits_no_D << "\n";
  // std::cout << "r: \n";
  // r.print_digits();

  for (int i = 0; i <= digits_no_N - digits_no_D ; i++) {

    // std::cout << "i: " << i << "\n";

    GreatBin alpha { this->digits_.at(digits_no_N - 1 - (i+digits_no_D-1)) };

    // std::cout << "alpha:\n";
    // alpha.print_digits();

    d = (base.mul(r)).add(alpha);

    // std::cout << "d:\n";
    // d.print_digits();

    GreatBin beta {find_beta(d, divisor, &r)};

    // std::cout << "r: \n";
    // r.print_digits();
    // std::cout << "beta: \n";
    // beta.print_digits();

    if (beta.less(ZERO)) { std::cerr << "div: find_beta() went wrong!" << std::endl; }

    q = base.mul(q).add(beta);

    // std::cout << "q: \n";
    // q.print_digits();
  }
  return std::pair<GreatBin, GreatBin> {q, r};
}

int GreatBin::longest_no_of_digits(const GreatBin& bin1,const GreatBin& bin2){
  int bin1_DigitNo {bin1.getDigitNo()}, bin2_DigitNo {bin2.getDigitNo()};
  if (bin1_DigitNo > bin2_DigitNo) {
    return bin1_DigitNo;
  } else {
    return bin2_DigitNo;
  }
}

GreatBin GreatBin::one(int N){
  std::vector<int> digits = { 1 };
  for (int i = 1; i < N; i++) {
    digits.push_back(0);
  }
  return { digits };
}
