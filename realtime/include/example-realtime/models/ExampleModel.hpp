#pragma once

#include "rfcommon/FrameDataListener.hpp"
#include "rfcommon/ListenerDispatcher.hpp"
#include "rfcommon/Reference.hpp"

namespace rfcommon {
    class Session;
}

class ExampleListener;

class ExampleModel : public rfcommon::FrameDataListener
{
public:
    void setConnectedState(bool connected);
    bool isConnected() const { return isConnected_;  }

    void setSession(rfcommon::Session* session);
    void clearSession();

    // Getters, used by view
    float totalDamagePlayer1() const { return totalDamage_[0]; }
    float totalDamagePlayer2() const { return totalDamage_[1]; }
    float earliestKillPlayer1() const { return earliestKill_[0]; }
    float earliestKillPlayer2() const { return earliestKill_[1]; }

    // If you want to use explicit interfaces for communication between models
    // and views, this lets view instances register as listeners to the model.
    //
    // If you want to use Qt's signals and slots, then you don't need this.
    rfcommon::ListenerDispatcher<ExampleListener> dispatcher;

private:
    void updateTotalDamage(int playerIdx, int stateIdx);
    void udpateEarliestKill(int playerIdx, int stateIdx);
    void notifyStatsUpdated();

private:
    // This will get called every time a new unique frame is received from the
    // Nintendo Switch
    void onFrameDataNewUniqueFrame(int frameIdx, const rfcommon::Frame<4>& frame) override;

    void onFrameDataNewFrame(int frameIdx, const rfcommon::Frame<4>& frame) override {}

private:
    rfcommon::Reference<rfcommon::Session> session_;
    float totalDamage_[2] = { 0.0, 0.0 };
    float earliestKill_[2] = { 999.0, 999.0 };
    bool isConnected_ = false;
};
