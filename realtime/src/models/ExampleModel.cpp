#include "example-realtime/models/ExampleModel.hpp"
#include "example-realtime/listeners/ExampleListener.hpp"
#include "rfcommon/Session.hpp"
#include "rfcommon/PlayerState.hpp"

void ExampleModel::setConnectedState(bool connected)
{
	isConnected_ = connected;
	dispatcher.dispatch(&ExampleListener::onConnectionStateChanged);
}

void ExampleModel::setSession(rfcommon::Session* session)
{
	assert(session_.isNull());

	// Reset our counters
	for (int i = 0; i != 2; ++i)
	{
		totalDamage_[i] = 0.0;
		earliestKill_[i] = 999.0;
	}

	// Increments refcount to session object
	session_ = session;

	// It's possible that the session object already contains frame data,
	// which happens if the session was loaded from a file, or if the plugin
	// was loaded while a session was running. We need to go through each
	// frame and update our model accordingly
	if (session_->playerCount() == 2) // Only care about 1v1
	{
		for (int p = 0; p != session_->playerCount(); ++p)
			for (int f = 0; f != session_->playerStateCount(p); ++f)
			{
				updateTotalDamage(p, f);
				udpateEarliestKill(p, f);
			}
		notifyStatsUpdated();
	}

	// We want to be notified of any new frame data that gets added to the
	// session in the future
	session_->dispatcher.addListener(this);
}

void ExampleModel::clearSession(rfcommon::Session* session)
{
	if (session_.isNull())
		return;

	// Stop listening to events
	session_->dispatcher.removeListener(this);

	// Release our reference to the session. This decrements the refcount.
	session_.drop();
}

void ExampleModel::updateTotalDamage(int playerIdx, int stateIdx)
{
	const rfcommon::PlayerState& state = session_->playerStateAt(playerIdx, stateIdx);
	const rfcommon::PlayerState& prevState = stateIdx > 0 ? session_->playerStateAt(playerIdx, stateIdx - 1) : state;

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
	const rfcommon::PlayerState& state = session_->playerStateAt(playerIdx, stateIdx);

	// Did a player die?
	const rfcommon::String* enumName = session_->mappingInfo().fighterStatus.statusToBaseEnumName(state.status());
	if (enumName != nullptr && *enumName == "FIGHTER_STATUS_KIND_DEAD")
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

void ExampleModel::onRunningSessionNewUniquePlayerState(int playerIdx, const rfcommon::PlayerState& state)
{
	// We only care about 1v1
	if (session_->playerCount() != 2)
		return;

	updateTotalDamage(playerIdx, session_->playerStateCount(playerIdx) - 1);
	udpateEarliestKill(playerIdx, session_->playerStateCount(playerIdx) - 1);
	notifyStatsUpdated();
}
