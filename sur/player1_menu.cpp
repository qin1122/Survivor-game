#pragma once
#include "player1_menu.h"
#include<QString>
#include<QPushButton>

player1_menu::player1_menu(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::player1_menuClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	num = 0;
	fund_attribute new_player{ 700,300,1000,20,4,1 };
	weapon_attribute new_player_weapon{ 5,0.5,3 };
	player_menu = new Player(1, new_player, new_player_weapon, 0, 1, 0, 1, 0);
	enemyclose_menu = new Enemy(300, 10, 4, 1);
	enemyfar_menu = new Enemy(200, 10, 5, 100);
	onetobattle = new battle(1, player_menu,enemyclose_menu,enemyfar_menu);
	ui->coin_num->display(player_menu->get_coin());
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;}");
	ui->back->setStyleSheet(stylesheet);
	QString stylesheet1 = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:20pt \"Century\";}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font:20pt \"Century\";}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font:20pt \"Century\";}");
	ui->start->setStyleSheet(stylesheet1);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(changeslot1()));
	QString stylesheet2 = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:13pt \"Century\";}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font:13pt \"Century\";}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font:13pt \"Century\";}");
	ui->go_to_store->setStyleSheet(stylesheet2);
	QObject::connect(ui->weapon, SIGNAL(clicked()), this, SLOT(see_weapon()));
	QObject::connect(ui->necklace , SIGNAL(clicked()), this, SLOT(see_necklace()));
	QObject::connect(ui->gloves, SIGNAL(clicked()), this, SLOT(see_gloves()));
	QObject::connect(ui->chestpate, SIGNAL(clicked()), this, SLOT(see_chestpate()));
	QObject::connect(ui->belt, SIGNAL(clicked()), this, SLOT(see_belt()));
	QObject::connect(ui->boot, SIGNAL(clicked()), this, SLOT(see_boot()));
	QObject::connect(ui->player1, SIGNAL(clicked()), this, SLOT(see_attribute()));
	QObject::connect(ui->go_to_store, SIGNAL(clicked()), this, SLOT(tostore()));
	QObject::connect(ui->start, SIGNAL(clicked()), this, SLOT(tobattle()));
	QObject::connect(&onetostore, SIGNAL(sig()), this, SLOT(toplayer_menu()));
	QObject::connect(onetobattle, SIGNAL(siga1()), this, SLOT(backtomenu()));
	QString text_attribute2 = QString("Player1:\n""Hp:"+QString::number(player_menu->get_Hp())+" (3000)""\n""ATK:"+QString::number(player_menu->get_attack_power())+" (60)""\n""Speed:"+QString::number(player_menu->get_speed())+" (10)\n""Get range:"+QString::number(player_menu->get_get_range())+" (5)\n""Attack range:"+QString::number(player_menu->get_attack_range())+" (30)\n""Duration:"+QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:"+QString::number(player_menu->get_cool(),'g',2)+" (0.5)");
	ui->textbox->setPlainText(text_attribute2);
}

player1_menu::player1_menu(Player*& player, Enemy*& enemyclose, Enemy*& enemyfar, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::player1_menuClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	num = 0;
	player_menu = player;
	enemyclose_menu = enemyclose;
	enemyfar_menu = enemyfar;
	onetobattle = new battle(1, player_menu, enemyclose_menu, enemyfar_menu);
	ui->coin_num->display(player_menu->get_coin());
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;}");
	ui->back->setStyleSheet(stylesheet);
	QString stylesheet1 = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:20pt \"Century\";}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font:20pt \"Century\";}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font:20pt \"Century\";}");
	ui->start->setStyleSheet(stylesheet1);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(changeslot1()));
	QString stylesheet2 = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:13pt \"Century\";}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font:13pt \"Century\";}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font:13pt \"Century\";}");
	ui->go_to_store->setStyleSheet(stylesheet2);
	QObject::connect(ui->weapon, SIGNAL(clicked()), this, SLOT(see_weapon()));
	QObject::connect(ui->necklace, SIGNAL(clicked()), this, SLOT(see_necklace()));
	QObject::connect(ui->gloves, SIGNAL(clicked()), this, SLOT(see_gloves()));
	QObject::connect(ui->chestpate, SIGNAL(clicked()), this, SLOT(see_chestpate()));
	QObject::connect(ui->belt, SIGNAL(clicked()), this, SLOT(see_belt()));
	QObject::connect(ui->boot, SIGNAL(clicked()), this, SLOT(see_boot()));
	QObject::connect(ui->player1, SIGNAL(clicked()), this, SLOT(see_attribute()));
	QObject::connect(ui->go_to_store, SIGNAL(clicked()), this, SLOT(tostore()));
	QObject::connect(ui->start, SIGNAL(clicked()), this, SLOT(tobattle()));
	QObject::connect(&onetostore, SIGNAL(sig()), this, SLOT(toplayer_menu()));
	QObject::connect(onetobattle, SIGNAL(siga1()), this, SLOT(backtomenu()));
	QString text_attribute2 = QString("Player1:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute2);
}

