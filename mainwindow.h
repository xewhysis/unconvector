#pragma once
#include <QMainWindow>
class QLineEdit;
class QTextEdit;
class QLabel;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void convert();
    void loadFile();
    void saveFile();
private:
    QLineEdit* inputEdit;
    QLineEdit* baseFromEdit;
    QLineEdit* baseToEdit;
    QTextEdit* resultEdit;
    QLabel* statusLabel;
    QString lastResult;
};