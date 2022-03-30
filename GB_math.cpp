#include "GreatBin.hpp"

namespace GB_Math{

    GreatBin fac ( GreatBin n ){
        GreatBin res {1}, i {2};
        for (i=one() ; i.less(n); i = i.add(one())) {
            res = res.mul(i);
            // std::cout << res << " res " << i << " i \n";
        }
        return res.mul(i);
    }

}
