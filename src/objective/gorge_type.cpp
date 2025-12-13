#include "gorge_type.h"

#include <functional>
#include <iostream>
#include <string>
#include <utility>
#include <boost/functional/hash.hpp>


OptString GorgeType::get_full_name() const {
    if (!namespace_name.has_value()) {
        return this->class_name;
    } else if (class_name.has_value()) {
        return this->namespace_name.value() + "." + this->class_name.value();
    }
    return std::nullopt;
}

bool GorgeType::is_generics_instance(
    const std::unique_ptr<GorgeType>& other) const {
    if (other == nullptr)
        return false;
    if (other.get() == this)
        return true;

    return this->basic_type == other->basic_type
           && this->class_name == other->class_name
           && this->namespace_name == other->namespace_name
           && this->sub_types.size() == other->sub_types.size();
}

bool GorgeType::operator==(const GorgeType& other) const {
    // if (&other == nullptr) return false; //在C++中对引用进行空检查没有必要，因为引用不能为空
    if (&other == this)
        return true;
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

const GorgeType GorgeType::Int(BasicType::Int, std::nullopt, std::nullopt,
                               false);
const GorgeType GorgeType::Float(BasicType::Float, std::nullopt, std::nullopt,
                                 false);
const GorgeType GorgeType::Bool(BasicType::Bool, std::nullopt, std::nullopt,
                                false);
const GorgeType GorgeType::String(BasicType::String, std::nullopt, std::nullopt,
                                  false);
const GorgeType GorgeType::IntArray = Object("IntArray", "Gorge");

const GorgeType GorgeType::FloatArray = Object("FloatArray", "Gorge");;

const GorgeType GorgeType::BoolArray = Object("BoolArray", "Gorge");

const GorgeType GorgeType::StringArray = Object("StringArray", "Gorge");

const GorgeType GorgeType::ObjectArray(BasicType::Object, "ObjectArray",
                                       "Gorge", false); //???

const GorgeType GorgeType::IntList = Object("IntList", "Gorge");

const GorgeType GorgeType::FloatList = Object("FloatList", "Gorge");

const GorgeType GorgeType::BoolList = Object("BoolList", "Gorge");

const GorgeType GorgeType::StringList = Object("StringList", "Gorge");

const GorgeType GorgeType::ObjectList(BasicType::Object, "ObjectList", "Gorge",
                                      false);

GorgeType GorgeType::Enum(const OptString& enum_name,
                          const OptString& namespace_name) {
    return GorgeType(BasicType::Enum, enum_name, namespace_name, false);
}

GorgeType GorgeType::Injector(const GorgeType& injected_class) {
    return GorgeType(BasicType::Object, "Injector", "Gorge", false,
                     injected_class);
}

GorgeType GorgeType::Generics(const OptString& class_name) {
    return GorgeType(BasicType::Object, class_name, std::nullopt, true);
}

GorgeType GorgeType::Interface(const OptString& interface_name,
                               const OptString& namespace_name) {
    return GorgeType(BasicType::Interface, interface_name, namespace_name,
                     false);
}

std::string GorgeType::to_string() const {
    std::string namespace_part = namespace_name.has_value()
                                     ? (namespace_name.value() + ".")
                                     : "";

    switch (basic_type) {
    case BasicType::Int:
        return "int";
    case BasicType::Float:
        return "float";
    case BasicType::Bool:
        return "bool";
    case BasicType::String:
        return "string";
    case BasicType::Object: {
        std::string full_name_ = class_name.has_value()
                                     ? class_name.value()
                                     : "";
        if (sub_types.empty()) {
            return namespace_part + full_name_;
        } else {
            std::string sub_types_str = "";
            for (int i = 0; i < sub_types.size(); ++i) {
                if (i > 0)
                    sub_types_str += ",";
                sub_types_str += sub_types.at(i).to_string();
            }
            return namespace_part + full_name_ + "(" + sub_types_str + ")";
        }
    }
    case BasicType::Interface:
        return namespace_part + (class_name.has_value()
                                     ? class_name.value()
                                     : "") + "(Interface)";
    case BasicType::Delegate: {
        if (sub_types.empty()) {
            return namespace_part + "delegate:Void()";
        }

        std::string return_type_str = sub_types.at(0).to_string();
        std::string params_str = "";

        for (int i = 0; i < sub_types.size(); ++i) {
            if (i > 1)
                params_str += ",";
            params_str += sub_types.at(i).to_string();
        }
        return namespace_part + "delegate:" + return_type_str + "(" + params_str
               + ")";
    }
    default:
        throw std::runtime_error("未知类型");

    }
}

std::string GorgeType::hashcode_type() {
    switch (basic_type) {
    case BasicType::Int:
        return "int";

    case BasicType::Float:
        return "float";

    case BasicType::Bool:
        return "bool";

    case BasicType::Enum:
        return get_full_name().value_or("");

    case BasicType::String:
        return "string";

    case BasicType::Object: {
        std::string full_name_ = get_full_name().value_or("");

        if (full_name_ == "Gorge.Injector" && !sub_types.empty()) {
            return sub_types[0].get_full_name().value_or("") + "^";
        } else if (full_name_ == "Gorge.IntArray") {
            return "int[]";
        } else if (full_name_ == "Gorge.StringArray") {
            return "string[]";
        } else if (full_name_ == "Gorge.ObjectArray" && !sub_types.empty()) {
            return sub_types[0].get_full_name().value_or("") + "[]";
        } else {
            return full_name_;
        }
    }

    case BasicType::Interface:
        return get_full_name().value_or("");

    case BasicType::Delegate:
        throw std::runtime_error("类型" + to_string() + "暂不支持生成硬编码代码");

    default:
        throw std::runtime_error("类型" + to_string() + "无法生成硬编码代码");
    }
}


//TODO:处理这下面的
// const GorgeType GorgeType::IntArray(BasicType::Int,std::nullopt,std::nullopt,true);