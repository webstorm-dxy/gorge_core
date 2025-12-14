
#include "lib.h"
#include "objective/annotation.h"
#include "objective/gorge_type.h"
#include <iostream>


int main(int argc, char** argv) {
    // 测试 Annotation 功能
    std::cout << "\nAnnotation Tests:" << "\n";
    
    // 创建一个注解
    Annotation myAnnotation("MyAnnotation", GorgeType::Object("MyType"));
    
    // 测试参数添加和获取
    std::cout << "\nTesting parameters:" << "\n";
    int paramValue = 42;
    bool added = myAnnotation.try_add_parameter("intValue", paramValue);
    std::cout << "Added parameter: " << (added ? "true" : "false") << "\n";
    
    std::any retrievedValue;
    bool found = myAnnotation.try_get_parameter("intValue", retrievedValue);
    std::cout << "Found parameter: " << (found ? "true" : "false") << "\n";
    if (found) {
        int value = std::any_cast<int>(retrievedValue);
        std::cout << "Retrieved value: " << value << "\n";
    }
    
    // 测试元数据添加和获取
    std::cout << "\nTesting metadata:" << "\n";
    Metadata metadata(GorgeType::String,"metadata_name" , "metadataValue");
    bool metadataAdded = myAnnotation.try_add_metadata(metadata);
    std::cout << "Added metadata: " << (metadataAdded ? "true" : "false") << "\n";
    Metadata* metadata_ptr = &metadata;
    auto retrievedMetadata = std::make_unique<Metadata>(metadata);
    bool metadataFound = myAnnotation.try_get_metadata("metadataName", std::move(retrievedMetadata));
    std::cout << "Found metadata: " << (metadataFound ? "true" : "false") << "\n";
    if (metadataFound) {
        std::cout << "Metadata name: " << retrievedMetadata->name << "\n";
        std::cout << "Metadata value: " << std::any_cast<std::string>(retrievedMetadata->value) << "\n";
    }
    
    // 测试元数据值添加
    std::cout << "\nTesting metadata value addition:" << "\n";
    std::string newValue = "new metadata value";
    bool valueAdded = myAnnotation.try_add_metadata_value("metadataName", newValue);
    std::cout << "Added metadata value: " << (valueAdded ? "true" : "false") << "\n";
    
    // 再次获取元数据以验证值是否已更新
    if (metadataFound) {
        std::cout << "Updated metadata value: " << std::any_cast<std::string>(retrievedMetadata->value) << "\n";
    }
    
    return 0;
}