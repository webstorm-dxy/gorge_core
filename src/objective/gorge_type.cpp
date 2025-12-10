#include "gorge_type.h"

#include <functional>
#include <string>
#include <utility>
#include <boost/functional/hash.hpp>

template<typename... Args>
GorgeType::GorgeType(const BasicType basic_type, OptString class_name, OptString namespace_name,
                     const bool is_generics, Args &&... args)
    : basic_type(basic_type), class_name(std::move(class_name)), namespace_name(std::move(namespace_name)),
      is_generics(is_generics), sub_types{std::forward<Args>(args)...} {
}

OptString GorgeType::get_full_name() const {
    if (namespace_name.has_value()) {
        return this->class_name;
    } else {
        return this->namespace_name.value() + "." + this->class_name.value();
    }
    return std::nullopt;
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

std::size_t GorgeType::get_hash_code() const {
    std::size_t seed = 0;

    boost::hash_combine(seed, static_cast<int>(this->basic_type));
    boost::hash_combine(seed, this->class_name);
    boost::hash_combine(seed, this->namespace_name);

    return seed;
}

const GorgeType GorgeType::Int(BasicType::Int,std::nullopt,std::nullopt,false);
const GorgeType GorgeType::Float(BasicType::Float,std::nullopt,std::nullopt,false);
const GorgeType GorgeType::Bool(BasicType::Bool,std::nullopt,std::nullopt,false);
const GorgeType GorgeType::String(BasicType::String,std::nullopt,std::nullopt,false);
GorgeType GorgeType::Enum(const OptString& enum_name,const OptString& namespace_name) {
    return GorgeType(BasicType::Enum,enum_name, namespace_name, false);
}
template <typename... Args>
GorgeType GorgeType::Object(const OptString& class_name,
                            const OptString& namespace_name,
                            Args&&... generics_type) {
    return GorgeType(BasicType::Object,class_name,namespace_name,false,std::forward<Args>(generics_type)...);
}
//TODO:处理这下面的
// const GorgeType GorgeType::IntArray(BasicType::Int,std::nullopt,std::nullopt,true);
