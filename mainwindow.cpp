#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBTNs = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1},
               {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},
               {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},
               {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
                 };


    foreach (auto btn, digitBTNs) {
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    }

    //数字点击
    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    //二元运算符点击
    connect(ui->btnMultiply,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(binaryOperatorClicked()));

    //一元操作符点击
    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
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
    opcode.clear();
    opcodes.clear();
    operands.clear();
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

void MainWindow::btnUnaryOperatorClicked()
{
    double result = 0;
    if(operand != "")
    {
        result = operand.toDouble();
        operand = "";

        QString op = qobject_cast<QPushButton*>(sender())->text();
        if(op == "%")
            result /= 100.0;
        else if(op == "1/x")
            result = 1/result;
        else if( op == "x^2")
            result = result * result;
        else if(op=="√")
            result = sqrt(result);
    }
    ui->display->setText(QString::number(result));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    foreach (auto btnKey, digitBTNs.keys()) {
        if(event->key()==btnKey){
            digitBTNs[btnKey]->animateClick();
        }
    }

    // 检查运算符键
    if (event->key() == Qt::Key_Plus) {
        ui->btnPlus->animateClick();
    } else if (event->key() == Qt::Key_Minus) {
        ui->btnSub->animateClick();
    } else if (event->key() == Qt::Key_Asterisk) {
        ui->btnMultiply->animateClick();
    } else if (event->key() == Qt::Key_Slash) {
        ui->btnDivide->animateClick();
    }else if (event->key() == Qt::Key_Equal || event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // 处理等于号键或回车键
        ui->btnEqual->animateClick();
    }else if (event->key() == Qt::Key_Period || event->key() == Qt::Key_Comma) {
        // 处理小数点键 (可以使用 "." 或 ",")
        ui->btnPoint->animateClick();
    }else if (event->key() == Qt::Key_Backspace) {
        // 处理 Backspace 键
        ui->btnDel->animateClick();
    }
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
        if(op == "=")
        {
            op = opcodes.front();
        }

        if(op == "+")
        {
            result = operand1 + operand2;
        }
        else if(op == "-")
        {
            result = operand1 - operand2;
        }
        else if(op == "×")
        {
            result = operand1 * operand2;
        }
        else if(op == "/")
        {
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));
        ui->statusbar->showMessage("calculation is running");
    }
    else
    {
        ui->statusbar->showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));
    }
    return QString::number(result);
}

void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_btnSign_clicked()
{
    // 确保 operand 不是空的
    if (!operand.isEmpty()) {
        // 转换 operand 为 double 类型，方便处理
        double value = operand.toDouble();

        // 改变符号
        value = -value;

        // 将值转换回字符串并更新 operand
        operand = QString::number(value);

        // 更新显示
        ui->display->setText(operand);
    }
}


