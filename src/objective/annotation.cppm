//
// Created by 达星屹 on 2025/12/18.
//
module;
#include "../lib.h"
export module annotation;

import std;
import gorge_type;
import basic_type;

using OptString = std::optional<std::string>;

export class GORGE_API Metadata {
public:
    std::string name;
    std::any value;
    GorgeType type;

    Metadata(GorgeType type, std::string name): name(std::move(name)), type(
                                                    std::move(type)){}

    Metadata(GorgeType type, std::string name, std::any value): name(std::move(name)), value(std::move(value)), type(
        std::move(type)){}
};

export class GORGE_API Annotation {
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

    bool try_get_metadata(const std::string& name,
                          std::unique_ptr<Metadata> metadata) const;

    bool try_add_metadata_value(const std::string& name, const std::any& value) const;

};