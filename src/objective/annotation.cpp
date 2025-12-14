//
// Created by daxingyi on 2025/11/11.
//

#include "annotation.h"

Annotation::Annotation(std::string name,
                       GorgeType generic_type)
    : name(std::move(name)), generic_type(std::move(generic_type)) {
}

bool Annotation::try_add_parameter(const std::string& name,
                                   const std::any& value) const {
    const auto [_, result] = _parameters->insert({name, value});
    return result;
}

bool Annotation::try_get_parameter(const std::string& name,
                                   std::any& value) const {
    if (const auto it = _parameters->find(name); it != _parameters->end()) {
        value = it->second;
        return true;
    }
    return false;
}

bool Annotation::try_add_metadata(const Metadata& metadata) const {
    const auto [_, result] = metadatas->insert({metadata.name, metadata});
    return result;
}

bool Annotation::try_get_metadata(const std::string& name,
                                  std::unique_ptr<Metadata> metadata) const {
    if (const auto it = _parameters->find(name); it != _parameters->end()) {
        *metadata = std::any_cast<Metadata>(it->second);
        return true;
    }
    return false;
}

bool Annotation::try_add_metadata_value(const std::string& name,
                                        const std::any& value) const {
    //TODO：修复这里的运行时问题
    std::unique_ptr<Metadata> metadata;
    if (try_get_metadata(name, std::move(metadata))) {
         metadata->value = value;
         return true;
    }
    return false;
}
