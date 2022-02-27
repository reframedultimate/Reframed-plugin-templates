#include "myplugin/PluginConfig.hpp"
#include "myplugin/models/ExampleModel.hpp"
#include "rfcommon/PluginInterface.hpp"

// Gets called when the main application is about to create your view.
// The model is created first, and the view is created by calling model->createView().
static rfcommon::Plugin* createExampleModel(RFPluginFactory* factory)
{
    return new ExampleModel(factory);
}

// Gets called when the main application removes your model from its
// list. You have to delete the object here.
static void destroyExampleModel(rfcommon::Plugin* model)
{
    delete model;
}

// This is a list of create/destroy functions which the main application uses
// to instantiate your objects. You can have multiple "plugins" in a single
// shared libary, but in this case we only have one.
static RFPluginFactory factories[] = {
    {createExampleModel, destroyExampleModel, RFPluginType::STANDALONE,
    {"Example Plugin (Standalone)",
     "misc > misc",  // category > sub-category
     "Author Name",  // your name
     "Author#5387, @Author, author@author.com",  // various contact details
     "This is an example plugin, doesn't do much!"}},

    {0}
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

