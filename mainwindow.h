#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;//操作符

    QString calculation(bool *ok=NULL);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void btnNumClicked();
    void on_btnPoint_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();
    void binaryOperatorClicked();
    void on_btnEqual_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
