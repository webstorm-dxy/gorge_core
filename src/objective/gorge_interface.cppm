//
// Created by 达星屹 on 2025/12/21.
//

export module gorge_interface;

import gorge_type;
import std;

using OptString = std::optional<std::string>;

class GorgeInterface {
public:
    GorgeType type;

    OptString name = type.get_full_name();

    bool is_native;
};
