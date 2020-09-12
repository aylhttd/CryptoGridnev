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

/*#include <iostream>
#include <fstream>
#include <regex>
#include <list>
#include <algorithm>
#include <cstring>
#include <locale>

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");

	std::ifstream _input("text.txt");
	std::ofstream _output("RESULTOFPARSE.txt");
	int count = 1;
	int helper = 1;
	int size = 0;
	int tmp;
	regex no_letters("[^А-Яа-я -]");
	regex spaces(" {2,}");
	regex defis("\ -[а-яА-Я]");
	regex post_defis("\-");
	regex un_defis("\- |\ -");
	regex yo("\[Ёё]");
	string replacement = " ";
	string nothing = "";
	std::string untext;
	if (_input.is_open()) {
		while (!_input.eof()) {
			tmp = _input.get();
			untext.push_back(tmp);
			size++;
		}
	}

	string temp6 = regex_replace(untext, yo, "е");
	string temp = regex_replace(temp6, no_letters, nothing);
	string temp5 = regex_replace(temp, post_defis, nothing);


	auto text = temp5;

	transform(text.begin(), text.end(), text.begin(), tolower);;
	if (text[0] == ' ')
		text.erase(0, 1);
	text.pop_back();
	if (text[text.size() - 1] != ' ')
		text.push_back(' ');
	_output << text;

	temp6.clear();
	temp5.clear();
	temp.clear();
	text.clear();
}*/

void MainWindow::on_pushButton_clicked()
{
    QString qs_ = ui->textEdit->toPlainText();  //v etom QString text dlya analiza

    //a tut dobav' regex

    ui->textBrowser->append("Всего символов: " + QString::number(qs_.length()) + "\n");


    //podshet bukv//
    map <QString, int> count_of_edinichnie_bukvi = {};

    for(auto obj : this->_bukvi)
        count_of_edinichnie_bukvi.insert(make_pair(obj, qs_.count(obj)));
    //podshet bukv//



    //dima, tut podshet i vivod bigramm

    /////////////////////////////////////



    //vivod
    for(auto obj : count_of_edinichnie_bukvi)
        ui->textBrowser->append(obj.first + QString::fromStdString(" " + to_string(obj.second) + " вхождений, \n"));

}
