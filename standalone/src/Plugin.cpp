#include "myplugin/PluginConfig.hpp"
#include "myplugin/models/ExampleModel.hpp"
#include "rfcommon/PluginInterface.hpp"

static rfcommon::Plugin* createExampleModel(RFPluginFactory* factory)
{
    return new ExampleModel(factory);
}
static void destroyExampleModel(rfcommon::Plugin* model)
{
    delete model;
}

static RFPluginFactory factories[] = {
    {createExampleModel, destroyExampleModel, RFPluginType::STANDALONE,
    {"Example Plugin",
     "misc > misc",  // category > sub-category
     "Author Name",  // your name
     "Author#5387, @Author, author@author.com",  // various contact details
     "This is an example plugin, doesn't do much!"}},

    {0}
};

static int start(uint32_t version)
{
    // Version of ReFramed gets passed in here. Return 0 if you're compatible, 
    // any other number (-1) if otherwise.
    return 0;
}

static void stop()
{
}

DEFINE_PLUGIN(factories, start, stop)

