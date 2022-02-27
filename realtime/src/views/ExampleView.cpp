#include "ui_ExampleView.h"
#include "example-realtime/views/ExampleView.hpp"
#include "example-realtime/models/ExampleModel.hpp"
#include <QLabel>

ExampleView::ExampleView(ExampleModel* model, QWidget* parent)
    : QWidget(parent)
    , model_(model)
    , ui_(new Ui::ExampleView)  // Instantiate UI created in QtDesigner
{
    // Set up UI created in QtDesigner
    ui_->setupUi(this);

    // Update view based on model
    ExampleView::onStatsUpdated();
    ExampleView::onConnectionStateChanged();

    // Listen to any changes to the model
    model_->dispatcher.addListener(this);
}

ExampleView::~ExampleView()
{
    // Remove things in reverse order
    model_->dispatcher.removeListener(this);
    delete ui_;
}

void ExampleView::onStatsUpdated()
{
    // The model has updated some statistics, fetch them and display
    // them in the UI
    ui_->label_totalDamagePlayer1->setText(QString::number(model_->totalDamagePlayer1()) + "%");
    ui_->label_totalDamagePlayer2->setText(QString::number(model_->totalDamagePlayer2()) + "%");

    ui_->label_earliestKillPlayer1->setText(QString::number(model_->earliestKillPlayer1()) + "%");
    ui_->label_earliestKillPlayer2->setText(QString::number(model_->earliestKillPlayer2()) + "%");
}

void ExampleView::onConnectionStateChanged()
{
    // Show or hide the big red "(not connected)" text
    ui_->label_disconnected->setVisible(!model_->isConnected());
}
