#include "example-realtime/models/ExampleModel.hpp"
#include "example-realtime/listeners/ExampleListener.hpp"
#include "rfcommon/Frame.hpp"
#include "rfcommon/FrameData.hpp"
#include "rfcommon/MappingInfo.hpp"
#include "rfcommon/MetaData.hpp"
#include "rfcommon/Session.hpp"

void ExampleModel::setConnectedState(bool connected)
{
    isConnected_ = connected;
    dispatcher.dispatch(&ExampleListener::onConnectionStateChanged);
}

void ExampleModel::setSession(rfcommon::Session* session)
{
    assert(session_.isNull());

    // Checks to see if the session has all of the data we need
    auto fdata = session->tryGetFrameData();  // need frame data
    auto mdata = session->tryGetMetaData();   // need meta data
    auto map = session->tryGetMappingInfo();  // need mapping info
    if (fdata == nullptr || mdata == nullptr || map == nullptr)
        return;
    // Note that if the first call to any of the tryXX() functions succeeds,
    // then every subsequent call will also succeed.

    // We only care about 1v1
    if (fdata->fighterCount() != 2)
        return;

    // hold reference to the session object (increments refcount)
    session_ = session;

    // Reset our counters
    for (int i = 0; i != 2; ++i)
    {
        totalDamage_[i] = 0.0;
        earliestKill_[i] = 999.0;
    }

    // It's possible that the session object already contains frame data,
    // which happens if the session was loaded from a file, or if the plugin
    // was loaded while a session was running. We need to go through each
    // frame and update our model accordingly
    for (int p = 0; p != fdata->fighterCount(); ++p)
        for (int f = 0; f != fdata->frameCount(); ++f)
        {
            updateTotalDamage(p, f);
            udpateEarliestKill(p, f);
        }
    notifyStatsUpdated();

    // We want to be notified of any new frame data that gets added to the
    // session in the future
    fdata->dispatcher.addListener(this);
}

void ExampleModel::clearSession()
{
    if (session_.isNull())
        return;

    // Stop listening to events
    session_->tryGetFrameData()->dispatcher.removeListener(this);

    // Release our reference to the session. This decrements the refcount.
    session_.drop();
}

void ExampleModel::updateTotalDamage(int playerIdx, int stateIdx)
{
    auto fdata = session_->tryGetFrameData();
    const auto& state = fdata->stateAt(playerIdx, stateIdx);
    const auto& prevState = stateIdx > 0 ? fdata->stateAt(playerIdx, stateIdx - 1) : state;

    // Accumulate the damage of the other player according to how much the
    // damage increased. NOTE: We want to skip doing this if the player
    // just died, otherwise we end up subtracting all of the damage back to 0%
    // again
    //
    // Also note: This isn't entirely accurate, because it attributes self
    // inflicted damage to the other player. Maybe there's a smarter way to do this.
    float diff = state.damage() - prevState.damage();
    if (diff > 0)
        totalDamage_[1 - playerIdx] += diff;
}

void ExampleModel::udpateEarliestKill(int playerIdx, int stateIdx)
{
    auto fdata = session_->tryGetFrameData();
    auto mdata = session_->tryGetMetaData();
    auto map = session_->tryGetMappingInfo();
    const auto& state = fdata->stateAt(playerIdx, stateIdx);

    // Did a player die?
    const auto fighterID = mdata->fighterID(playerIdx);
    const char* enumName = map->status.toName(fighterID, state.status(), nullptr);
    if (enumName != nullptr && strcmp(enumName, "FIGHTER_STATUS_KIND_DEAD") == 0)
    {
        // The other player gets the credit
        if (earliestKill_[1 - playerIdx] > state.damage())
            earliestKill_[1 - playerIdx] = state.damage();
    }
}

void ExampleModel::notifyStatsUpdated()
{
    // Calls any listeners, in this case the ExampleView, so they
    // know that we've updated statistics data
    dispatcher.dispatch(&ExampleListener::onStatsUpdated);
}

void ExampleModel::onFrameDataNewUniqueFrame(int frameIdx, const rfcommon::Frame<4>& frame)
{
    // We only care about 1v1
    if (frame.count() != 2)
        return;

    auto fdata = session_->tryGetFrameData();

    for (int playerIdx = 0; playerIdx != frame.count(); ++playerIdx)
    {
        updateTotalDamage(playerIdx, frameIdx);
        udpateEarliestKill(playerIdx, frameIdx);
    }
    notifyStatsUpdated();
}
