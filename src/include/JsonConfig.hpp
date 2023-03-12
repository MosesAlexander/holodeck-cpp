#ifndef JSONCONFIG_HEADERFILE_H
#define JSONCONFIG_HEADERFILE_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

enum class object_type {
    Cube,
    LightCube,
    Floor,
    Wall,
    None
};

struct JsonConfig {
    json mData;
    JsonConfig(string filepath);
    object_type get_object_type();
};

#endif