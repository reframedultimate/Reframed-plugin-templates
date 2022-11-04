#pragma once

#include "rfcommon/Plugin.hpp"
#include <memory>

class ExampleModel;

class ExamplePlugin
        : public rfcommon::Plugin
        , public rfcommon::Plugin::UIInterface
{
public:
    ExamplePlugin(RFPluginFactory* factory);
    ~ExamplePlugin();

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
    QWidget* createView() override;

    /*!
     * The counter-part to createView(). When ReFramed removes your view
     * it will give it back to you to destroy.
     */
    void destroyView(QWidget* view) override;

private:
    std::unique_ptr<ExampleModel> model_;
};
