#include "calculator.h"
#include "ui_calculator.h"

double result_so_far = 0;
double last_number = 0;
bool first_operation = true;
std::function<double(double, double)> op;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->pushButton_zero, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_one, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_two, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_three, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_four, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_five, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_six, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_seven, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_eight, SIGNAL(released()), this, SLOT(number_pressed()));
    connect(ui->pushButton_nine, SIGNAL(released()), this, SLOT(number_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operation_pressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::number_pressed()
{
    if(ui->label->text() == "0"){
        return;
    }

    if(ui->label->text().length() >= 20){
        return;
    }

    QPushButton * button = (QPushButton*)sender();
    QString new_label = ui->label->text() + button->text();
    ui->label->setText(new_label);
}


void Calculator::on_pushButton_seperator_released()
{
    QString check_sep = ui->label->text();
    bool result = check_sep.contains('.');

    if (!result && ui->label->text() != "")
    {
        ui->label->setText(ui->label->text() + ".");
    }
    else if (ui->label->text() == ""){
        ui->label->setText("0.");
    }
}


void Calculator::on_pushButton_clear_released()
{
    result_so_far = 0;
    last_number = 0;
    first_operation = true;
    ui->label->setText("");
}
void Calculator::on_pushButton_equals_released()
{
    if(ui->label->text() != "" && op){
        result_so_far = op(last_number, ui->label->text().toDouble());
    }
    else if(ui->label->text() != ""){
        result_so_far = ui->label->text().toDouble();
    }

    QString new_label = QString::number(result_so_far, 'g', 15);
    ui->label->setText(new_label);
    first_operation = true;
}

void Calculator::binary_operation_pressed()
{
    QPushButton * button = (QPushButton*) sender();

    if(ui->label->text() != ""){

        if(!first_operation){
            result_so_far = op(last_number, ui->label->text().toDouble());
        }
        else {
            first_operation = false;
            last_number = ui->label->text().toDouble();
            result_so_far = last_number;
        }

        if(button->text() == "+"){
            op = std::plus<double>();
        }
        if(button->text() == "÷"){
            op = std::divides<double>();
        }
        if(button->text() == "−"){
            op = std::minus<double>();
        }
        if(button->text() == "×"){
            op = std::multiplies<double>();
        }

        ui->label->setText("");
        last_number = result_so_far;
    }
}

void Calculator::on_pushButton_clearlast_released()
{
    ui->label->setText("");
}

void Calculator::on_pushButton_plus_minus_released()
{
    if(ui->label->text() != ""){
        double current_number = ui->label->text().toDouble();
        current_number *= -1;
        QString new_label = QString::number(current_number, 'g', 15);
        ui->label->setText(new_label);
    }
}
