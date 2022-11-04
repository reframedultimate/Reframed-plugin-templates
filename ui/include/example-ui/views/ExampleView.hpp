#pragma once

#include "example-ui/listeners/ExampleListener.hpp"
#include <QWidget>

// Forward declare the class created by Qt designer
namespace Ui {
    class ExampleView;
}

class ExampleModel;

class ExampleView
        : public QWidget
        , public ExampleListener
{
    Q_OBJECT

public:
    explicit ExampleView(ExampleModel* model, QWidget* parent=nullptr);
    ~ExampleView();

private slots:
    void onButtonPressed();

private:
    void onCounterChanged() override;

private:
    // We hold a weak reference to the model (ExampleModel) so we can listen
    // to it
    ExampleModel* model_;

    // This is an instance of the widget hierarchy we created in QtDesigner
    Ui::ExampleView* ui_;
};

