cmake_minimum_required(VERSION 3.15)
project(LucidCpp
  LANGUAGES CXX
  VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(dependencies)

target_include_directories(main PRIVATE src
                                        src/Data
                                        src/GUI
                                        src/Action
                                        src/Globals
                                        src/IO
)

target_link_libraries(main PRIVATE sfml-window sfml-graphics sfml-system sfml-audio ImGui-SFML::ImGui-SFML)