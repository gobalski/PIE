#ifndef GREATBIN_HPP
#define GREATBIN_HPP

#include <string>
#include <vector>
#include <limits>
#include <iostream>

struct GreatBin {
  protected:
    int DIGIT_NO_;
    // helper function for the division algorithm
    GreatBin find_beta(const GreatBin&,const GreatBin&, GreatBin*) const;
  public:
    std::vector<int> digits_;

    // Constructors:

    // cast int into GreatBin
    GreatBin(int);

    // cast long into GreatBin
    GreatBin(long);

    // Returns a GreatBin built from the digits given in the input vector.
    // @param digits_ a vector containing integers.
    // @return GreatBin whose digits are the integers of the input vector.
    // Note that the first digit is given by the first entry and so forth.
    // I.e. the digits of a GreatBin are reversed compared to usual numbers.
    GreatBin(std::vector<int>);

    //virtual ~GreatBin();

    // utils:

    /// Tests if this GreatBin has more digits than the other
    /// @param other input GreatBin
    /// @return true if this GreatBin has strictly more digits then other
    inline bool longer(GreatBin other){return this->DIGIT_NO_ > other.getDigitNo();}

    /// Compares the numerical size of two GreatBins
    /// @param input GreatBin
    /// @returns true if this is smaller than the input
    bool less(const GreatBin&) const;

    // TODO
    bool equals(GreatBin&);

    bool iszero();

    void delete_leading_zeros();

    // Prints the digits of the GreatBin.
    void print_digits();
    std::ostream& print_digits(std::ostream&);

    inline std::ostream& print(std::ostream& os) {return os << dec_string();}

    // Returns the representation of the GreatBin in decimal base as a string.
    std::string dec_string();

    // Returns the decade representation as a vector
    std::vector<short> dec_vector();


    // arithmetic
    GreatBin add(const GreatBin&);
    //GreatBin add_overflow(GreatBin);
    GreatBin sub(const GreatBin&) const;
    GreatBin mul(const GreatBin&) const;
    std::pair<GreatBin,GreatBin> div_naive(GreatBin&);
    std::pair<GreatBin,GreatBin> div (const GreatBin&) const;
    // negates the input. s.t. bin.add(bin.neg()) = 0
    // GreatBin neg();
    GreatBin bitshift();
    //GreatBin bitshift_overflow();
    GreatBin digitshift(int);
    GreatBin strip(int);
    GreatBin gb_and(const GreatBin&);
    GreatBin gb_xor(const GreatBin&);

    // Getter & Setter
    inline int getDigitNo() const {return this->DIGIT_NO_;}
    inline void setDigitNo(int DIGIT_NO_){this->DIGIT_NO_ = DIGIT_NO_;}

    // statics
    static inline GreatBin zero(int N = 1){return std::vector<int>(N,0);}
    static GreatBin one(int N=1);
    static int longest_no_of_digits(const GreatBin&,const GreatBin&);
};


inline std::ostream& operator<<(std::ostream& os, GreatBin& b) {return b.print(os);}


#endif // GREATBIN_HPP
