#pragma once

#include "basic_type.h"
#include <any>
#include <memory>
#include <string>
#include <vector>

class GorgeType {
private:
    std::string full_name;
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
    /**
     * 这里对应C#版本的Getter和Setter
     */
    std::string get_full_name() const ;
    /**
     * 判断目标类是不是本类的泛型参数类
     * 也就是判断子类型长度是否相等，而不要求子类型严格相等
     * TODO: 换成智能指针，保证内存安全
     * @param other 目标类
     * @return 是否是泛型参数类
     */
    bool is_generics_instance(GorgeType* other) const;

    // TODO：需要改动，考虑subtype
    /**
     * TODO：换用智能的指针保证内存安全
     * @param other 目标类
     * @return 对比
     */
    bool equals(GorgeType* other) const;

    // TODO：论证这里是否可以使用重载运算符实现，因为对于C++来说，这里直接采用函数的方式比较有点不现实
    bool equals(std::any other) const;


};
