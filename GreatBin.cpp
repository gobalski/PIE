#include<vector>
#include<limits>
#include<iostream>

struct GreatBin {
  private:
    int CHUNK_NO_;
  public:
    std::vector<int> chunks_;
    GreatBin(int CHUNK_NO);
    GreatBin(int CHUNK_NO, int val);
    GreatBin(long val);
    GreatBin(std::vector<int> chunks_);

    //virtual ~GreatBin();

    // utils:
    bool longer(GreatBin bin){return this->CHUNK_NO_ > bin.getChunkNo();}
    bool less(GreatBin bin);
    bool equals(GreatBin bin);
    bool iszero();
    void print_chunks();
    void delete_leading_zeros();

    // arithmetic
    GreatBin add(GreatBin summand);
    GreatBin mul(GreatBin& factor);
    GreatBin bitshift();
    GreatBin digitshift(int N);
    GreatBin gb_and(GreatBin operand);
    GreatBin gb_xor(GreatBin operand);

    // Getter & Setter
    int getChunkNo(){return this->CHUNK_NO_;}
};



// initialize GreatBin with zero
GreatBin::GreatBin(int val)
  :CHUNK_NO_(1), chunks_({val}){}

GreatBin::GreatBin(int N, int val)
  :CHUNK_NO_(N), chunks_({}){
  for (int i = 0; i < N; i++) {
    chunks_.push_back(val);
  }
}

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
  :CHUNK_NO_(), chunks_(chunks_){
  CHUNK_NO_ = chunks_.size();
}

void GreatBin::print_chunks(){
  for ( int chunk : this->chunks_ ) {
    std::cout << chunk << "  ";
  }
  std::cout << std::endl;
}

void GreatBin::delete_leading_zeros(){
  int count {0};
  for (int chunk : this->chunks_) {
    if (chunk == 0) {
      count++;
    } else {
      count = 0;
    }
  }
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

GreatBin GreatBin::gb_and(GreatBin operand){
  int res_chunk_no;
  this->longer(operand) ? res_chunk_no = this->CHUNK_NO_: res_chunk_no = operand.getChunkNo();
  std::vector <int> res_chunks(res_chunk_no);
  int this_chunk, other_chunk;
  for (int i=0; i<res_chunk_no; i++){
    i>this->CHUNK_NO_ ? this_chunk = 0 : this_chunk = this->chunks_[i];
    i>operand.getChunkNo() ? other_chunk = 0 : other_chunk = operand.chunks_[i];
    res_chunks[i] = (this_chunk&other_chunk);
  }
  return {res_chunks};
}

GreatBin GreatBin::gb_xor(GreatBin operand){
  int res_chunk_no;
  this->longer(operand) ? res_chunk_no = this->CHUNK_NO_: res_chunk_no = operand.getChunkNo();
  std::vector <int> res_chunks(res_chunk_no);
  int this_chunk, other_chunk;
  for (int i=0; i<res_chunk_no; i++){
    i>this->CHUNK_NO_ ? this_chunk = 0 : this_chunk = this->chunks_[i];
    i>operand.getChunkNo() ? other_chunk = 0 : other_chunk = operand.chunks_[i];
    res_chunks[i] = (this_chunk^other_chunk);
  }
  return {res_chunks};
}

GreatBin GreatBin::bitshift(){
  int res_chunk_no {this->getChunkNo()};
  std::vector <int> res_chunks(res_chunk_no);
  bool msb {0}, prev_msb {0};
  int tmp, chunk, min {std::numeric_limits<int>::min()};
  for (int i=0; i<this->getChunkNo(); i++){
    chunk = this->chunks_[i];
    tmp = chunk << 1;
    if (tmp<0){
      msb = 1;
      // sign bit of tmp flippen
      tmp = tmp^min;
    } else {
      msb = 0;
    }
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

GreatBin GreatBin::mul(GreatBin& factor){
  int factor1_chunk_no = this->CHUNK_NO_;
  int factor2_chunk_no = factor.getChunkNo();
  GreatBin res {factor1_chunk_no + factor2_chunk_no, 0};
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
