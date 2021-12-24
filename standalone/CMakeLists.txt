cmake_minimum_required (VERSION 3.2)

set (PLUGIN_NAME "myplugin")

project ("plugin-${PLUGIN_NAME}"
    VERSION 0.0.1
    LANGUAGES CXX)

find_package (ReFramed REQUIRED)
include (ReFramedPlugin)

reframed_add_plugin (plugin-${PLUGIN_NAME}
    FORMS
        "forms/ExampleView.ui"
    SOURCES
        "src/models/ExampleModel.cpp"
        "src/views/ExampleView.cpp"
        "src/Plugin.cpp"
    INCLUDE_DIRECTORIES
        "include"
    MOC_HEADERS
        "include/${PLUGIN_NAME}/views/ExampleView.hpp")

if (${REFRAMED_plugin-${PLUGIN_NAME}})
endif ()

