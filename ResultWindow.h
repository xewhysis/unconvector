#pragma once
#include <QDialog>
#include <QTextEdit>
class ResultWindow : public QDialog {
    Q_OBJECT
public:
    explicit ResultWindow(QWidget* parent = nullptr);
    void setText(const QString& text);
private:
    QTextEdit* output;
};