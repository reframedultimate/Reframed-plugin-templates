#pragma once

class ExampleListener
{
public:
    // Called when the model updates its counter
    virtual void onCounterChanged() = 0;
};
