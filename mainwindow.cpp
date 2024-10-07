#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //数字点击
    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    //二元运算符点击
    connect(ui->btnMultiply,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{

    QString digit = qobject_cast<QPushButton*>(sender())->text();
    //处理开始输入0的几种特殊情况
    if(digit == "0" && operand == "0")
        digit = "";

    if(digit != "0" &&operand == "0")
        operand = "";


    operand += digit;


    ui->display->setText(operand);
    // ui->statusbar->showMessage(qobject_cast<QPushButton*>(sender())->text()+"btn Clicked");

}

void MainWindow::on_btnPoint_clicked()
{
    if(!operand.contains(".")){
        operand += qobject_cast<QPushButton*>(sender())->text();
    }
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length()-1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}

void MainWindow::binaryOperatorClicked()
{
    ui->statusbar->showMessage("current operand: "+operand);

    QString opcode = qobject_cast<QPushButton*>(sender())->text();

    if(operand != "")
    {
        operands.push_back(operand);
        operand = "";

        opcodes.push_back(opcode);
    }
    QString result = calculation();
    ui->display->setText(result);
}


void MainWindow::on_btnEqual_clicked()
{
    if(operand != "")
    {
        operands.push_back(operand);
        operand = "";
    }
    QString result = calculation();
    ui->display->setText(result);
}

QString MainWindow::calculation(bool *ok)
{
    // ui->statusbar->showMessage("calculation is running");
    double result = 0;
    if(operands.size()==2 && opcodes.size()>0)
    {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //去操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+")
        {
            result = operand1 + operand2;
        }
        else if(op == "-")
        {
            result = operand1 - operand2;
        }
        else if(op == "*")
        {
            result = operand1 * operand2;
        }
        else if(op == "/")
        {
            result = operand1 / operand2;
        }

        ui->statusbar->showMessage("calculation is running");
    }
    else
    {
        ui->statusbar->showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    return QString::number(result);
}
