cmake_minimum_required (VERSION 3.2)

set (PLUGIN_NAME "example-simple")

project ("plugin-${PLUGIN_NAME}"
    VERSION 0.0.1
    LANGUAGES CXX)

find_package (ReFramed REQUIRED)
include (ReFramedPlugin)

reframed_add_plugin (plugin-${PLUGIN_NAME}
    SOURCES
        "src/Plugin.cpp")

if (${REFRAMED_plugin-${PLUGIN_NAME}})
    # Do any plugin-specific dependency stuff here
endif ()

