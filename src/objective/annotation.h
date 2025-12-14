//
// Created by daxingyi on 2025/11/11.
//

#pragma once


#include "gorge_type.h"

#include <any>
#include <optional>
#include <string>
#include <unordered_map>

#include "../lib.h"

using OptString = std::optional<std::string>;

class GORGE_API Metadata {
public:
    std::string name;
    std::any value;
    GorgeType type;
    
    // Metadata();
    
    Metadata(GorgeType type, std::string name): name(std::move(name)), type(
                                                    std::move(type)){}
    
    Metadata(GorgeType type, std::string name, std::any value): name(std::move(name)), value(std::move(value)), type(
        std::move(type)){}
};

class GORGE_API Annotation {
private:
    const std::unique_ptr<std::unordered_map<std::string, std::any>> _parameters
        = std::make_unique<std::unordered_map<std::string, std::any>>();

public:
    std::string name;

    GorgeType generic_type;

    std::unique_ptr<std::unordered_map<std::string, Metadata>> metadatas =
        std::make_unique<std::unordered_map<std::string, Metadata>>();

    Annotation(std::string name, GorgeType generic_type);
    
    bool try_add_parameter(const std::string& name, const std::any& value) const;

    bool try_get_parameter(const std::string& name, std::any& value) const;
    
    bool try_add_metadata(const Metadata& metadata) const;
    
    bool try_get_metadata(const std::string& name, Metadata& metadata) const;
    
    bool try_add_metadata_value(const std::string& name, const std::any& value) const;

};