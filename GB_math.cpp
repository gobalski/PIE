#include "GreatBin.hpp"
#include "GB_math.hpp"

GreatBin GB_math::fac ( GreatBin& n ){
    GreatBin res {1}, i {2};
    for (i= GreatBin::one() ; i.less(n); i = i.add(GreatBin::one())) {
        res = res.mul(i);
        // std::cout << res << " res " << i << " i \n";
    }
    return res.mul(i);
}

GreatBinExp GB_math::reziproc (GreatBin& d, int prec){
    // assuming d > 1
    GreatBin n = GreatBin::one();
    int exponent = -d.getDigitNo();
    n = n.digitshift( -exponent );
    std::pair<GreatBin,GreatBin> div {n.div(d)};
    GreatBin res {div.first}, remainder {div.second};

    for (int i = 2; i <= prec; i++) {
        n = remainder;
        while(!remainder.less(n)){
            n = n.digitshift(1);
            res = res.digitshift(1);
            exponent--;
        }
        div = n.div(d);
        res = res.add(div.first);
        remainder = div.second;
        if (remainder.iszero()) {return {res, exponent};}
    }

    return {res, exponent};
}
