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

    int counter_of_GS_bigramms = 0;
    int counter_of_SG_bigramms = 0;
    int counter_of_SS_bigramms = 0;
    int counter_of_GG_bigramms = 0;

    map <QString, int> map_of_GS_bigramms = {};
    map <QString, int> map_of_SG_bigramms = {};
    map <QString, int> map_of_SS_bigramms = {};
    map <QString, int> map_of_GG_bigramms = {};

    //podshet bigram
    for(int i = 0; i < this->_glasnie.size(); ++i)
        for(int j = 0; j < this->_glasnie.size(); ++j)
            map_of_GG_bigramms.insert(make_pair(_glasnie[i] + _glasnie[j], qs_.count(_glasnie[i] + _glasnie[j])));

    for(int i = 0; i < this->_soglasnie.size(); ++i)
        for(int j = 0; j < this->_soglasnie.size(); ++j)
            map_of_SS_bigramms.insert(make_pair(_soglasnie[i] + _soglasnie[j], qs_.count(_soglasnie[i] + _soglasnie[j])));

    for(int i = 0; i < this->_glasnie.size(); ++i)
        for(int j = 0; j < this->_soglasnie.size(); ++j)
            map_of_GS_bigramms.insert(make_pair(_glasnie[i] + _soglasnie[j], qs_.count(_glasnie[i] + _soglasnie[j])));

    for(int i = 0; i < this->_soglasnie.size(); ++i)
        for(int j = 0; j < this->_glasnie.size(); ++j)
            map_of_SG_bigramms.insert(make_pair(_soglasnie[i] + _glasnie[j], qs_.count(_soglasnie[i] + _glasnie[j])));

    //poisk 4-gramm
    map <QString, int> map_of_4gramms = {};
    for(int i = 0;  (i + 3) < qs_.size(); ++i){
        auto _4gramm = QString(qs_.at(i)) + QString(qs_.at(i + 1)) + QString(qs_.at(i + 2)) + QString(qs_.at(i + 3));
        map_of_4gramms.insert(make_pair(_4gramm, qs_.count(_4gramm)));
    }


    //Udalenie nuley i podshet
    for(auto pos = map_of_GG_bigramms.begin(); pos != map_of_GG_bigramms.end();)
      if(pos->second == 0)
        pos = map_of_GG_bigramms.erase(pos);
      else{
        counter_of_GG_bigramms += pos->second;
        ++pos;
      }

    for(auto pos = map_of_4gramms.begin(); pos != map_of_4gramms.end();)
      if(pos->second == 0)
        pos = map_of_4gramms.erase(pos);
      else
        ++pos;

    for(auto pos = map_of_SS_bigramms.begin(); pos != map_of_SS_bigramms.end();)
      if(pos->second == 0)
        pos = map_of_SS_bigramms.erase(pos);
      else{
        counter_of_SS_bigramms += pos->second;
        ++pos;
      }

    for(auto pos = map_of_GS_bigramms.begin(); pos != map_of_GS_bigramms.end();)
      if(pos->second == 0)
        pos = map_of_GS_bigramms.erase(pos);
      else{
        counter_of_GS_bigramms += pos->second;
        ++pos;
      }

    for(auto pos = map_of_SG_bigramms.begin(); pos != map_of_SG_bigramms.end();)
      if(pos->second == 0)
        pos = map_of_SG_bigramms.erase(pos);
      else{
        counter_of_SG_bigramms += pos->second;
        ++pos;
      }

    ui->textBrowser->append("ВСЕГО " + QString::number(qs_.size()) + " Символов,\n" + "ВСЕГО ГС Биграмм " + QString::number(counter_of_GS_bigramms) + "\nВСЕГО СГ Биграмм " + QString::number(counter_of_SG_bigramms) + "\n");
    ui->textBrowser->append("ВСЕГО СС Биграмм " + QString::number(counter_of_SS_bigramms) + "\nВСЕГО ГГ Биграмм " + QString::number(counter_of_GG_bigramms) + "\n");
    //vivod bukv
    for(auto obj : count_of_edinichnie_bukvi)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));

    ui->textBrowser->append("\n\n\nВЫВОД БИГРАММ ГГ\n");

    //vivod bigramm
    for(auto obj : map_of_GG_bigramms)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));

    ui->textBrowser->append("\n\n\nВЫВОД БИГРАММ СС\n");

    for(auto obj : map_of_SS_bigramms)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));

    ui->textBrowser->append("\n\n\nВЫВОД БИГРАММ СГ\n");

    for(auto obj : map_of_SG_bigramms)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));

    ui->textBrowser->append("\n\n\nВЫВОД БИГРАММ ГС\n");

    for(auto obj : map_of_GS_bigramms)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));

    ui->textBrowser->append("\n\n\nВЫВОД 4 ГРАММ ГС\n");

    for( auto obj : map_of_4gramms)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений"));


}
