#include <string>

using namespace std;

struct ConfigurationManager {
    String config_file;
    ConfigurationManager(string file_path);

    void parse_config_file();
};