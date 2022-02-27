#pragma once

class ExampleListener
{
public:
	// Called when the model updates statistics
	virtual void onStatsUpdated() = 0;

	// Called when the nintendo switch connects or disconnects
	virtual void onConnectionStateChanged() = 0;
};
