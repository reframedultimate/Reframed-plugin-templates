#pragma once

#include "rfcommon/ListenerDispatcher.hpp"

class ExampleListener;

/*!
 * \brief This would be your "model", i.e. where you store your state. The
 * "view" is given a pointer to the model so it can display all of the model's
 * data. Typically, the view will also register as a listener to the model so
 * it can update the view whenever data changes.
 *
 * To demonstrate this in this example we simply have the model store a counter
 * value that gets incremented.
 *
 * Read up on "model view architecture" for more information. It is a simpler
 * version of "model view controller" architecture
 */
class ExampleModel
{
public:
    void incCounter();
    int counterValue() const { return counter_; }

    rfcommon::ListenerDispatcher<ExampleListener> dispatcher;

private:
    int counter_ = 0;
};
