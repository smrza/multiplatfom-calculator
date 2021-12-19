#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void number_pressed();
    void on_pushButton_seperator_released();
    void on_pushButton_clear_released();
    void on_pushButton_equals_released();
    void binary_operation_pressed();
    void on_pushButton_clearlast_released();
    void on_pushButton_plus_minus_released();
};

#endif // CALCULATOR_H
