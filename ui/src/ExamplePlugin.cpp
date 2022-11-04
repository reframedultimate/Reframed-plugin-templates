#include "example-ui/ExamplePlugin.hpp"
#include "example-ui/models/ExampleModel.hpp"
#include "example-ui/views/ExampleView.hpp"

ExamplePlugin::ExamplePlugin(RFPluginFactory* factory)
    : Plugin(factory)
    , model_(new ExampleModel)
{
}

ExamplePlugin::~ExamplePlugin()
{
}

QWidget* ExamplePlugin::createView()
{
    // Create new instance of view. The view registers as a listener to this model
    return new ExampleView(model_.get());
}

void ExamplePlugin::destroyView(QWidget* view)
{
    // ReFramed no longer needs the view, delete it
    delete view;
}
