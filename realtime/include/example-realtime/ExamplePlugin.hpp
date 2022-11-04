#pragma once

#include "rfcommon/Plugin.hpp"
#include <memory>

class ExampleModel;

class ExamplePlugin
        : public rfcommon::Plugin
        , public rfcommon::Plugin::UIInterface
        , public rfcommon::Plugin::ReplayInterface
        , public rfcommon::Plugin::RealtimeInterface
{
public:
    ExamplePlugin(RFPluginFactory* factory);
    ~ExamplePlugin();

private:
    /*!
     *  ReFramed calls these to check if a given plugin implements a certain
     * interface. If you do, simply return "this", otherwise you can return nullptr.
     *
     * Plugins may also separate the interfaces into individual objects and return
     * those instead, if it's more convenient.
     */
    Plugin::UIInterface* uiInterface() override { return this; }
    Plugin::ReplayInterface* replayInterface() override { return this; }
    Plugin::VisualizerInterface* visualizerInterface() override { return nullptr; }
    Plugin::RealtimeInterface* realtimeInterface() override { return this; }
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
    // These get called by the main application when connecting/disconnecting
    // to the Nintendo Switch. Typically you don't really need these,
    // but it might be interesting to show the status of the connection somewhere.
    void onProtocolAttemptConnectToServer(const char* ipAddress, uint16_t port) override {}
    void onProtocolFailedToConnectToServer(const char* errormsg, const char* ipAddress, uint16_t port) override {}
    void onProtocolConnectedToServer(const char* ipAddress, uint16_t port) override;
    void onProtocolDisconnectedFromServer() override;

    // These get called when a new game starts/ends, or if a new training mode session starts/ends.
    // In this example, we ignore training mode and only focus on games being started/ended.
    void onProtocolTrainingStarted(rfcommon::Session* session) override {}
    void onProtocolTrainingResumed(rfcommon::Session* session) override {}
    void onProtocolTrainingReset(rfcommon::Session* oldSession, rfcommon::Session* newSession) override {}
    void onProtocolTrainingEnded(rfcommon::Session* session) override {}
    void onProtocolGameStarted(rfcommon::Session* session) override;
    void onProtocolGameResumed(rfcommon::Session* session) override;
    void onProtocolGameEnded(rfcommon::Session* session) override;

private:
    // These get called when ReFramed loads/unloads a replay file
    void onGameSessionLoaded(rfcommon::Session* game) override;
    void onGameSessionUnloaded(rfcommon::Session* game) override;
    void onTrainingSessionLoaded(rfcommon::Session* training) override {}
    void onTrainingSessionUnloaded(rfcommon::Session* training) override {}

    // These get called when ReFramed loads/unloads multiple replay files (multi-selection)
    void onGameSessionSetLoaded(rfcommon::Session** games, int numGames) override;
    void onGameSessionSetUnloaded(rfcommon::Session** games, int numGames) override;

private:
    std::unique_ptr<ExampleModel> model_;
};
