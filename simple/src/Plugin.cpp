#include "example-simple/PluginConfig.hpp"
#include "rfcommon/PluginInterface.hpp"
#include "rfcommon/Plugin.hpp"

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class ExamplePlugin
        : public rfcommon::Plugin
        , public rfcommon::Plugin::UIInterface
{
public:
    ExamplePlugin(RFPluginFactory* factory)
        : Plugin(factory)
    {}

private:
    /*!
     *  ReFramed calls these to check if a given plugin implements a certain
     * interface. If you do, simply return "this", otherwise you can return nullptr.
     *
     * Plugins may also separate the interfaces into individual objects and return
     * those instead, if it's more convenient.
     */
    Plugin::UIInterface* uiInterface() override { return this; }
    Plugin::ReplayInterface* replayInterface() override { return nullptr; }
    Plugin::VisualizerInterface* visualizerInterface() override { return nullptr; }
    Plugin::RealtimeInterface* realtimeInterface() override { return nullptr; }
    Plugin::VideoPlayerInterface* videoPlayerInterface() override { return nullptr; }

private:
    /*!
     * This is called by ReFramed to create an instance of your view.
     * It is possible that this gets called more than once, for example if
     * ReFramed wants to add your view to different parts of the program.
     * Your view should be designed in a way such that multiple views can
     * share the same underlying model.
     */
    QWidget* createView() override
    {
        QLabel* hello = new QLabel("Hello World!");
        hello->setAlignment(Qt::AlignCenter);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(hello);

        QWidget* widget = new QWidget;
        widget->setLayout(layout);

        return widget;
    }

    /*!
     * The counter-part to createView(). When ReFramed removes your view
     * it will give it back to you to destroy.
     */
    void destroyView(QWidget* view) override
    {
        // ReFramed no longer needs the view, delete it
        delete view;
    }
};

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
    {"Example Plugin (Simple)",
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
