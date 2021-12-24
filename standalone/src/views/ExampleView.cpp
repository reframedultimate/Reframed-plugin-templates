#include "ui_ExampleView.h"
#include "myplugin/views/ExampleView.hpp"
#include "myplugin/models/ExampleModel.hpp"

ExampleView::ExampleView(ExampleModel* model, QWidget* parent)
    : QWidget(parent)
    , model_(model)
    , ui_(new Ui::ExampleView)
{
    ui_->setupUi(this);

    // Get sum from model and add it to the view
    ui_->lineEdit_sum->setText(QString::number(model_->sum()));

    // Connect up with the spinboxes in the UI
    connect(ui_->spinBox_number1, qOverload<int>(&QSpinBox::valueChanged), this, &ExampleView::onNumber1Changed);
    connect(ui_->spinBox_number2, qOverload<int>(&QSpinBox::valueChanged), this, &ExampleView::onNumber2Changed);

    model_->dispatcher.addListener(this);
}

ExampleView::~ExampleView()
{
    model_->dispatcher.removeListener(this);
    delete ui_;
}

void ExampleView::onNumber1Changed(int value)
{
    model_->setNumber1(value);
}

void ExampleView::onNumber2Changed(int value)
{
    model_->setNumber2(value);
}

void ExampleView::onExampleSumChanged()
{
    int sum = model_->sum();
    ui_->lineEdit_sum->setText(QString::number(sum));
}

