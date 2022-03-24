#include "GreatBin.hpp"


// Constructors

GreatBin::GreatBin(int val)
  :CHUNK_NO_(1), chunks_({val}){}

GreatBin::GreatBin(long val)
  :CHUNK_NO_(2), chunks_({}){
  long base = (long) std::numeric_limits<int>::max() + 1;
  int digit;
  while (val!=0){
    digit = val % base;
    val = val/base;
    chunks_.push_back(digit);
  }
}

GreatBin::GreatBin(std::vector<int> chunks_)
  :CHUNK_NO_(chunks_.size()), chunks_(chunks_){}


// print stuff

void GreatBin::print_chunks(){
  for ( int chunk : this->chunks_ ) {
    std::cout << chunk << "  ";
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
  for (int chunk : this->chunks_) {
    if (chunk == 0) {
      count++;
    } else {
      count = 0;
    }
  }
  // delete the last count entries of chunk_
  if (count!=0){
    std::vector<int>::iterator it1, it2;
    it2 = this->chunks_.end();
    it1 = it2 - count;
    this->chunks_.erase(it1, it2);
  }
}

bool GreatBin::iszero(){
  for ( int chunk : this->chunks_ ) {
    if (chunk != 0) { return false; }
  }
  return true;
}

bool GreatBin::less(GreatBin bin){
  if (this->CHUNK_NO_ < bin.getChunkNo()) { return true; }
  if (this->CHUNK_NO_ > bin.getChunkNo()) { return false; }
  for ( int i=this->CHUNK_NO_-1; i>-1; i--) {
    if (this->chunks_[i] < bin.chunks_[i]){ return true; }
    else if (this->chunks_[i] == bin.chunks_[i]){ continue; }
    else { return false; }
  }
  return false;
}

GreatBin GreatBin::gb_and(GreatBin other){
  // build chunks_ for return, s.t. its length coresponds to the longer operand
  int res_chunk_no {longest_no_of_digits(*this, other)}, this_chunk, other_chunk;
  std::vector <int> res_chunks(res_chunk_no);
  // loop over digits and compare them via &
  for (int i=0; i<res_chunk_no; i++){
    // append if necessary leading zeros
    i>this->CHUNK_NO_ ? this_chunk = 0 : this_chunk = this->chunks_[i];
    i>other.getChunkNo() ? other_chunk = 0 : other_chunk = other.chunks_[i];
    res_chunks[i] = (this_chunk&other_chunk);
  }
  return {res_chunks};
}

GreatBin GreatBin::gb_xor(GreatBin other){
  // build chunks_ for return, s.t. its length coresponds to the longer operand
  int res_chunk_no {longest_no_of_digits(*this, other)}, this_chunk, other_chunk;
  std::vector <int> res_chunks(res_chunk_no);
  // loop over digits and compare them via ^
  for (int i=0; i<res_chunk_no; i++){
    // append if necessary leading zeros
    i>this->CHUNK_NO_ ? this_chunk = 0 : this_chunk = this->chunks_[i];
    i>other.getChunkNo() ? other_chunk = 0 : other_chunk = other.chunks_[i];
    res_chunks[i] = (this_chunk^other_chunk);
  }
  return {res_chunks};
}

GreatBin GreatBin::bitshift(){
  int res_chunk_no {this->getChunkNo()};
  std::vector <int> res_chunks(res_chunk_no);
  bool msb {0}, prev_msb {0};
  int tmp, chunk, min {std::numeric_limits<int>::min()};
  // loop over digits
  for (int i=0; i<this->getChunkNo(); i++){
    chunk = this->chunks_[i];
    tmp = chunk << 1; // bitshift digit
    // if overflow aka sign bit becomes 1
    if (tmp<0){
      msb = 1;
      // sign bit of tmp flippen
      tmp = tmp^min;
    } else {
      msb = 0;
    }
    // if prev digit caused overflow. add one to current digit.
    // This cannot cause overflow, since the last bit is 0, because of the shift
    if (prev_msb) {tmp++;}
    res_chunks[i] = tmp;
    prev_msb = msb;
  }
  if (prev_msb) {res_chunks.push_back((int) 1);}
  return {res_chunks};
}

GreatBin GreatBin::digitshift(int digits){
  std::vector<int> chunks { this->chunks_ };
  for (int i = 0; i < digits; i++) {
    chunks.insert(chunks.begin(),0);
  }
  return chunks;
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

// Uses the usual multiplication algorithm.
GreatBin GreatBin::mul(GreatBin& factor){
  int factor1_chunk_no = this->CHUNK_NO_;
  int factor2_chunk_no = factor.getChunkNo();
  GreatBin res = zero(factor1_chunk_no + factor2_chunk_no);
  long tmp;

  for (int digit1 = 0; digit1 < factor1_chunk_no; digit1++) {
    for (int digit2 = 0; digit2 < factor2_chunk_no; digit2++) {
      tmp = (long) this->chunks_[digit1] * factor.chunks_[digit2];
      GreatBin summand {tmp};
      summand.digitshift(digit1 + digit2);
      res = res.add(summand);
    }
  }
  res.delete_leading_zeros();
  return res;
}

// a naive implementation of integer division
GreatBin GreatBin::div(GreatBin& divisor){
  if (this->equals(divisor)) { return {1}; }
  if (this->less(divisor))   { return {0}; }
  GreatBin remainder {*this};
  GreatBin result {1};
  while (divisor.less(remainder)) {
    result = divisor.mul(result);
    // TODO
  }
  return result;
}


int longest_no_of_digits(GreatBin bin1, GreatBin bin2){
  int bin1_ChunkNo {bin1.getChunkNo()}, bin2_ChunkNo {bin2.getChunkNo()};
  if (bin1_ChunkNo > bin2_ChunkNo) {
    return bin1_ChunkNo;
  } else {
    return bin2_ChunkNo;
  }
}
