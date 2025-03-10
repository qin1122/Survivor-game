#include "player2_menu.h"
#include"player.h"

player2_menu::player2_menu(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::player2_menuClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	fund_attribute new_player{ 800,400,1200,25,4,1 };
	weapon_attribute new_player_weapon{ 5,0.5,2 };
	player_menu = new Player(2, new_player, new_player_weapon, 0, 1, 0, 1, 0);
	enemyclose_menu = new Enemy(300, 10, 4, 1);
	enemyfar_menu = new Enemy(200, 10, 5, 100);
	twotobattle = new battle(2, player_menu, enemyclose_menu, enemyfar_menu);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(changeslot2()));
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
	ui->to_store->setStyleSheet(stylesheet2);
	QObject::connect(ui->weapon, SIGNAL(clicked()), this, SLOT(see_weapon()));
	QObject::connect(ui->necklace, SIGNAL(clicked()), this, SLOT(see_necklace()));
	QObject::connect(ui->gloves, SIGNAL(clicked()), this, SLOT(see_gloves()));
	QObject::connect(ui->chestpate, SIGNAL(clicked()), this, SLOT(see_chestpate()));
	QObject::connect(ui->belt, SIGNAL(clicked()), this, SLOT(see_belt()));
	QObject::connect(ui->boots, SIGNAL(clicked()), this, SLOT(see_boot()));
	QObject::connect(ui->player2, SIGNAL(clicked()), this, SLOT(see_attribute()));
	QObject::connect(ui->to_store, SIGNAL(clicked()), this, SLOT(tostore()));
	QObject::connect(ui->start, SIGNAL(clicked()), this, SLOT(tobattle()));
	QObject::connect(&twotostore, SIGNAL(sig2()), this, SLOT(toplayer_menu()));
	QObject::connect(twotobattle, SIGNAL(siga2()), this, SLOT(backtomenu()));
	QString text_attribute1 = QString("Player2:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute1);
}

player2_menu::player2_menu(Player*& player, Enemy*& enemyclose, Enemy*& enemyfar, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::player2_menuClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	player_menu = player;
	enemyclose_menu = enemyclose;
	enemyfar_menu = enemyfar;
	twotobattle = new battle(2, player_menu, enemyclose_menu, enemyfar_menu);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(changeslot2()));
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
	ui->to_store->setStyleSheet(stylesheet2);
	QObject::connect(ui->weapon, SIGNAL(clicked()), this, SLOT(see_weapon()));
	QObject::connect(ui->necklace, SIGNAL(clicked()), this, SLOT(see_necklace()));
	QObject::connect(ui->gloves, SIGNAL(clicked()), this, SLOT(see_gloves()));
	QObject::connect(ui->chestpate, SIGNAL(clicked()), this, SLOT(see_chestpate()));
	QObject::connect(ui->belt, SIGNAL(clicked()), this, SLOT(see_belt()));
	QObject::connect(ui->boots, SIGNAL(clicked()), this, SLOT(see_boot()));
	QObject::connect(ui->player2, SIGNAL(clicked()), this, SLOT(see_attribute()));
	QObject::connect(ui->to_store, SIGNAL(clicked()), this, SLOT(tostore()));
	QObject::connect(ui->start, SIGNAL(clicked()), this, SLOT(tobattle()));
	QObject::connect(&twotostore, SIGNAL(sig2()), this, SLOT(toplayer_menu()));
	QObject::connect(twotobattle, SIGNAL(siga2()), this, SLOT(backtomenu()));
	QString text_attribute1 = QString("Player2:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute1);
}

player2_menu::~player2_menu()
{
	delete ui;
	delete player_menu;
	delete twotobattle;
}

void player2_menu::closeEvent(QCloseEvent* event)
{
	save2();
	event->accept();
}

void player2_menu::save2()
{
	twotobattle->save_game(player_menu, twotobattle->enemy_close_, twotobattle->enemy_far_);
}

void player2_menu::see_weapon()
{
	int levels = 1;
	levels += (player_menu->get_attack_power() - 25) / 5;
	QString text_weapon = QString("Weapon""\n""\n""Level:" + QString::number(levels) + "\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)");
	ui->textbox->setPlainText(text_weapon);
}

