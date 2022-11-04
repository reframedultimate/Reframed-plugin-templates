#include "example-realtime/ExamplePlugin.hpp"
#include "example-realtime/models/ExampleModel.hpp"
#include "example-realtime/views/ExampleView.hpp"
#include "rfcommon/Session.hpp"

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

void ExamplePlugin::onProtocolConnectedToServer(const char* ipAddress, uint16_t port)
{
    model_->setConnectedState(true);
}

void ExamplePlugin::onProtocolDisconnectedFromServer()
{
    model_->setConnectedState(false);
}

void ExamplePlugin::onProtocolGameStarted(rfcommon::Session* session)
{
    // A game just started. We pass the session object to the model so it can
    // process the frame data and listen to new session events
    model_->clearSession();
    model_->setSession(session);
}

void ExamplePlugin::onProtocolGameResumed(rfcommon::Session* session)
{
    // We re-connected to the server mid-match, which means the session
    // object contains frame data, but the game is not over yet. In this case,
    // we wrote our code in a way where it doesn't distinguish between a game
    // starting and a game resuming, so we can call the same method as in onProtocolGameStarted().
    model_->clearSession();
    model_->setSession(session);
}

void ExamplePlugin::onProtocolGameEnded(rfcommon::Session* session)
{
    // A game just ended. We don't call model_->clearSession() so that the data
    // is still visible until the next game starts.
}

void ExamplePlugin::onGameSessionLoaded(rfcommon::Session* game)
{
    model_->clearSession();
    model_->setSession(game);
}

void ExamplePlugin::onGameSessionUnloaded(rfcommon::Session* game)
{
    model_->clearSession();
}

void ExamplePlugin::onGameSessionSetLoaded(rfcommon::Session** games, int numGames)
{
    model_->clearSession();
}

void ExamplePlugin::onGameSessionSetUnloaded(rfcommon::Session** games, int numGames)
{
}
