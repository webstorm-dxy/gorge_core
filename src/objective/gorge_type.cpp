#include "gorge_type.h"

#include <functional>
#include <string>

template<typename ... Args>
GorgeType::GorgeType(BasicType basic_type, std::string class_name, std::string namespace_name, bool is_generics, Args&& ... args)
    : basic_type(basic_type), class_name(class_name), namespace_name(namespace_name), is_generics(is_generics), sub_types{std::forward<Args>(args)...} {}

std::string GorgeType::get_full_name() const {
    if (!namespace_name.empty()) {
        return this->class_name;
    }
    else {
        return this->namespace_name + "." + this->class_name;
    }
    return full_name;
}

bool GorgeType::is_generics_instance(GorgeType* other) const {
    if (other == nullptr) return false;
    if (other == this) return true;

    return this->basic_type == other->basic_type
        && this->class_name == other->class_name
        && this->namespace_name == other->namespace_name
        && this->sub_types.size() == other->sub_types.size();
}

bool GorgeType::equals(GorgeType *other) const {
    if (other == nullptr) return false;
    if (other == this) return true;

    return this->basic_type == other->basic_type
        && this->class_name == other->class_name
        && this->namespace_name == other->namespace_name
        && &this->sub_types == &other->sub_types; //TODO: 目前这里仅比较指针，需要改成比较内容，这种写法是错误的
}

