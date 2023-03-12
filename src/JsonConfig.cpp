#include "JsonConfig.hpp"
#include <filesystem>
#include "Cube.hpp"

JsonConfig::JsonConfig(string filepath) {
    std::ifstream f(filepath);
    mData = json::parse(f);
}


object_type JsonConfig::get_object_type() {
    if (mData["object_type"] == "Cube") {
        return object_type::Cube;
    }
    if (mData["object_type"] == "LightCube") {
        return object_type::LightCube;
    }
    if (mData["object_type"] == "Wall") {
        return object_type::Wall;
    }
    if (mData["object_type"] == "Floor") {
        return object_type::Floor;
    }

    return object_type::None;
}