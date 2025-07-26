#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_start_clicked();

    void on_output_sourceChanged(const QUrl &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_crit_rate_textChanged(const QString &arg1);

    void on_speed_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_7_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_lineEdit_11_textChanged(const QString &arg1);

    void on_lineEdit_12_textChanged(const QString &arg1);

    void on_start_2_clicked();

    void on_start_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
