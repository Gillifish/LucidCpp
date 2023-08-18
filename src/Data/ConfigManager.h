#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct Config
{
    std::string user;
    std::string pin;
    std::string filepath;
    bool setup;
};

class ConfigManager
{
#ifdef __APPLE__
    const std::string m_defaultDir = getenv("HOME");
#elif __linux__
    const std::string defaultPath = "";
#elif _WIN32
    const std::string defaultPath = "";
#endif

    std::string m_filepath = m_defaultDir + "/Lucid";
    Config m_config;

    void loadFromFile();
    void configSetup();

public:
    ConfigManager();

    void saveToFile();
    void setConfig(Config &config);
    Config &getConfig();
};