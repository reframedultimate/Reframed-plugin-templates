// This file is generated from the form file (ExampleView.ui)
#include "ui_ExampleView.h"

#include "example-ui/views/ExampleView.hpp"
#include "example-ui/models/ExampleModel.hpp"

ExampleView::ExampleView(ExampleModel* model, QWidget* parent)
    : QWidget(parent)
    , model_(model)
    , ui_(new Ui::ExampleView)  // Instantiate UI created in QtDesigner
{
    // Set up UI created in QtDesigner
    ui_->setupUi(this);

    // Update view based on model
    ExampleView::onCounterChanged();

    // Listen to any changes to the model
    model_->dispatcher.addListener(this);

    // We listen to whenever the push button is pressed by the user
    connect(ui_->pushButton, &QPushButton::released, this, &ExampleView::onButtonPressed);
}

ExampleView::~ExampleView()
{
    // Remove things in reverse order
    model_->dispatcher.removeListener(this);
    delete ui_;
}

void ExampleView::onButtonPressed()
{
    // Increment counter when button is pressed
    model_->incCounter();
}

void ExampleView::onCounterChanged()
{
    ui_->spinBox->setValue(model_->counterValue());
}
