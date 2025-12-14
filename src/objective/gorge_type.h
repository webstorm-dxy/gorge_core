#pragma once

#include "basic_type.h"

#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../lib.h"

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
              OptString namespace_name, bool is_generics, Args&&... args)
        : basic_type(basic_type), class_name(std::move(class_name)),
          namespace_name(std::move(namespace_name)),
          is_generics(is_generics), sub_types{std::forward<Args>(args)...} {
    }

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
                            Args&&... generics_type) {
        return GorgeType(BasicType::Object, class_name, namespace_name, false,
                         std::forward<Args>(generics_type)...);
    }

    static GorgeType Injector(const GorgeType& injected_class);

    static GorgeType Generics(const OptString& class_name);

    static GorgeType Interface(const OptString& interface_name,
                               const OptString& namespace_name = std::nullopt);

    template <typename... Args>
    static GorgeType Delegate(const std::optional<GorgeType>& return_type,
                              Args&&... args) {
        GorgeType sub_type = return_type.or_else([] {
            std::cout << "return_type is null" << "\n";
        });
        return GorgeType(BasicType::Delegate, std::nullopt, std::nullopt, false,
                         sub_type, std::forward<Args>(args)...);
    }

    /**
     * 填充泛型参数类型形成对应的实例类型
     * @tparam Args 泛型参数类型
     * @param types 泛型参数类型
     * @return 泛型实例类型
     */
    template <typename... Args>
    GorgeType create_generics_instance_type(Args&&... types) {
        if (is_generics)
            throw std::exception("不能直接填充泛型类本身");

        std::vector<GorgeType> types_vec{std::forward<Args>(types)...};

        std::vector<GorgeType> sub_types_;

        int j = 0;

        for (int i = 0; i < sub_types.size(); ++i) {
            const GorgeType& sub_type = sub_types.at(i);
            if (sub_type.is_generics) {
                sub_types_.push_back(types_vec.at(j)); // 这里有运行时问题，数组越界了
                j++;
            } else {
                sub_types_.at(i) = sub_types.at(i);
            }
        }

        return GorgeType(basic_type, class_name, namespace_name, false,
                         sub_types_);
    }

    std::string to_string() const;

    /**
     * 获取本类型对应的硬编码代码
     * @return 本类型对应的硬编码代码
     */
    std::string hashcode_type() const;
};