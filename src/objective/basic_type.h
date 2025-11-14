//
// Created by daxingyi on 2025/11/11.
//

#ifndef GORGE_CORE_BASIC_TYPE_H
#define GORGE_CORE_BASIC_TYPE_H
#include "gorge_type.h"


class BasicType {
public:
    BasicType() = default;
    // 这里的写法没有经过验证，可能会出现问题，现在是直接采用的是指针的比较，对一个引用取了指针地址，而实际上这里使用值来比较才是正确的写法，要用到这里的时候再改就行了
    bool operator==(const BasicType & basic_type) const;
};


#endif //GORGE_CORE_BASIC_TYPE_H
