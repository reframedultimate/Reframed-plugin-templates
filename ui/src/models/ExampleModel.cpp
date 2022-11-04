#include "example-ui/models/ExampleModel.hpp"
#include "example-ui/listeners/ExampleListener.hpp"

void ExampleModel::incCounter()
{
    counter_++;
    dispatcher.dispatch(&ExampleListener::onCounterChanged);
}
