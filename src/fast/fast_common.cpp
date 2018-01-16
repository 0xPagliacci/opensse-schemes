//
//  sophos_common.cpp
//  SSE_Schemes
//
//  Created by Raphael Bost on 04/10/2017.
//  Copyright © 2017 Raphael Bost. All rights reserved.
//

#include "fast_common.hpp"


#include <sse/crypto/prf.hpp>

#include <cstring>

namespace sse {
    namespace fast {
        
        void gen_update_token_masks(const std::string &deriv_key,
                                    const std::string search_token,
                                    update_token_type &update_token,
                                    std::array<uint8_t, kUpdateTokenSize> &mask)
        {
            auto derivation_prf = crypto::Prf<kUpdateTokenSize>(deriv_key);
           
            update_token = derivation_prf.prf_string(search_token + '0').erase(kUpdateTokenSize);
                        
            mask = derivation_prf.prf(search_token + '1');
        }
        
    }
}
