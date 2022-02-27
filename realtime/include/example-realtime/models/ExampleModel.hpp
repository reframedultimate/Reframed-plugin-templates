#pragma once

#include "rfcommon/SessionListener.hpp"
#include "rfcommon/ListenerDispatcher.hpp"
#include "rfcommon/Reference.hpp"

namespace rfcommon {
    class Session;
}

class ExampleListener;

class ExampleModel : public rfcommon::SessionListener
{
public:
    void setConnectedState(bool connected);
    bool isConnected() const { return isConnected_;  }

    void setSession(rfcommon::Session* session);
    void clearSession(rfcommon::Session* session);

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
    // RunningGameSession events
    void onRunningGameSessionPlayerNameChanged(int playerIdx, const rfcommon::SmallString<15>& name) override {}
    void onRunningGameSessionSetNumberChanged(rfcommon::SetNumber number) override {}
    void onRunningGameSessionGameNumberChanged(rfcommon::GameNumber number) override {}
    void onRunningGameSessionFormatChanged(const rfcommon::SetFormat& format) override {}
    void onRunningGameSessionWinnerChanged(int winnerPlayerIdx) override {}

    // RunningSession events
    void onRunningSessionNewUniquePlayerState(int playerIdx, const rfcommon::PlayerState& state) override;
    void onRunningSessionNewPlayerState(int playerIdx, const rfcommon::PlayerState& state) override {}
    void onRunningSessionNewUniqueFrame(const rfcommon::SmallVector<rfcommon::PlayerState, 8>& states) override {}
    void onRunningSessionNewFrame(const rfcommon::SmallVector<rfcommon::PlayerState, 8>& states) override {}

private:
    rfcommon::Reference<rfcommon::Session> session_;
    float totalDamage_[2] = { 0.0, 0.0 };
    float earliestKill_[2] = { 999.0, 999.0 };
    bool isConnected_ = false;
};
