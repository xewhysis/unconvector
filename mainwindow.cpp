#include "mainwindow.h"
#include "ResultWindow.h"
#include "BaseConverter.h"
#include "test.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
MainWindow::MainWindow() {
    auto* central = new QWidget;
    auto* layout = new QVBoxLayout;
    inputEdit = new QLineEdit;
    baseFromEdit = new QLineEdit;
    baseToEdit = new QLineEdit;
    resultEdit = new QTextEdit;
    resultEdit->setReadOnly(true);
    auto* convertButton = new QPushButton("Convert");
    auto* loadButton = new QPushButton("Load from file");
    auto* saveButton = new QPushButton("Save result");
    statusLabel = new QLabel;
    layout->addWidget(new QLabel("Input number"));
    layout->addWidget(inputEdit);
    layout->addWidget(new QLabel("Source base"));
    layout->addWidget(baseFromEdit);
    layout->addWidget(new QLabel("Target base"));
    layout->addWidget(baseToEdit);
    layout->addWidget(convertButton);
    layout->addWidget(loadButton);
    layout->addWidget(saveButton);
    layout->addWidget(new QLabel("Result"));
    layout->addWidget(resultEdit);
    layout->addWidget(statusLabel);
    central->setLayout(layout);
    setCentralWidget(central);
    connect(convertButton, &QPushButton::clicked,
            this, &MainWindow::convert);
    connect(loadButton, &QPushButton::clicked,
            this, &MainWindow::loadFile);
    connect(saveButton, &QPushButton::clicked,
            this, &MainWindow::saveFile);
    resize(700, 500);
}

void MainWindow::convert() {
    try {
        QString sp = baseFromEdit->text();
        QString sq = baseToEdit->text();
        test(sp);
        test(sq);
        int p = sp.toInt();
        int q = sq.toInt();
        // qDebug() << p << q;
        if (p < 2 || p > 500 || q < 2 || q > 500)
            throw "Base must be in range 2..500";
        QString result = BaseConverter::convert(inputEdit->text(), p, q);
        resultEdit->setText(result);
        lastResult = result;
        // statusLabel->setText("Success");
        // ResultWindow* rw = new ResultWindow(this);
        // rw->setText(result);
        // rw->show();
    }
    catch (const char* error) {
        QMessageBox::critical(this, "ERROR", error);
    }
}
void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);
    inputEdit->setText(in.readLine());
    baseFromEdit->setText(in.readLine());
    baseToEdit->setText(in.readLine());

}
void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
        return;
    QTextStream out(&file);
    out << lastResult;
}