#pragma once

#include "myplugin/listeners/ExampleListener.hpp"
#include <QWidget>

// Forward declare the class created by Qt designer
namespace Ui {
	class ExampleView;
}

class ExampleModel;

class ExampleView : public QWidget
                  , public ExampleListener
{
    Q_OBJECT

public:
    explicit ExampleView(ExampleModel* model, QWidget* parent=nullptr);
    ~ExampleView();

private slots:
    void onNumber1Changed(int value);
    void onNumber2Changed(int value);

private:
    // Listen to when the model changes
    void onExampleSumChanged() override;

private:
    ExampleModel* model_;
    Ui::ExampleView* ui_;
};

