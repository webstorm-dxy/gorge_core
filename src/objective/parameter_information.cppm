export module parameter_information;

import std;
import gorge_type;

export class ParameterInformation {
   public:
    int id;
    std::string name;
    GorgeType type;
    int index;

    ParameterInformation(int id, std::string name, const GorgeType& type,
                         int index)
        : id(id), name(std::move(name)), type(type), index(index) {};
};
