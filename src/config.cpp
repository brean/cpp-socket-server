#include "../include/config.h"

void Config::load(const char* filename, const char* appname) {
    YAML::Node config = YAML::LoadFile(filename);
    for (YAML::iterator it = config[appname].begin(); it != config[appname].end(); ++it) {
        std::string key = it->first.as<std::string>();
        YAML::Node value = it->second;
        if (key == "port") {
            this->port = it->second.as<int>();
        } else if (key == "host") {
            this->host = it->second.as<std::string>();
        }
    }
};
