#include "GreatBinExp.hpp"
#include <cstdlib>
#include <string>
#include <vector>

GreatBinExp::GreatBinExp(GreatBin m, int e): exponent_(e), mantisse_(m) {
// TODO so schreiben, dass zb 1 0 0 0 E -3 in 1 E0 gewandelt wird.
    int i { 0 };
    for (i=0; i<mantisse_.getDigitNo(); i++) {
        if (mantisse_.digits_.at(i) != 0) { break; }
    }
    if (i!=0) {
        auto it = mantisse_.digits_.begin();
        mantisse_.digits_.erase(it, it + i);
        mantisse_.setDigitNo(mantisse_.digits_.size());
        exponent_ = e + i;
    }
}

bool GreatBinExp::less(GreatBinExp & other){
    if (this->getExponent() < other.getExponent()) { return true; }
    else if (this->getExponent() == other.getExponent()) {
        GreatBin otherM = other.getMantisse();
        return this->getMantisse().less(otherM);
    }
    else { return false; }
}

bool GreatBinExp::equals(GreatBinExp & other){
   return false;
}

GreatBinExp GreatBinExp::digitshift(int N){
    if (N<0) { std::cerr << "digitshift: negative shift not allowed.. " << std::endl; }
    GreatBin m { this->getMantisse().digitshift(N) };
    int e { this->getExponent() - N };
    return { m, e };
}

void GreatBinExp::equalizeExponents(GreatBinExp * other){
    if (this->exponent_ > other->exponent_) {
        this->setExponent(other->exponent_);
    } else if (this->exponent_ < other->exponent_) {
        other->setExponent(this->exponent_);
    }
}

GreatBinExp GreatBinExp::add(GreatBinExp& other){
    this->equalizeExponents(&other);
    GreatBin this_m {this->getMantisse()}, other_m {other.getMantisse()};
    return {this_m.add(other_m), this->getExponent()};
}

GreatBinExp GreatBinExp::sub(GreatBinExp& other){
    this->equalizeExponents(&other);
    GreatBin this_m {this->getMantisse()}, other_m {other.getMantisse()};
    return {this_m.sub(other_m), this->getExponent()};
}

GreatBinExp GreatBinExp::mul(GreatBinExp& other){
    this->equalizeExponents(&other);
    GreatBin this_m {this->getMantisse()}, other_m {other.getMantisse()};
    return {this_m.mul(other_m), this->getExponent() + other.getExponent()};
}

std::pair<GreatBinExp, GreatBinExp> GreatBinExp::div(GreatBinExp& other){
    this->equalizeExponents(&other);
    GreatBin this_m {this->getMantisse()}, other_m {other.getMantisse()};
    std::pair<GreatBin, GreatBin> div { this_m.div(other_m) };
    int e {this->getExponent() - other.getExponent()};
    GreatBinExp res {div.first, e}, remainder {div.second, e};
    return { res, remainder };
}

std::pair<std::vector<short>, std::vector<short>> GreatBinExp::dec_vector(int dec_prec){
    int e {this->getExponent()};
    GreatBin m {this->getMantisse()}, TEN {10};
    std::vector<short> fraction {};
    std::vector<short> whole { 0 };
    if ( e>=0 ) {
        this->setExponent(0);
        whole = m.dec_vector();
    } else {
        GreatBin tmp {m};
        // strip of whole part
        if (abs(e) < m.getDigitNo()) {
            std::vector<int> whole_digits;
            // copy whole part
            for (int i = 0; i < tmp.getDigitNo() - abs(e); i++) {
                int size {tmp.getDigitNo()};
                whole_digits.push_back( tmp.digits_.at(size - i - 1) );
            }
            GreatBin whole_part {whole_digits};
            whole = whole_part.dec_vector();
            // delete whole part
            tmp = tmp.strip(tmp.getDigitNo() - abs(e));
        }
        // calculate fraction part
        short digit {};
        int no_dec_digits {0};
        while (no_dec_digits < dec_prec){
            tmp = tmp.mul(TEN);
            // if there is a new digit.
            if (tmp.getDigitNo() == abs(e) + 1 ) {
                // copy new digit
                digit = (short) tmp.digits_.back();
                // delete new digit from tmp
                tmp = tmp.strip(1);
            } else {
                digit = 0;
            }
            fraction.push_back( digit );
            no_dec_digits++; // count the number of decimal digits
        }
    }
    return {whole, fraction};
}

std::string GreatBinExp::dec_string(){
    int precision { 10*(this->getMantisse().getDigitNo()) }; // senseful precision for *this.DIGIT_NO_
    auto euler_dec = this->dec_vector(precision);
    std::string str {""};
    for ( short digit : euler_dec.first ){
        str += std::to_string(digit);
    }
    str += ".";
    for ( short digit : euler_dec.second ){
        str += std::to_string(digit);
    }
    return str;
}

std::ostream& GreatBinExp::print_digits(std::ostream& os){
    return this->mantisse_.print_digits(os) << "  E" << this->getExponent();
}


void GreatBinExp::setExponent(int e){
    // cut least significant digits: DATA LOSS!!!
    if (e>exponent_) {
        int shift { e - exponent_ };
        auto i = mantisse_.digits_.begin();
        mantisse_.digits_.erase(i, i + shift);
        mantisse_.setDigitNo(mantisse_.digits_.size());
        exponent_ = e;
    // add zeros to mantisse no data loss
    } else {
        int shift { exponent_ - e };
        mantisse_ = mantisse_.digitshift(shift);
        exponent_ = e;
    }
}
