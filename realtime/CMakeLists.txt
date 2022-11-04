cmake_minimum_required (VERSION 3.2)

set (PLUGIN_NAME "example-realtime")

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
		"src/ExamplePlugin.cpp"
        "src/Plugin.cpp"
	HEADERS
		"include/${PLUGIN_NAME}/models/ExampleModel.hpp"
		"include/${PLUGIN_NAME}/views/ExampleView.hpp"
		"include/${PLUGIN_NAME}/ExamplePlugin.hpp"
    INCLUDE_DIRECTORIES
        "include"
    MOC_HEADERS
        "include/${PLUGIN_NAME}/views/ExampleView.hpp")

if (${REFRAMED_plugin-${PLUGIN_NAME}})
    # Do any plugin-specific dependency stuff here
endif ()

