#include "gorge_type.h"
#include <string>

template<typename ... Args>
GorgeType::GorgeType(BasicType basic_type, std::string class_name, std::string namespace_name, bool is_generics, Args&& ... args)
    : basic_type(basic_type), class_name(class_name), namespace_name(namespace_name), is_generics(is_generics), sub_types{std::forward<Args>(args)...} {}

void GorgeType::set_full_name(const std::string& name) {
    full_name = name;
}

std::string GorgeType::get_full_name() const {
    if (!namespace_name.empty()) {
        return this->class_name;
    }
    else {
        return this->namespace_name + "." + this->class_name;
    }
    return full_name;
}
