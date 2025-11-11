#pragma once

#include "basic_type.h"
#include <string>
#include <vector>

class GorgeType {
public:
    // 类基础类型
    BasicType basic_type;
    // 类名
    // TODO:未来可能替换为复合的namespace结构
    std::string class_name;
    std::string namespace_name;
    // 本类是否为泛型函数
    bool is_generics;
    // 子类型
    // 如果是ObjectiveArray类型，则0号位为内容的类型
    // 如果是Injector，则0号位为对应的类型
    // 其他情况可考虑存储泛型类型
    // 有可能把Injector纳入泛型？
    std::vector<GorgeType> sub_types;
    
    template<typename ... Args>
    GorgeType(
        BasicType basic_type, 
        std::string class_name, 
        std::string namespace_name, 
        bool is_generics, 
        Args&& ... args
    );
    /*
     * 这里对应C#版本的Getter和Setter
     */
    std::string full_name;
    std::string get_full_name() const;
    void set_full_name(const std::string& name);
    
    bool is_generics_instance(const GorgeType& other) const;
};
