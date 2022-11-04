#include "example-ui/PluginConfig.hpp"
#include "example-ui/ExamplePlugin.hpp"
#include "rfcommon/PluginInterface.hpp"

// Gets called when the main application wants to create your plugin
static rfcommon::Plugin* createExamplePlugin(
        RFPluginFactory* factory,
        rfcommon::VisualizerContext* visCtx,
        rfcommon::Log* log,
        rfcommon::UserMotionLabels* userLabels,
        rfcommon::Hash40Strings* hash40Strings)

{
    return new ExamplePlugin(factory);
}

// Gets called when the main application removes your plugin from its
// list. You have to delete the object here.
static void destroyExamplePlugin(rfcommon::Plugin* model)
{
    delete model;
}

// OR together all of the interfaces this plugin implements here. This is used
// by ReFramed to sort your plugin into the proper locations
static RFPluginType examplePluginType =
        RFPluginType::UI;

// This is a list of create/destroy functions which the main application uses
// to instantiate your plugins. You can have multiple plugins in a single
// shared libary, but in this case we only have one.
static RFPluginFactory factories[] = {
    {createExamplePlugin, destroyExamplePlugin, examplePluginType,
    {"Example Plugin (UI)",
     "misc > misc",  // category > sub-category
     "Author Name",  // your name
     "Author#5387, @Author, author@author.com",  // various contact details
     "This is an example plugin, doesn't do much!"}},

    {0}  // List must be terminated with a NULL or bad things happen!
};

static int start(uint32_t version, const char** error)
{
    // Gets called right after shared library is loaded. Initialize global state
    // here
    //
    // Version of ReFramed gets passed in here. Return 0 if you're compatible,
    // any other number (-1) if otherwise. If you return non-zero, write an
    // error message to *error so the main application can tell the user what
    // went wrong.
    return 0;
}

static void stop()
{
    // Gets called before the shared libary is unloaded. Clean up global state here.
}

DEFINE_PLUGIN(factories, start, stop)
