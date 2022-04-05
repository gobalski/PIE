#include "GB_math.hpp"
#include "GreatBinExp.hpp"

GreatBin GB_math::fac (GreatBin& n ){
    GreatBin res {1}, i {2}, ONE {GreatBin::one()};
    for (i= GreatBin::one() ; i.less(n); i = i.add(ONE)) {
        res = res.mul(i);
        // std::cout << res << " res " << i << " i \n";
    }
    return res.mul(i);
}

GreatBin GB_math::fac (int n){
    GreatBin res {1};
    int i;
    for (i = 1; i<n ; i++) {
        res = res.mul(i);
    }
    return res.mul(i);
}

GreatBinExp GB_math::reziproc (const GreatBin& d, int prec){
    // assuming d > 1
    GreatBin n = GreatBin::one();
    int exponent = -d.getDigitNo();
    n = n.digitshift( -exponent );
    std::pair<GreatBin,GreatBin> div {n.div(d)};
    GreatBin res {div.first}, remainder {div.second};

    for (int i = 2; i < prec; i++) {
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

GreatBinExp GB_math::E (int precision){
    GreatBinExp E { 2,0 }, summand { 0,0 };
    GreatBin fac { 1 };
    int i {2}, curr_prec {-1};

    while (curr_prec > -precision){
        fac = fac.mul(i);
        summand = GB_math::reziproc(fac, precision);
        E = E.add(summand);
        i++;
        curr_prec = summand.getExponent() + summand.getMantisse().getDigitNo();
        std::cout << "\r current precision : " << -curr_prec;
        std::cout << " | current term : " << i << std::flush;
    }

    std::cout << "\n" ;
    E.setExponent(-precision);
    return E;
}

GreatBinExp GB_math::PI (int precision){
    GreatBinExp PI { 1, 0 }, summand { 0, 0 }, nom { 1, 0 };
    GreatBinExp i { 1, 0 }, ONE { 1, 0 }, TWO { 2, 0 };
    GreatBin den { 3 };
    int curr_prec { -1 }, int_i { 1 };

    while (curr_prec > -precision){
        summand = GB_math::reziproc(den, precision).mul(nom);
        PI = PI.add(summand);
        int_i++;
        i = int_i;
        nom = nom.mul(i);
        den = den.mul(i.mul(TWO).add(ONE).getMantisse());
        curr_prec = summand.getExponent() + summand.getMantisse().getDigitNo();
        // std::cout << "\n";
        // odd.print_digits(std::cout) << " odd \n";
        // summand.print_digits(std::cout) << " summand \n";
        std::cout << "\r current precision : " << -curr_prec;
        std::cout << " | current term : " << int_i << std::flush;
    }

    std::cout << "\n" ;

    PI = PI.mul(TWO);
    PI.setExponent(-precision);
    return PI;
}
