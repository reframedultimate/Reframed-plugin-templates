#include "example-realtime/ExamplePlugin.hpp"
#include "example-realtime/models/ExampleModel.hpp"
#include "example-realtime/views/ExampleView.hpp"
#include "rfcommon/RunningGameSession.hpp"

ExamplePlugin::ExamplePlugin(RFPluginFactory* factory)
    : RealtimePlugin(factory)
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

void ExamplePlugin::onProtocolMatchStarted(rfcommon::RunningGameSession* session)
{
    // A match just started. We pass the session object to the model so it can
    // process the frame data and listen to new session events
    model_->setSession(session);
}

void ExamplePlugin::onProtocolMatchResumed(rfcommon::RunningGameSession* session)
{
    // We re-connected to the server mid-match, which means the session
    // object contains frame data, but the match is not over yet. In this case,
    // we wrote our code in a way where it doesn't distinguish between a match
    // starting and a match resuming, so we can call the same method as in MatchStarted().
    model_->setSession(session);
}

void ExamplePlugin::onProtocolMatchEnded(rfcommon::RunningGameSession* session)
{
    // A match just ended. We tell the model to release any references to the
    // session
    model_->clearSession(session);
}