player1_menu::~player1_menu()
{
	delete ui;
	delete player_menu;
	delete onetobattle;
}

void player1_menu::closeEvent(QCloseEvent* event)
{
	save1();
	event->accept();
}

void player1_menu::see_weapon()
{
	int levels = 1;
	levels += (player_menu->get_attack_power() - 20) / 5;
	QString text_weapon = QString("Weapon""\n""\n""Level:"+QString::number(levels)+"\n""ATK:"+ QString::number(player_menu->get_attack_power()) + " (60)");
	ui->textbox->setPlainText(text_weapon);
}

void player1_menu::see_necklace()
{
	int levels = 1;
	levels += (player_menu->get_duration() - 0.5) / 0.5;
	QString text_necklace = QString("Necklace""\n""\n""Level:" + QString::number(levels) + "\n""duration:"+QString::number(player_menu->get_duration(),'g',2)+" (3)");
	ui->textbox->setPlainText(text_necklace);
}

void player1_menu::see_gloves()
{
	int levels = 1;
	levels += (3 - player_menu->get_cool()) / 0.5;
	QString text_gloves = QString("Glove""\n""\n""Level:" + QString::number(levels) + "\n""cool:"+QString::number(player_menu->get_cool(),'g',2)+" (0.5)");
	ui->textbox->setPlainText(text_gloves);
}

void player1_menu::see_chestpate()
{
	int levels = 1;
	levels += (player_menu->get_hp1() - 700) / 100;
	QString text_chestpate = QString("Chestplate""\n""\n""Level:" + QString::number(levels) + "\n""Hp:"+QString::number(player_menu->get_hp1())+" (2000)");
	ui->textbox->setPlainText(text_chestpate);
}

void player1_menu::see_belt()
{
	int levels = 1;
	levels += (player_menu->get_hp2() - 300) / 100;
	QString text_belt = QString("Belt""\n""\n""Level:" + QString::number(levels) + "\n""Hp:"+ QString::number(player_menu->get_hp2()) + " (1000)");
	ui->textbox->setPlainText(text_belt);
}

void player1_menu::see_boot()
{
	int levels = 1;
	levels += (player_menu->get_speed() - 4) / 1;
	QString text_boot = QString("Boot""\n""\n""Level:" + QString::number(levels) + "\n""Speed:"+ QString::number(player_menu->get_speed())+" (10)");
	ui->textbox->setPlainText(text_boot);
}

void player1_menu::see_attribute() {
	QString text_attribute = QString("Player1:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute);
}

void player1_menu::changeslot1() {
	emit sig1();
}

void player1_menu::tostore() {
	this->hide();
	onetostore.show();
	int mainx = this->geometry().x();
	int mainy = this->geometry().y();
	onetostore.setGeometry(mainx, mainy, 1280, 900);
	onetostore.player_upgrade = player_menu;
	onetostore.enemy_close1 = onetobattle->enemy_close_;
	onetostore.enemy_far1 = onetobattle->enemy_far_;
	onetostore.ui->coin_num->display(onetostore.player_upgrade->get_coin());
	onetostore.set_levels();
	onetostore.set_colors();
	onetostore.set_prices();
	onetostore.set_text();
}

void player1_menu::tobattle() {
	onetobattle->show();
	onetobattle->ui->player1->show();
	onetobattle->ui->player1_hp->show();
	onetobattle->ui->player2->hide();
	onetobattle->ui->player2_hp->hide();
	onetobattle->player_ = player_menu;
	onetobattle->ui->coin_num->display(onetobattle->player_->get_coin());
	onetobattle->ui->exp_num->display(onetobattle->player_->get_exp());
	onetobattle->ui->level_num->display(onetobattle->player_->get_level());
	this->hide();
	onetobattle->time_start();
	this->ui->back->setEnabled(false);
}

void player1_menu::toplayer_menu()
{
	onetostore.hide();
	this->show();
	int mainx = onetostore.geometry().x();
	int mainy = onetostore.geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
	player_menu = onetostore.player_upgrade;
	ui->coin_num->display(player_menu->get_coin());
	QString text_attribute2 = QString("Player1:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute2);
}

void player1_menu::backtomenu()
{
	this->show();
	onetobattle->hide();
	int mainx = onetobattle->geometry().x();
	int mainy = onetobattle->geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
	player_menu = onetobattle->player_;
	ui->coin_num->display(player_menu->get_coin());
	QString text_attribute2 = QString("Player1:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute2);
}

void player1_menu::save1()
{
	onetobattle->save_game(player_menu, onetobattle->enemy_close_, onetobattle->enemy_far_);
}



