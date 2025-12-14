#ifdef __cplusplus
extern "C" {
#endif

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
