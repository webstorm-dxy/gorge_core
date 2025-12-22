//
// Created by 达星屹 on 2025/12/21.
//

export module gorge_class_declaration;

import gorge_type;
import std;

using OptString = std::optional<std::string>;

class ClassDeclaration {
public:
    // TODO 是否需要有ID？不管用不用，感觉应当有
    // TODO 这个ID应该是链接时确定的，如果没有链接，那就要保持带namespace的完整名字作为类索引


    GorgeType type;

     /**
      * 类名
      */
    OptString name = type.get_full_name();
     /**
     * 超类
     */
    std::unique_ptr<ClassDeclaration> super_class;


};