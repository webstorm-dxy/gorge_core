//
// Created by 达星屹 on 2025/12/18.
//
module;
#include "../lib.h"
#include <cstring>
#include <cstdlib>  // 包含malloc/free
#include <memory>
#include <string>
module ffi;

import gorge_type;
import annotation;
import basic_type;
import std;


extern "C" {
    // 内存管理函数
    GORGE_API void FreeMemory(void* ptr) {
        free(ptr);
    }

    // 基础类型创建函数
    GORGE_API void* CreateBasicType(int basic_type) {
        try {
            BasicType bt = static_cast<BasicType>(basic_type);
            switch(bt) {
                case BasicType::Int:
                    return new GorgeType(GorgeType::Int);
                case BasicType::Float:
                    return new GorgeType(GorgeType::Float);
                case BasicType::Bool:
                    return new GorgeType(GorgeType::Bool);
                case BasicType::String:
                    return new GorgeType(GorgeType::String);
                default:
                    return nullptr;
            }
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API void* CreateGorgeType(int basic_type, const char* class_name, const char* namespace_name, bool is_generics) {
        try {
            BasicType bt = static_cast<BasicType>(basic_type);
            std::optional<std::string> opt_class_name = class_name ? std::optional<std::string>(class_name) : std::nullopt;
            std::optional<std::string> opt_namespace_name = namespace_name ? std::optional<std::string>(namespace_name) : std::nullopt;

            return new GorgeType(bt, opt_class_name, opt_namespace_name, is_generics);
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API void DeleteGorgeType(void* type_ptr) {
        if (type_ptr) {
            delete static_cast<GorgeType*>(type_ptr);
        }
    }

    // 类型信息获取函数
    GORGE_API int GetBasicType(void* type_ptr) {
        if (!type_ptr) return -1;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            return static_cast<int>(type->basic_type);
        } catch(...) {
            return -1;
        }
    }

    GORGE_API char* GetClassName(void* type_ptr) {
        if (!type_ptr) return nullptr;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            if (type->class_name.has_value()) {
                const std::string& str = type->class_name.value();
                char* result = static_cast<char*>(malloc(str.length() + 1));
                strcpy(result, str.c_str());
                return result;
            }
            return nullptr;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API char* GetNamespaceName(void* type_ptr) {
        if (!type_ptr) return nullptr;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            if (type->namespace_name.has_value()) {
                const std::string& str = type->namespace_name.value();
                char* result = static_cast<char*>(malloc(str.length() + 1));
                strcpy(result, str.c_str());
                return result;
            }
            return nullptr;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API char* GetFullName(void* type_ptr) {
        if (!type_ptr) return nullptr;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            auto full_name = type->get_full_name();
            if (full_name.has_value()) {
                const std::string& str = full_name.value();
                char* result = static_cast<char*>(malloc(str.length() + 1));
                strcpy(result, str.c_str());
                return result;
            }
            return nullptr;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API bool IsGenerics(void* type_ptr) {
        if (!type_ptr) return false;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            return type->is_generics;
        } catch(...) {
            return false;
        }
    }

    // 类型操作函数
    GORGE_API char* TypeToString(void* type_ptr) {
        if (!type_ptr) return nullptr;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            std::string str = type->to_string();
            char* result = static_cast<char*>(malloc(str.length() + 1));
            strcpy(result, str.c_str());
            return result;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API size_t GetHashCode(void* type_ptr) {
        if (!type_ptr) return 0;
        try {
            GorgeType* type = static_cast<GorgeType*>(type_ptr);
            return type->get_hash_code();
        } catch(...) {
            return 0;
        }
    }

    // 工厂函数
    GORGE_API void* CreateEnumType(const char* enum_name, const char* namespace_name) {
        try {
            std::optional<std::string> opt_enum_name = enum_name ? std::optional<std::string>(enum_name) : std::nullopt;
            std::optional<std::string> opt_namespace_name = namespace_name ? std::optional<std::string>(namespace_name) : std::nullopt;

            GorgeType* result = new GorgeType(GorgeType::Enum(opt_enum_name, opt_namespace_name));
            return result;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API void* CreateObjectType(const char* class_name, const char* namespace_name) {
        try {
            std::optional<std::string> opt_class_name = class_name ? std::optional<std::string>(class_name) : std::nullopt;
            std::optional<std::string> opt_namespace_name = namespace_name ? std::optional<std::string>(namespace_name) : std::nullopt;

            GorgeType* result = new GorgeType(GorgeType::Object(opt_class_name, opt_namespace_name));
            return result;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API void* CreateInterfaceType(const char* interface_name, const char* namespace_name) {
        try {
            std::optional<std::string> opt_interface_name = interface_name ? std::optional<std::string>(interface_name) : std::nullopt;
            std::optional<std::string> opt_namespace_name = namespace_name ? std::optional<std::string>(namespace_name) : std::nullopt;

            GorgeType* result = new GorgeType(GorgeType::Interface(opt_interface_name, opt_namespace_name));
            return result;
        } catch(...) {
            return nullptr;
        }
    }

    // 注解相关函数
    GORGE_API void* CreateAnnotation(const char* name, void* generic_type_ptr) {
        try {
            if (!name || !generic_type_ptr) return nullptr;

            GorgeType* generic_type = static_cast<GorgeType*>(generic_type_ptr);
            Annotation* annotation = new Annotation(std::string(name), *generic_type);
            return annotation;
        } catch(...) {
            return nullptr;
        }
    }

    GORGE_API void DeleteAnnotation(void* annotation_ptr) {
        if (annotation_ptr) {
            delete static_cast<Annotation*>(annotation_ptr);
        }
    }

    // 测试函数
    GORGE_API int Add(int a, int b) {
        return a + b;
    }
}
