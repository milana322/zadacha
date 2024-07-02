#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->taskComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onTaskSelected()));
    connect(ui->executeButton, SIGNAL(clicked()), this, SLOT(onExecuteButtonClicked()));

    ui->epsilonTextEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTaskSelected()
{
    ui->resultTextEdit->clear();
    ui->epsilonTextEdit->setVisible(ui->taskComboBox->currentIndex() == 1);
}

void MainWindow::onExecuteButtonClicked()
{
    int taskIndex = ui->taskComboBox->currentIndex();
    switch (taskIndex) {
    case 0:
        checkPrime();
        break;
    case 1:
        calculateSin();
        break;
    case 2:
        solveQuadratic();
        break;
    }
}

void MainWindow::checkPrime()
{
    bool ok;
    int num = ui->resultTextEdit->toPlainText().toInt(&ok);
    if (!ok) {
        ui->resultTextEdit->setText("Введите допустимое целое число.");
        return;
    }

    if (num <= 1) {
        ui->resultTextEdit->setText("Число должно быть больше 1");
        return;
    }
    Functions a;
    QVector<int> res = a.checkPrimary(num);
    if (res.isEmpty()) {
        ui->resultTextEdit->setText("Число " + QString::number(num) + " простое.");
    } else {
        ui->resultTextEdit->setText("Число " + QString::number(num) + " составное.");
        ui->resultTextEdit->append("Его разложение: ");
        for (int factor : res) {
            ui->resultTextEdit->append(QString::number(factor));
        }
    }
}

void MainWindow::calculateSin() {
    bool ok;

    // Проверка точности
    double epsilon = ui->epsilonTextEdit->toPlainText().toDouble(&ok);
    if (!ok || epsilon <= 0) {
        ui->epsilonTextEdit->setText("Введите допустимое значение точности.");
        return;
    }

    // Проверка угла
    float x = ui->resultTextEdit->toPlainText().toFloat(&ok);
    if (!ok) {
        ui->resultTextEdit->setText("Введите угол в радианах.");
        return;
    }

    // Вычисление синуса
    Functions a;
    double sinx = a.Sin(x, epsilon);

    // Вывод результата с заданной точностью
    ui->resultTextEdit->setText("sin(" + QString::number(x) + ") ≈ " + QString::number(sinx, 'f', -std::log10(epsilon)));

    // Скрытие поля для точности после вычисления
    ui->epsilonTextEdit->setVisible(false);
}

void MainWindow::solveQuadratic() {
    bool ok;
    QStringList coefficients = ui->resultTextEdit->toPlainText().split(" ");
    if (coefficients.size() != 3) {
        ui->resultTextEdit->setText("Введите три коэффициента (a, b, c).");
        return;
    }

    double a = coefficients[0].toDouble(&ok);
    if (!ok) {
        ui->resultTextEdit->setText("Некорректный коэффициент a.");
        return;
    }

    double b = coefficients[1].toDouble(&ok);
    if (!ok) {
        ui->resultTextEdit->setText("Некорректный коэффициент b.");
        return;
    }

    double c = coefficients[2].toDouble(&ok);
    if (!ok) {
        ui->resultTextEdit->setText("Некорректный коэффициент c.");
        return;
    }

    // Вычисление корней квадратного уравнения
    Functions aFunc;
    QVector <double> resul = aFunc.solveQuadratic(a, b, c);
    if(resul[1]==0 && resul[0]==0)  ui->resultTextEdit->setText("Нет действительных корней.");
    else ui->resultTextEdit->setText("Корнями являюся числа" + QString::number(resul[0])+" и "+QString::number(resul[1]));
    // Вывод результата

}
