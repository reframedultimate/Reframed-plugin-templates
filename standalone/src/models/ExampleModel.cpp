#include "myplugin/models/ExampleModel.hpp"
#include "myplugin/views/ExampleView.hpp"

ExampleModel::ExampleModel(RFPluginFactory* factory)
    : StandalonePlugin(factory)
{
}

ExampleModel::~ExampleModel()
{
}

QWidget* ExampleModel::createView()
{
    // Create new instance of view. The view registers as a listener to this model
    return new ExampleView(this);
}

void ExampleModel::destroyView(QWidget* view)
{
    // ReFramed no longer needs the view, delete it
    delete view;
}

void ExampleModel::setNumber1(int value)
{
    number1_ = value;
    updateSum();
}

void ExampleModel::setNumber2(int value)
{
    number2_ = value;
    updateSum();
}

void ExampleModel::updateSum()
{
    sum_ = number1_ + number2_;
    dispatcher.dispatch(&ExampleListener::onExampleSumChanged);
}

