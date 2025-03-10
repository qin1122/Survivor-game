#include "menupage.h"
#include<QPushButton>
#include<QString>

menupage::menupage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::menupageClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;}");
	QString stylesheet1 = QString("QPushButton{color:rgba(255,255,255,0);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,0);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,0);background-color:transparent;}");
	ui->back->setStyleSheet(stylesheet);
	ui->player1_btn->setStyleSheet(stylesheet1);
	ui->player2_btn->setStyleSheet(stylesheet1);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(changeslots()));
	QObject::connect(ui->player1_btn, SIGNAL(clicked()), this, SLOT(toplayer1_menu()));
	QObject::connect(ui->player2_btn, SIGNAL(clicked()), this, SLOT(toplayer2_menu()));
	QObject::connect(&flag1, SIGNAL(sig1()), this, SLOT(tomenupage1()));
	QObject::connect(&flag2, SIGNAL(sig2()), this, SLOT(tomenupage2()));

}

menupage::~menupage()
{
	delete ui;
}

void menupage::changeslots() {
	emit mysignal();
}

void menupage::toplayer1_menu() {
	this->hide();
	flag1.show();
	int mainx = this->geometry().x();
	int mainy = this->geometry().y();
	flag1.setGeometry(mainx, mainy, 1280, 900);
}

void menupage::toplayer2_menu() {
	this->hide();
	flag2.show();
	int mainx = this->geometry().x();
	int mainy = this->geometry().y();
	flag2.setGeometry(mainx, mainy, 1280, 900);
}

void menupage::tomenupage1() {
	flag1.hide();
	this->show();
	int mainx = flag1.geometry().x();
	int mainy = flag1.geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
}

void menupage::tomenupage2() {
	flag2.hide();
	this->show();
	int mainx = flag2.geometry().x();
	int mainy = flag2.geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
}