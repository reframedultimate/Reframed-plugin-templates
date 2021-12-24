#pragma once

#include "rfcommon/StandalonePlugin.hpp"
#include "rfcommon/ListenerDispatcher.hpp"

class ExampleListener;

class ExampleModel : public rfcommon::StandalonePlugin
{
public:
    ExampleModel(RFPluginFactory* factory);
    ~ExampleModel();

    /*!
     * This is called by ReFramed to create an instance of your view.
     * It is possible that this gets called more than once, for example if
     * ReFramed wants to add your view to different parts of the program.
     *
     * Typically
     */
    QWidget* createView() override;

    /*!
     * The counter-part to createView(). When ReFramed removes your view
     * it will give it back to you to destroy.
     */
    void destroyView(QWidget* view) override;

    // View sets the input numbers with these methods
    void setNumber1(int number);
    void setNumber2(int number);

    // Get the sum
    int sum() const
        { return sum_; }

    // If you want to use explicit interfaces for communication between models
    // and views, this lets view instances register as listeners to the model.
    //
    // If you want to use Qt's signals and slots, then you don't need this.
    rfcommon::ListenerDispatcher<ExampleListener> dispatcher;

private:
    void updateSum();

private:
    int number1_ = 0;
    int number2_ = 0;
    int sum_ = 0;
};

