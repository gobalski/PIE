#ifndef GREATBIN_HPP
#define GREATBIN_HPP

#include <vector>
#include <limits>
#include <iostream>

struct GreatBin {
  private:
        // TODO Update Chunk number in arithmetic functions!
    int CHUNK_NO_;
  public:
    std::vector<int> chunks_;

    // Constructors:

    // cast int into GreatBin
    GreatBin(int);

    // cast long into GreatBin
    GreatBin(long);

    // Returns a GreatBin built from the digits given in the input vector.
    // @param chunks_ a vector containing integers.
    // @return GreatBin whose digits are the integers of the input vector.
    // Note that the first digit is given by the first entry and so forth.
    // I.e. the digits of a GreatBin are reversed compared to usual numbers.
    GreatBin(std::vector<int>);

    //virtual ~GreatBin();

    // utils:

    /// Tests if this GreatBin has more digits than the other
    /// @param other input GreatBin
    /// @return true if this GreatBin has strictly more digits then other
    inline bool longer(GreatBin other){return this->CHUNK_NO_ > other.getChunkNo();}

    /// Compares the numerical size of two GreatBins
    /// @param input GreatBin
    /// @returns true if this is smaller than the input
    bool less(GreatBin);

    // TODO
    bool equals(GreatBin);

    bool iszero();

    void delete_leading_zeros();

    // Prints the digits of the GreatBin.
    // The order of the digits is reversed compared to traditional numbers.
    // I.e. the first digit is on the left, the last digit on the right.
    void print_chunks();

    // Returns the representation of the GreatBin in decimal base as a string.
    std::string dec_string();


    // arithmetic
    GreatBin add(GreatBin);
    //GreatBin add_overflow(GreatBin);
    GreatBin sub(GreatBin);
    GreatBin mul(GreatBin&);
    std::pair<GreatBin,GreatBin> div(GreatBin&);
    // negates the input. s.t. bin.add(bin.neg()) = 0
    // TODO
    GreatBin neg();
    GreatBin bitshift();
    //GreatBin bitshift_overflow();
    GreatBin digitshift(int);
    GreatBin gb_and(GreatBin);
    GreatBin gb_xor(GreatBin);

    // Getter & Setter
    inline int getChunkNo(){return this->CHUNK_NO_;}
    inline void setChunkNo(int CHUNK_NO_){this->CHUNK_NO_ = CHUNK_NO_;}
};

int longest_no_of_digits(GreatBin, GreatBin);
// TODO
int longest_no_of_digits(std::vector<GreatBin>);

inline GreatBin zero(int N = 1){return std::vector<int>(N,0);}
GreatBin one(int N=1);

#endif // GREATBIN_HPP
