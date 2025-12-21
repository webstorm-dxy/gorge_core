#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>  // 包含size_t定义

#if defined(_WIN32)
#   define __export         __declspec(dllexport)
#elif defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3))
#   define __export         __attribute__((visibility("default")))
#else
#   define __export
#endif



__export int add(int a, int b);

#ifdef __cplusplus
}
#endif

// 当在windows上运行时定义WINDOWS宏，主要用于编译DLL时使用

#ifdef WINDOWS
#ifdef GORGE_CORE_CPP_EXPORTS
#define GORGE_API __declspec(dllexport)
#else
#define GORGE_API __declspec(dllimport)
#endif
#else
#define GORGE_API
#endif

// FFI函数声明
#ifdef __cplusplus
extern "C" {
#endif

// 内存管理函数
GORGE_API void FreeMemory(void* ptr);

// 基础类型创建函数
GORGE_API void* CreateBasicType(int basic_type);
GORGE_API void* CreateGorgeType(int basic_type, const char* class_name, const char* namespace_name, bool is_generics);
GORGE_API void DeleteGorgeType(void* type_ptr);

// 类型信息获取函数
GORGE_API int GetBasicType(void* type_ptr);
GORGE_API char* GetClassName(void* type_ptr);
GORGE_API char* GetNamespaceName(void* type_ptr);
GORGE_API char* GetFullName(void* type_ptr);
GORGE_API bool IsGenerics(void* type_ptr);

// 类型操作函数
GORGE_API char* TypeToString(void* type_ptr);
GORGE_API size_t GetHashCode(void* type_ptr);

// 工厂函数
GORGE_API void* CreateEnumType(const char* enum_name, const char* namespace_name);
GORGE_API void* CreateObjectType(const char* class_name, const char* namespace_name);
GORGE_API void* CreateInterfaceType(const char* interface_name, const char* namespace_name);

// 注解相关函数
GORGE_API void* CreateAnnotation(const char* name, void* generic_type_ptr);
GORGE_API void DeleteAnnotation(void* annotation_ptr);

// 测试函数
GORGE_API int Add(int a, int b);

#ifdef __cplusplus
}
#endif

