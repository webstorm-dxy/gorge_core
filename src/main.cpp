
#include "lib.h"
#include "objective/gorge_type.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "add(1, 2) = " << add(1, 2) << std::endl;
    
    // 测试基本类型
    std::cout << "Basic Types:" << std::endl;
    std::cout << "Int: " << GorgeType::Int.to_string() << std::endl;
    std::cout << "Float: " << GorgeType::Float.to_string() << std::endl;
    std::cout << "Bool: " << GorgeType::Bool.to_string() << std::endl;
    std::cout << "String: " << GorgeType::String.to_string() << std::endl;
    
    // 测试对象类型
    std::cout << "\nObject Types:" << std::endl;
    auto myClass = GorgeType::Object("MyClass");
    std::cout << "MyClass: " << myClass.to_string() << std::endl;
    
    // 测试枚举类型
    std::cout << "\nEnum Types:" << std::endl;
    auto myEnum = GorgeType::Enum("MyEnum");
    std::cout << "MyEnum: " << myEnum.to_string() << std::endl;
    
    // 测试数组类型
    std::cout << "\nArray Types:" << std::endl;
    std::cout << "IntArray: " << GorgeType::IntArray.to_string() << std::endl;
    std::cout << "StringArray: " << GorgeType::StringArray.to_string() << std::endl;
    
    // 测试带命名空间的类型
    std::cout << "\nNamespaced Types:" << std::endl;
    auto namespacedClass = GorgeType::Object("MyClass", "MyNamespace");
    std::cout << "Namespaced Class: " << namespacedClass.to_string() << std::endl;
    
    // 测试硬编码类型
    std::cout << "\nHardcoded Types:" << std::endl;
    std::cout << "Int hardcoded: " << GorgeType::Int.hashcode_type() << std::endl;
    try {
        std::cout << "IntArray hardcoded: " << GorgeType::IntArray.hashcode_type() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    // 测试相等性比较
    std::cout << "\nEquality Tests:" << std::endl;
    auto anotherInt = GorgeType::Int;
    std::cout << "Int == Int: " << (GorgeType::Int == anotherInt ? "true" : "false") << std::endl;
    std::cout << "Int == Float: " << (GorgeType::Int == GorgeType::Float ? "true" : "false") << std::endl;
    
    return 0;
}