#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->pb0,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb1,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb2,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb3,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb4,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb5,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb6,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb7,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb8,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pb9,SIGNAL(released()), this,SLOT(digit_pressed()));
    connect(ui->pbPlusOrMinus,SIGNAL(released()), this,SLOT(unary_operation_pressed()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digit_pressed() {
    // qDebug() << "Button pressed";
    QPushButton *button = (QPushButton *) sender();
    double labelNumber;
    QString newLabel;
    labelNumber = (ui->labelDisplay->text() + button->text()).toDouble();
    newLabel = QString::number(labelNumber, 'g', 15);
    ui->labelDisplay->setText(newLabel);
}

void MainWindow::on_pbDot_released() {
    ui->labelDisplay->setText(ui->labelDisplay->text() + ".");
}

void MainWindow::unary_operation_pressed() {
    double labelNumber;
    QString newLabel;

    QPushButton *button = (QPushButton *) sender();
    if (button->text() == "+/-") {
        labelNumber = ui->labelDisplay->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->labelDisplay->setText(newLabel);
    }
}
