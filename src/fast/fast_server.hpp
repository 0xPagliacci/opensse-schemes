//
// Sophos - Forward Private Searchable Encryption
// Copyright (C) 2016 Raphael Bost
//
// This file is part of Sophos.
//
// Sophos is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// Sophos is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Sophos.  If not, see <http://www.gnu.org/licenses/>.
//

//
// Forward Private Searchable Symmetric Encryption with Optimized I/O Efficiency
//      
//      FAST - by Xiangfu Song
//      bintasong@gmail.com
//

#pragma once

#include "fast_common.hpp"
#include "utils/rocksdb_wrapper.hpp"

#include <string>
#include <array>
#include <fstream>
#include <functional>

#include <sse/crypto/tdp.hpp>
#include <sse/crypto/prf.hpp>

namespace sse {
namespace fast {
        

    class FastServer {
    public:
        
        FastServer(const std::string& db_path);
        FastServer(const std::string& db_path, const size_t tm_setup_size);
        
        std::list<index_type> search(const SearchRequest& req);
        void search_callback(const SearchRequest& req, std::function<void(index_type)> post_callback);

        void update(const UpdateRequest& req);
        
        std::ostream& print_stats(std::ostream& out) const;
    private:
        sse::sophos::RockDBWrapper edb_;
        
    };

} // namespace fast
} // namespace sse
