#pragma once

#include "basic_type.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

#ifdef GORGE_CORE_CPP_EXPORTS
    #define GORGE_API __declspec(dllexport)
#else
    #define GORGE_API __declspec(dllimport)
#endif

using OptString = std::optional<std::string>;

class GORGE_API GorgeType {
private:
    OptString full_name;

public:
    // 类基础类型
    BasicType basic_type;
    // 类名
    // TODO:未来可能替换为复合的namespace结构
    OptString class_name;
    OptString namespace_name;
    // 本类是否为泛型函数
    bool is_generics;
    // 子类型
    // 如果是ObjectiveArray类型，则0号位为内容的类型
    // 如果是Injector，则0号位为对应的类型
    // 其他情况可考虑存储泛型类型
    // 有可能把Injector纳入泛型？
    std::vector<GorgeType> sub_types;

    template <typename... Args>
    GorgeType(BasicType basic_type, OptString class_name,
              OptString namespace_name, bool is_generics, Args&&... args);

    /**
     * 这里对应C#版本的Getter和Setter
     */
    OptString get_full_name() const;

    /**
     * 判断目标类是不是本类的泛型参数类
     * 也就是判断子类型长度是否相等，而不要求子类型严格相等
     * @param other 目标类
     * @return 是否是泛型参数类
     */
    bool is_generics_instance(const std::unique_ptr<GorgeType>& other) const;

    /**
     * 判断两个类的等价性
     * @param other 目标类
     * @return 对比
     */
    bool operator==(const GorgeType& other) const;

    /**
     * 获取类的哈希码
     * @return 获取的哈希码
     */
    std::size_t get_hash_code() const;

    static const GorgeType Int;
    static const GorgeType Float;
    static const GorgeType Bool;
    static const GorgeType String;
    static const GorgeType IntArray;
    static const GorgeType FloatArray;
    static const GorgeType BoolArray;
    static const GorgeType StringArray;
    static const GorgeType ObjectArray;
    static const GorgeType IntList;
    static const GorgeType FloatList;
    static const GorgeType BoolList;
    static const GorgeType StringList;
    static const GorgeType ObjectList;


    // 使用驼峰命名，因为如果在这里使用蛇形命名法，enum会和关键字冲突
    static GorgeType Enum(const OptString& enum_name,
                          const OptString& namespace_name = std::nullopt);

    template <typename... Args>
    static GorgeType Object(const OptString& class_name,
                            const OptString& namespace_name = std::nullopt,
                            Args&&... generics_type);

    static GorgeType Injector(const GorgeType& injected_class);

    static GorgeType Generics(const OptString& class_name);

    static GorgeType Interface(const OptString& interface_name,
                               const OptString& namespace_name = std::nullopt);

    template <typename... Args>
    static GorgeType Delegate(const std::optional<GorgeType>& return_type,
                              Args&&... args);

    /**
     * 填充泛型参数类型形成对应的实例类型
     * @tparam Args 泛型参数类型
     * @param types 泛型参数类型
     * @return 泛型实例类型
     */
    template <typename... Args>
    GorgeType create_generics_instance_type(Args&&... types);

    std::string to_string() const;
    
    /**
     * 获取本类型对应的硬编码代码
     * @return 本类型对应的硬编码代码
     */
    std::string hashcode_type();
};