void player2_menu::see_necklace()
{
	int levels = 1;
	levels += (player_menu->get_duration() - 0.5) / 0.5;
	QString text_necklace = QString("Necklace""\n""\n""Level:" + QString::number(levels) + "\n""duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)");
	ui->textbox->setPlainText(text_necklace);
}

void player2_menu::see_gloves()
{
	int levels = 1;
	levels += (2 - player_menu->get_cool()) / 0.5;
	QString text_gloves = QString("Glove""\n""\n""Level:" + QString::number(levels) + "\n""cool:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_gloves);
}

void player2_menu::see_chestpate()
{
	int levels = 1;
	levels += (player_menu->get_hp1() - 800) / 100;
	QString text_chestpate = QString("Chestplate""\n""\n""Level:" + QString::number(levels) + "\n""Hp:" + QString::number(player_menu->get_hp1()) + " (2000)");
	ui->textbox->setPlainText(text_chestpate);
}

void player2_menu::see_belt()
{
	int levels = 1;
	levels += (player_menu->get_hp2() - 400) / 100;
	QString text_belt = QString("Belt""\n""\n""Level:" + QString::number(levels) + "\n""Hp:" + QString::number(player_menu->get_hp2()) + " (1000)");
	ui->textbox->setPlainText(text_belt);
}

void player2_menu::see_boot()
{
	int levels = 1;
	levels += (player_menu->get_speed() - 4) / 1;
	QString text_boot = QString("Boot""\n""\n""Level:" + QString::number(levels) + "\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)");
	ui->textbox->setPlainText(text_boot);
}

void player2_menu::see_attribute() {
	QString text_attribute = QString("Player2:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute);
}

void player2_menu::changeslot2() {
	emit sig2();
}

void player2_menu::tostore() {
	this->hide();
	twotostore.show();
	int mainx = this->geometry().x();
	int mainy = this->geometry().y();
	twotostore.setGeometry(mainx, mainy, 1280, 900);
	twotostore.player_upgrade = player_menu;
	twotostore.enemy_close1 = twotobattle->enemy_close_;
	twotostore.enemy_far1 = twotobattle->enemy_far_;
	twotostore.ui->coin_num->display(twotostore.player_upgrade->get_coin());
	twotostore.set_levels();
	twotostore.set_colors();
	twotostore.set_text();
	twotostore.set_prices();
}

void player2_menu::tobattle() {
	this->hide();
	twotobattle->show();
	int mainx = this->geometry().x();
	int mainy = this->geometry().y();
	twotobattle->setGeometry(mainx, mainy, 1280, 900);
	twotobattle->ui->player1->hide();
	twotobattle->ui->player1_hp->hide();
	twotobattle->ui->player2->show();
	twotobattle->ui->player2_hp->show();
	twotobattle->player_ = player_menu;
	twotobattle->ui->exp_num->display(twotobattle->player_->get_exp());
	twotobattle->ui->level_num->display(twotobattle->player_->get_level());
	twotobattle->ui->coin_num->display(twotobattle->player_->get_coin());
	twotobattle->time_start();
	this->ui->back->setEnabled(false);
}

void player2_menu::toplayer_menu()
{
	twotostore.hide();
	this->show();
	int mainx = twotostore.geometry().x();
	int mainy = twotostore.geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
	player_menu = twotostore.player_upgrade;
	ui->coin_num->display(player_menu->get_coin());
	QString text_attribute1 = QString("Player2:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute1);
}

void player2_menu::backtomenu()
{
	int mainx = twotobattle->geometry().x();
	int mainy = twotobattle->geometry().y();
	this->setGeometry(mainx, mainy, 1280, 900);
	player_menu = twotobattle->player_;
	ui->coin_num->display(player_menu->get_coin());
	this->show();
	twotobattle->close();
	QString text_attribute1 = QString("Player2:\n""Hp:" + QString::number(player_menu->get_Hp()) + " (3000)""\n""ATK:" + QString::number(player_menu->get_attack_power()) + " (60)""\n""Speed:" + QString::number(player_menu->get_speed()) + " (10)\n""Get range:" + QString::number(player_menu->get_get_range()) + " (5)\n""Attack range:" + QString::number(player_menu->get_attack_range()) + " (30)\n""Duration:" + QString::number(player_menu->get_duration(), 'g', 2) + " (3)\n""Cool time:" + QString::number(player_menu->get_cool(), 'g', 2) + " (0.5)");
	ui->textbox->setPlainText(text_attribute1);
}


