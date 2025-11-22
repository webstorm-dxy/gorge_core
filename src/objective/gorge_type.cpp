#include "gorge_type.h"

#include <functional>
#include <string>
#include <utility>

template<typename... Args>
GorgeType::GorgeType(const BasicType basic_type, std::string class_name, std::string namespace_name,
                     const bool is_generics, Args &&... args)
    : basic_type(basic_type), class_name(std::move(class_name)), namespace_name(std::move(namespace_name)),
      is_generics(is_generics), sub_types{std::forward<Args>(args)...} {}

std::string GorgeType::get_full_name() const {
    if (!namespace_name.empty()) {
        return this->class_name;
    } else {
        return this->namespace_name + "." + this->class_name;
    }
    return full_name;
}

bool GorgeType::is_generics_instance(const std::unique_ptr<GorgeType> &other) const {
    if (other == nullptr) return false;
    if (other.get() == this) return true;

    return this->basic_type == other->basic_type
           && this->class_name == other->class_name
           && this->namespace_name == other->namespace_name
           && this->sub_types.size() == other->sub_types.size();
}

bool GorgeType::operator==(const GorgeType &other) const {
    // if (&other == nullptr) return false; //在C++中对引用进行空检查没有必要，因为引用不能为空
    if (&other == this) return true;
    bool sub_types_is_equals = false;
    if (this->sub_types.size() == other.sub_types.size()) {
        sub_types_is_equals = true;
        for (int i = 0; i < this->sub_types.size(); i++) {
            if (this->sub_types[i] != other.sub_types[i]) {
                sub_types_is_equals = false;
                break;
            }
        }
    } else {
        sub_types_is_equals = false;
    }

    return this->basic_type == other.basic_type
           && this->class_name == other.class_name
           && this->namespace_name == other.namespace_name
           && sub_types_is_equals;
}
