#include "mainwindow.h"
#include "ui_mainwindow.h"

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


using namespace std;

char fixed_tolower(char c) {
    return tolower((unsigned char)c);
}

QString regex_and_tolower(QString _text) {

    setlocale(LC_ALL, "Russian");

    QString untext = _text;

    QRegExp no_letters("[^А-Яа-я -]");
    QRegExp spaces(" {1,}");
    QRegExp defis("\ -[а-яА-Я]");
    QRegExp post_defis("\-");
    QRegExp un_defis("\- |\ -");
    QRegExp yo("\[Ёё]");

    QString replacement = " ";
    QString nothing = "";

    untext.replace(yo, "е");
    untext.replace(no_letters, nothing);
    untext.replace(post_defis, nothing);
    untext.replace(spaces, nothing);

    auto text = untext;
    text = text.toLower();

    untext.clear();

    return text;
}

void MainWindow::on_pushButton_clicked()
{
    QString qs_1 = ui->textEdit->toPlainText();  //v etom QString text dlya analiza

    auto qs_ = regex_and_tolower(qs_1); //erase all trash including spaces, make all letters low


    ui->textBrowser->append("Всего символов: " + QString::number(qs_.length()) + "\n");


    //podshet bukv//
    map <QString, int> count_of_edinichnie_bukvi = {};

    for(auto obj : this->_bukvi)
        count_of_edinichnie_bukvi.insert(make_pair(obj, qs_.count(obj)));
    //podshet bukv//



    //sasha, tut podshet bigramm
    map <QString, int> count_of_bigramms = {};
    vector<QString> used_letters;

    for (auto x : count_of_edinichnie_bukvi)
        if (x.second != 0)
            used_letters.push_back(x.first);
    for (auto i : used_letters)
        for (auto j : used_letters){
            QString _key = i+j;
            count_of_bigramms[_key] = 0;
        }
    for (auto x : count_of_bigramms) {
        int counter = 0;
        QString f = x.first;
        counter = qs_.count(f);
        count_of_bigramms[f] = counter;
    }


    /////////////////////////////////////



    //vivod
    for(auto obj : count_of_edinichnie_bukvi)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений, \n"));

}
