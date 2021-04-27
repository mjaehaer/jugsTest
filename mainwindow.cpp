#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QListView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

struct response {
    int steps;
    QList<int> allsteps;
};

int gcd(int a, int b)
{
    if (b==0)
       return a;
    return gcd(b, a%b);
}

response pour1(int fromCap, int toCap, int d)
{
    response resp1;
    int from = fromCap;
    int to = 0;
    int step = 1;
    resp1.allsteps.push_back(0);
    resp1.allsteps.push_back(0);
    resp1.allsteps.push_back(from);
    resp1.allsteps.push_back(to);
    while (from != d && to != d)
    {
        int temp = std::min(from, toCap - to);
        resp1.allsteps.push_back(from);
        resp1.allsteps.push_back(to);
        to   += temp;
        from -= temp;
        step++;
        resp1.allsteps.push_back(from);
        resp1.allsteps.push_back(to);

        if (from == d || to == d)
            break;
        if (from == 0)
        {
            resp1.allsteps.push_back(from);
            resp1.allsteps.push_back(to);
            from = fromCap;
            step++;
            resp1.allsteps.push_back(from);
            resp1.allsteps.push_back(to);
        }

        if (to == toCap)
        {
            resp1.allsteps.push_back(from);
            resp1.allsteps.push_back(to);
            to = 0;
            step++;
            resp1.allsteps.push_back(from);
            resp1.allsteps.push_back(to);
        }
    }
//    qDebug() << resp1.allsteps;
    resp1.steps = step;
    return resp1;
}


void MainWindow::on_pushButton_clicked()
{
    int x,y,z;
    x = ui->lineEdit->text().toInt();
    y = ui->lineEdit_2->text().toInt();
    z = ui->lineEdit_3->text().toInt();
    if (x == 0 || y == 0 || z == 0)
    {
        ui->label_5->setText("Void in a one of parameters.");
        return ;
    }
    if (y > x)
        std::swap(y, x);

    if (z > x){
        ui->label_5->setText("No solution.");
        return ;
    }

    if ((z % gcd(x,y)) != 0)
    {
        ui->label_5->setText("No solution.");
        return;
    }

    response struct1 = pour1(x,y,z);
//    qDebug() << struct1.steps;
    response struct2 = pour1(y,x,z);
//    qDebug() << struct2.steps;
    response trgtstruct;
    if (struct1.steps > struct2.steps)
        trgtstruct = struct2;
    else
        trgtstruct = struct1;

//    QStandardItemModel *model = new QStandardItemModel;
//    QStringList horizontalHeader;
//    horizontalHeader.append("First jug");
//    horizontalHeader.append("Second jug");
//    horizontalHeader.append("First jug");
//    horizontalHeader.append("Second jug");
//    int counter = 3;
//    int col = 0;
//    int row = 0;
//    for (int i = 0; i < trgtstruct.allsteps.length(); i++)
//    {
//        QStandardItem *item;
//        item = new QStandardItem(QString(trgtstruct.allsteps[i]));
//        if (col == counter){
//            model->setItem(row, col, item);
//            row++;
//            col = 0;
//        } else {
//            model->setItem(row, col, item);
//            col++;
//        }
//        delete item;
//    }
//    model->setHorizontalHeaderLabels(horizontalHeader);
//    ui->tableView->setModel(model);
//    ui->tableView->resizeRowsToContents();
//    ui->tableView->resizeColumnsToContents();
//    ui->tableWidget = new QTableWidget(this);
    QStringList horizontalHeader;
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setShowGrid(true);
    horizontalHeader.append("First jug");
    horizontalHeader.append("Second jug");
    horizontalHeader.append("First jug");
    horizontalHeader.append("Second jug");
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);
    int counter = 3;
    int col = 0;
    int row = 0;
    ui->tableWidget->insertRow(row);
    for (int i = 0; i < trgtstruct.allsteps.length(); i++)
    {
        if (col == counter){
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::number(trgtstruct.allsteps[i])));
            row++;
            col = 0;
//            qDebug() << trgtstruct.allsteps[i];
            ui->tableWidget->insertRow(row);

        } else {
            ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::number(trgtstruct.allsteps[i])));
            col++;
//            qDebug() << trgtstruct.allsteps[i];
        }
    }
    ui->tableWidget->setRowCount(row);
    ui->tableWidget->resizeColumnsToContents();
    ui->label_5->setText("Optial algorithm have a " + QString::number(trgtstruct.steps) + " steps!");
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->label_5->setText("Click calculate");
    ui->tableWidget->setRowCount(0);
}

