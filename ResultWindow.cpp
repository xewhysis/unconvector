#include "ResultWindow.h"
#include <QVBoxLayout>
     ResultWindow::ResultWindow(QWidget* parent)
    : QDialog(parent) {
    resize(800, 600);
    output = new QTextEdit;
    output->setReadOnly(true);
    auto* layout = new QVBoxLayout;
    layout->addWidget(output);
    setLayout(layout);
}
void ResultWindow::setText(const QString& text) {
    output->setText(text);
}