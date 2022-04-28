#ifndef GREATBINEXP_HPP
#define GREATBINEXP_HPP

#include "GreatBin.hpp"

struct GreatBinExp{
  protected:
    int exponent_;
    GreatBin mantisse_;
  public:

    // constructor
    GreatBinExp(GreatBin, int);
    inline GreatBinExp(int n): exponent_(0), mantisse_(n){} ;

    bool less(GreatBinExp&);
    bool equals(GreatBinExp&);
    inline bool iszero(GreatBinExp&) { return mantisse_.iszero(); }
    GreatBinExp digitshift(int);

    // checks which of the two exponents is smaller
    // and sets the other to the smaller exponent through sideeffect!
    void equalizeExponents(GreatBinExp*);


    // arithmetic
    GreatBinExp add(GreatBinExp&);
    GreatBinExp sub(GreatBinExp&);
    GreatBinExp mul(GreatBinExp&);
    std::pair<GreatBinExp, GreatBinExp> div(GreatBinExp&);

    // Returns the decimal representation as a pair of vectors.
    // the first represents the digits greater 1
    // the second represents the digits smaller 1
    std::pair<std::vector<short>, std::vector<short>> dec_vector(int);
    // Returns the representation of the GreatBin in decimal base as a string.
    std::string dec_string();
    inline std::ostream& print(std::ostream& os) {return os << dec_string();}
    // prints digits and exponent in base 2^31
    std::ostream& print_digits(std::ostream& os);

    // Getter & Setter
    inline int getExponent(){return this->exponent_;}
    void setExponent(int e);
    inline GreatBin getMantisse(){return this->mantisse_;}
    inline void setMantisse(GreatBin m){this->mantisse_ = m;}
};

inline std::ostream& operator<<(std::ostream& os, GreatBinExp& b) {return b.print(os);}

#endif
