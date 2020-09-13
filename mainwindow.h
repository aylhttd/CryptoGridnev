#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include <algorithm>
#include <cstring>
#include <locale>
#include <string>
#include <map>
#include <vector>
#include <QString>

using namespace std;

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

private:
    Ui::MainWindow *ui;

    vector<QString> _bukvi = {"а","б","в","г","д","е","ж","з","и","й","к","л","м","н","о","п","р","с","т","у","ф","х","ц","ч","ш","щ","ъ","ы","ь","э","ю","я"};
    vector<QString> _glasnie = {"а", "е", "и", "о", "у", "ы", "э", "ю", "я"};
    vector<QString> _soglasnie = {"б","в","г","д","ж","з","й","к","л","м","н","п","р","с","т","ф","х","ц","ч","ш","щ","ъ","ь"};

};
#endif // MAINWINDOW_H
