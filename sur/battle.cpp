#pragma once
#include "battle.h"
#include<qlistview.h>
#include<qtimer.h>
#include<time.h>
#include<stdlib.h>
#include<random>
#include<qpushbutton.h>
#include<qprogressbar.h>
#include<qdialog.h>
#include<qtextedit.h>
#include<fstream>
#include<string>

battle::battle(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::battleClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	player_ = new Player;
	enemy_close_ = new Enemy;
	enemy_far_ = new Enemy;
	flag = 1;
	kill = 0;
	expupnum = 0;
	time0 = new QTimer(this);
	time11 = new QTimer(this);
	time1 = new QTimer(this);
	time2 = new QTimer(this);
	time3 = new QTimer(this);
	time4 = new QTimer(this);
	timer = new QTimer(this);
	time_enemy_close = new QTimer(this);
	time_enemy_far = new QTimer(this);
	store = new QTimer(this);
	setFocus();
	ui->btn2->setEnabled(false);
}

battle::battle(int flag, Player*& player_, Enemy*& enemyclose_,Enemy*&enemyfar_,QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::battleClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	this->player_ = player_;
	this->flag = flag;
	this->player_->change_playernum(this->flag);
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;}");
	ui->stop->setStyleSheet(stylesheet);
	ui->upgrade->hide();
	ui->overpage->hide();
	enemy_close_ = enemyclose_;
	enemy_far_ = enemyfar_;
	time11 = new QTimer(this);
	timer = new QTimer(this);
	time_enemy_close = new QTimer(this);
	time_enemy_far = new QTimer(this);
	setFocus();
	set_enemy();
	set_Hp();
	ui->btn2->setEnabled(false);
	timer->start(100);
	connect(timer, &QTimer::timeout, [=]() {
		move_enemy_close(this->player_->get_playernum());
		move_enemy_far(enemy_far_->get_Speed());
		});
	time0 = new QTimer(this);
	time0->start(this->player_->get_cool() * 1000);
	connect(time0, &QTimer::timeout, [=]() {
		for (int i = 0; i < (this->player_->get_duration()) / 0.25; i++) {
			player_close_attack(this->player_->get_playernum());
		}
		});
	time1 = new QTimer(this);
	time1->start(100);
	connect(time1, &QTimer::timeout, [=]() {
		enemy_close_attack(this->player_->get_playernum());
		});
    time2 = new QTimer(this);
	time2->start(10);
	connect(time2, &QTimer::timeout, [=]() {
		enemy_far_attack(this->player_->get_playernum());
		});
	time3 = new QTimer(this);
	time3->start(1);
	connect(time3, &QTimer::timeout, [=]() {
		get_drops();
		});
	change_coin();
	if (this->flag == 1) {
		QObject::connect(ui->stop, SIGNAL(clicked()), this, SLOT(backtomenupage1()));
	}
	else if (this->flag == 2) {
		QObject::connect(ui->stop, SIGNAL(clicked()), this, SLOT(backtomenupage2()));
	}
	store = new QTimer(this);
	store->start(30000);
	QObject::connect(ui->btn, SIGNAL(clicked()), this, SLOT(save()));
	QObject::connect(ui->btn2, SIGNAL(clicked()), this, SLOT(reborn_page()));
	QObject::connect(ui->choice1, SIGNAL(clicked()), this, SLOT(upgrade1()));
	QObject::connect(ui->choice2, SIGNAL(clicked()), this, SLOT(upgrade2()));
	QObject::connect(ui->choice3, SIGNAL(clicked()), this, SLOT(upgrade3()));
}


battle::~battle()
{
	delete ui;
	delete player_;
	delete enemy_close_;
	delete enemy_far_;
	delete timer;
	delete time0;
	delete time1;
	delete time2;
	delete time3;
	delete time4;
	delete time_enemy_close;
	delete time_enemy_far;
	flag = 0;
	name_enemy_close.clear();
	name_enemy_far.clear();
	drop_exps.clear();
	drop_hps.clear();
	drop_coins.clear();
	nums.clear();
}

void battle::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_A:
		if (flag == 1) {
			player_move(1, event, player_);
			break;
		}
		else if (flag == 2) {
			player_move(2, event, player_);
			break;
		}
	case Qt::Key_D:
		if (flag == 1) {
			player_move(1, event, player_);
			break;
		}
		else if (flag == 2) {
			player_move(2, event, player_);
			break;
		}
	case Qt::Key_W:
		if (flag == 1) {
			player_move(1, event, player_);
			break;
		}
		else if (flag == 2) {
			player_move(2, event, player_);
			break;
		}
	case Qt::Key_S:
		if (flag == 1) {
			player_move(1, event, player_);
			break;
		}
		else if (flag == 2) {
			player_move(2, event, player_);
			break;
		}
	default:
		break;
	}
}

void battle::set_enemy()
{
	time_enemy_close->start(3000);
	connect(time_enemy_close, &QTimer::timeout, [=]() {
		int num1 = Random_num(10000);
		if ((num1 % 5 != 2) && (num1 % 5 != 4)) {
			int num_enemy = name_enemy_close.size() + 1;
			QString str = QString::number(num_enemy);
			QString enemy_name = "enemy_close" + str;
			QString enemy_hp_name = "enemy_close_hp" + str;
			QListView* enemy_close = new QListView;
			QProgressBar* enemy_close_hp = new QProgressBar;
			int num0 = Random_num(10000);
			int numx = Random_num(1050);
			int numy = Random_num(846);
			if (num0 % 3 == 0) {
				enemy_close->setGeometry(20, numy, 38, 53);
				enemy_close_hp->setGeometry(0, numy - 20, 80, 10);
			}
			else if (num0 % 3 == 1) {
				enemy_close->setGeometry(1222, numy, 38, 53);
				enemy_close_hp->setGeometry(1202, numy - 20, 80, 10);
			}
			else if (num0 % 3 == 2) {
				enemy_close->setGeometry(numx, 847, 38, 53);
				enemy_close_hp->setGeometry(numx - 20, 827, 80, 10);
			}
			QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/enemy_close.png);background-color:transparent;}");
			QString stylesheet1 = QString("QProgressBar::chunk{background-color: rgb(255, 0, 0);}");
			enemy_close_hp->setStyleSheet(stylesheet1);
			enemy_close_hp->setTextVisible(false);
			enemy_close_hp->setMaximum(enemy_close_->get_Hp());
			enemy_close_hp->setValue(enemy_close_->get_Hp());
			enemy_close->setStyleSheet(stylesheet);
			enemy_close->setFrameStyle(QFrame::NoFrame);
			enemy_close->setParent(this);
			enemy_close->show();
			enemy_close_hp->setParent(this);
			enemy_close_hp->show();
			struct names name_close { enemy_close, enemy_close_hp };
			name_enemy_close.push_back(name_close);
			enemy_close->QObject::setObjectName(enemy_name);
			enemy_close_hp->QObject::setObjectName(enemy_hp_name);
		}
	});
	time_enemy_far->start(3000);
	connect(time_enemy_far, &QTimer::timeout, [=]() {
		int num1 = Random_num(10000);
		if (name_enemy_far.size() == 5) {
			return;
		}
		if ((num1 % 5 == 2) || (num1 % 5 == 4)) {
			int temp = 0;
			int num_enemy = name_enemy_far.size() + 1;
			QString str = QString::number(num_enemy);
			QString enemy_name = "enemy_far" + str;
			QString enemy_hp_name = "enemy_far_hp" + str;
			QListView* enemy_far = new QListView;
			QProgressBar* enemy_far_hp = new QProgressBar;
			int num0 = Random_num(10000);
			int numx = Random_num(1044);
			int numy = Random_num(846);
			if (num0 % 3 == 2) {
				enemy_far->setGeometry(20, numy, 44, 53);
				enemy_far_hp->setGeometry(0, numy - 20, 80, 10);
				temp = 1;
			}
			else if (num0 % 3 == 0) {
				enemy_far->setGeometry(1216, numy, 44, 53);
				enemy_far_hp->setGeometry(1196, numy - 20, 80, 10);
				temp = 2;
			}
			else if (num0 % 3 == 1) {
				enemy_far->setGeometry(numx, 847, 44, 53);
				enemy_far_hp->setGeometry(numx - 20, 827, 80, 10);
				temp = 3;
			}
			QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/enemy_far.png);background-color:transparent;}");
			QString stylesheet1 = QString("QProgressBar::chunk{background-color: rgb(255, 0, 0);}");
			enemy_far_hp->setStyleSheet(stylesheet1);
			enemy_far_hp->setTextVisible(false);
			enemy_far_hp->setMaximum(enemy_far_->get_Hp());
			enemy_far_hp->setValue(enemy_far_->get_Hp());
			enemy_far->setStyleSheet(stylesheet);
			enemy_far->setFrameStyle(QFrame::NoFrame);
			enemy_far->setParent(this);
			enemy_far->show();
			enemy_far_hp->setParent(this);
			enemy_far_hp->show();
			struct names_far name_far { enemy_far, enemy_far_hp, temp, 0 };
			enemy_far->QObject::setObjectName(enemy_name);
			enemy_far_hp->QObject::setObjectName(enemy_hp_name);
			name_enemy_far.push_back(name_far);
		}
	});
}

void battle::set_Hp()
{
	if (player_->get_playernum() == 1) {
		ui->player1_hp->setMaximum(player_->get_Hp());
	}
	else if (player_->get_playernum() == 2) {
		ui->player2_hp->setMaximum(player_->get_Hp());
	}
}

void battle::closeEvent(QCloseEvent* event)
{
	save_game(player_, enemy_close_, enemy_far_);
	event->accept();
}

bool battle::if_touch_block(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		int px = player1_pos.x();
		int py = player1_pos.y();
		if ((((px == 110+91 ) && (py > 180-53) && (py < 180+278))||
			((px == 600+91 )&&(py>0)&&(py<20+278))||
			((px == 900+190) && (py > 420-53) && (py < 420+95)) ||
			((px == 350+190) && (py > 710-53) && (py < 710+95)) ||
			((px == 1090+91) && (py > 610-53) && (py < 610+278)))){
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		int px = player2_pos.x();
		int py = player2_pos.y();
		if ((((px == 110 + 91) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 + 91) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 + 190) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 + 190) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 + 91) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
}

bool battle::if_touchright_block(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		int px = player1_pos.x();
		int py = player1_pos.y();
		if ((((px == 110-39 ) && (py > 180-53) && (py < 180+278)) ||
			((px == 600-39) && (py > 0) && (py <20+278)) ||
			 ((px == 900-39) && (py > 420-53) && (py < 420+95)) ||
			 ((px == 350-39) && (py > 710-53) && (py < 710+95))||
			((px==1090-39)&&(py>610-53)&&(py<610+278)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		int px = player2_pos.x();
		int py = player2_pos.y();
		if ((((px == 110 - 45) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 - 45) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 - 45) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 - 45) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 - 45) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
}

bool battle::if_touchup_block(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		int px = player1_pos.x();
		int py = player1_pos.y();
		if ((((py == 180+278)&& (px > 110-39) && (px < 110+91))||
			((py == 20+278) && (px > 600-39) && (px < 600+91)) ||
			((py == 420+95) && (px > 900-39) && (px < 900+190)) ||
			((py == 710+95) && (px > 350-39) && (px < 350+190)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		int px = player2_pos.x();
		int py = player2_pos.y();
		if ((((py == 180 + 278) && (px > 110 - 45) && (px < 110 + 91)) ||
			((py == 20 + 278) && (px > 600 - 45) && (px < 600 + 91)) ||
			((py == 420 + 95) && (px > 900 - 45) && (px < 900 + 190)) ||
			((py == 710 + 95) && (px > 350 - 45) && (px < 350 + 190)))) {
			return true;
		}
		else return false;
	}
}

bool battle::if_touchdown_block(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		int px = player1_pos.x();
		int py = player1_pos.y();
		if ((((py == 180 -53) && (px > 110 - 39) && (px < 110 + 91)) ||
			((py == 20 -53) && (px > 600 - 39) && (px < 600 + 91)) ||
			((py == 420 -53) && (px > 900 - 39) && (px < 900 + 190)) ||
			((py == 710 -53) && (px > 350 - 39) && (px < 350 + 190))||
			((py==610-53)&&(px>1090-39)&&(px<1090+91)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		int px = player2_pos.x();
		int py = player2_pos.y();
		if ((((py == 180 -53) && (px > 110 - 45) && (px < 110 + 91)) ||
			((py == 20 -53) && (px > 600 - 45) && (px < 600 + 91)) ||
			((py == 420 -53) && (px > 900 - 45) && (px < 900 + 190)) ||
			((py == 710 -53) && (px > 350 - 45) && (px < 350 + 190)) ||
			((py == 610 - 53) && (px > 1090 - 45) && (px < 1090 + 91)))) {
			return true;
		}
		else return false;
	}
}

bool battle::if_enemytouch_block(QListView*& enemy, int flag)
{
	if (flag == 1) {//½üÕ½¹Ö
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((px == 110 + 91) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 + 91) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 + 190) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 + 190) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 + 91) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((px == 110 + 91) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 + 91) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 + 190) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 + 190) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 + 91) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
	return false;
}

bool battle::if_enemytouchright_block(QListView*& enemy, int flag)
{
	if (flag == 1) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((px == 110 - 38) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 - 38) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 - 38) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 - 38) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 - 38) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((px == 110 - 44) && (py > 180 - 53) && (py < 180 + 278)) ||
			((px == 600 - 44) && (py > 0) && (py < 20 + 278)) ||
			((px == 900 - 44) && (py > 420 - 53) && (py < 420 + 95)) ||
			((px == 350 - 44) && (py > 710 - 53) && (py < 710 + 95)) ||
			((px == 1090 - 44) && (py > 610 - 53) && (py < 610 + 278)))) {
			return true;
		}
		else return false;
	}
	return false;
}

bool battle::if_enemytouchup_block(QListView*& enemy, int flag)
{
	if (flag == 1) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((py == 180 + 278) && (px > 110 - 38) && (px < 110 + 91)) ||
			((py == 20 + 278) && (px > 600 - 38) && (px < 600 + 91)) ||
			((py == 420 + 95) && (px > 900 - 38) && (px < 900 + 190)) ||
			((py == 710 + 95) && (px > 350 - 38) && (px < 350 + 190)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((py == 180 + 278) && (px > 110 - 44) && (px < 110 + 91)) ||
			((py == 20 + 278) && (px > 600 - 44) && (px < 600 + 91)) ||
			((py == 420 + 95) && (px > 900 - 44) && (px < 900 + 190)) ||
			((py == 710 + 95) && (px > 350 - 44) && (px < 350 + 190)))) {
			return true;
		}
		else return false;
	}
	return false;
}

bool battle::if_enemytouchdown_block(QListView*& enemy, int flag)
{
	if (flag == 1) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((py == 180 - 53) && (px > 110 - 38) && (px < 110 + 91)) ||
			((py == 20 - 53) && (px > 600 - 38) && (px < 600 + 91)) ||
			((py == 420 - 53) && (px > 900 - 38) && (px < 900 + 190)) ||
			((py == 710 - 53) && (px > 350 - 38) && (px < 350 + 190)) ||
			((py == 610 - 53) && (px > 1090 - 38) && (px < 1090 + 91)))) {
			return true;
		}
		else return false;
	}
	else if (flag == 2) {
		QPoint enemy_pos = enemy->pos();
		int px = enemy_pos.x();
		int py = enemy_pos.y();
		if ((((py == 180 - 53) && (px > 110 - 44) && (px < 110 + 91)) ||
			((py == 20 - 53) && (px > 600 - 44) && (px < 600 + 91)) ||
			((py == 420 - 53) && (px > 900 - 44) && (px < 900 + 190)) ||
			((py == 710 - 53) && (px > 350 - 44) && (px < 350 + 190)) ||
			((py == 610 - 53) && (px > 1090 - 44) && (px < 1090 + 91)))) {
			return true;
		}
		else return false;
	}
	return false;
}


void battle::move_player(int flag, int a, int b)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		QPoint player1_hp_pos = ui->player1_hp->pos();
		ui->player1->move(player1_pos.x() + a, player1_pos.y() + b);
		ui->player1_hp->move(player1_hp_pos.x() + a, player1_hp_pos.y() + b);
	}
	else if (flag == 2) {
		QPoint player1_pos = ui->player2->pos();
		QPoint player1_hp_pos = ui->player2_hp->pos();
		ui->player2->move(player1_pos.x() + a, player1_pos.y() + b);
		ui->player2_hp->move(player1_hp_pos.x() + a, player1_hp_pos.y() + b);
	}
}

void battle::move_enemy(QListView*& enemy,QProgressBar*& enemy_hp, int a, int b)
{
	QPoint enemy_pos = enemy->pos();
	QPoint enemy_hp_pos = enemy_hp->pos();
	enemy->move(enemy_pos.x() + a, enemy_pos.y() + b);
	enemy_hp->move(enemy_hp_pos.x() + a, enemy_hp_pos.y() + b);
}

void battle::move_enemy_close(int flag)
{
	time11->start(10);
	connect(time11, SIGNAL(timeout()), this, SLOT(get_pos()));
	for (std::vector<names>::iterator it = name_enemy_close.begin(); it != name_enemy_close.end(); it++) {
		QPoint enemy_pos = it->name->pos();
		if (flag == 1) {
			int a;
			int b;
			if (enemy_pos.x() > player1_pos.x()) {
				a = -enemy_close_->get_Speed();
			}
			else if (enemy_pos.x() == player1_pos.x()) {
				a = 0;
			}
			else {
				a = enemy_close_->get_Speed();
			}
			if (enemy_pos.y() > player1_pos.y()) {
				b = -enemy_close_->get_Speed();
			}
			else if (enemy_pos.y() == player1_pos.y()) {
				b = 0;
			}
			else {
				b = enemy_close_->get_Speed();
			}
			if (a != 0 || b != 0) {
				if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1) {
					for (int i = 0; i < qAbs(b); i++) {
						if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1)
							move_enemy(it->name, it->name_hp, 0, b / qAbs(b));
					}
				}
				else if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1) {
					for (int i = 0; i < qAbs(a); i++) {
						if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1)
							move_enemy(it->name, it->name_hp, a / qAbs(a), 0);
					}
				}
				else {
					if (a == 0) {
						for (int i = 0; i < qAbs(b); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, 0, b / qAbs(b));
						}
					}
					else if (b == 0) {
						for (int i = 0; i < qAbs(a); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, a / qAbs(a), 0);
						}
					}
					else {
						for (int i = 0; i < qAbs(a); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, a / qAbs(a), b / qAbs(b));
						}
					}
				}

			}
			else {
				if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1) {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouch_block(it->name, 1) || if_enemytouchright_block(it->name, 1))
							move_enemy(it->name, it->name_hp, 0, 1);
						else break;
					}
				}
				else if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1) {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouchup_block(it->name, 1) || if_enemytouchdown_block(it->name, 1))
							move_enemy(it->name, it->name_hp, 1, 0);
						else break;
					}
				}
				else {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
							move_enemy(it->name, it->name_hp, 1, 1);
						else break;
					}
				}
			}
		}
		else if (flag == 2) {
			int a;
			int b;
			QPoint player2_pos = ui->player2->pos();
			if (enemy_pos.x() > player2_pos.x()) {
				a = -enemy_close_->get_Speed();
			}
			else if (enemy_pos.x() == player2_pos.x()) {
				a = 0;
			}
			else {
				a = enemy_close_->get_Speed();
			}
			if (enemy_pos.y() > player2_pos.y()) {
				b = -enemy_close_->get_Speed();
			}
			else if (enemy_pos.y() == player2_pos.y()) {
				b = 0;
			}
			else {
				b = enemy_close_->get_Speed();
			}
			if (a != 0 || b != 0) {
				if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1) {
					for (int i = 0; i < qAbs(b); i++) {
						if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1)
							move_enemy(it->name, it->name_hp, 0, b / qAbs(b));
					}
				}
				else if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1) {
					for (int i = 0; i < qAbs(a); i++) {
						if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1)
							move_enemy(it->name, it->name_hp, a / qAbs(a), 0);
					}
				}
				else {
					if (a == 0) {
						for (int i = 0; i < qAbs(b); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, 0, b / qAbs(b));
						}
					}
					else if (b == 0) {
						for (int i = 0; i < qAbs(a); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, a / qAbs(a), 0);
						}
					}
					else {
						for (int i = 0; i < qAbs(a); i++) {
							if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
								move_enemy(it->name, it->name_hp, a / qAbs(a), b / qAbs(b));
						}
					}
				}

			}
			else {
				if (if_enemytouch_block(it->name, 1) == 1 || if_enemytouchright_block(it->name, 1) == 1) {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouch_block(it->name, 1) || if_enemytouchright_block(it->name, 1))
							move_enemy(it->name, it->name_hp, 0, 1);
						else break;
					}
				}
				else if (if_enemytouchup_block(it->name, 1) == 1 || if_enemytouchdown_block(it->name, 1) == 1) {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouchup_block(it->name, 1) || if_enemytouchdown_block(it->name, 1))
							move_enemy(it->name, it->name_hp, 1, 0);
						else break;
					}
				}
				else {
					for (int i = 0; i < enemy_close_->get_Speed(); i++) {
						if (if_enemytouch_block(it->name, 1) == 0 && if_enemytouchright_block(it->name, 1) == 0 && if_enemytouchup_block(it->name, 1) == 0 && if_enemytouchdown_block(it->name, 1) == 0)
							move_enemy(it->name, it->name_hp, 1, 1);
						else break;
					}
				}
			}
		}
	}
}

void battle::move_enemy_far(int speed)
{
	for (std::vector<names_far>::iterator it = name_enemy_far.begin(); it != name_enemy_far.end(); it++) {
		QPoint enemy_pos = it->name->pos();
		QPoint enemy_hp_pos = it->name_hp->pos();
		if (it->edge == 1) {
			if (it->dir == 0) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, 0, 1);
					if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
						it->dir = 1;
						break;
					}
				}
				if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
					it->dir = 1;
				}
			}
			else if (it->dir == 1) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, 0, -1);
					if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
						it->dir = 0;
						break;
					}
				}
				if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
					it->dir = 0;
				}
			}
		}
		else if (it->edge == 2) {
			if (it->dir == 0) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, 0, 1);
					if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
						it->dir = 1;
						break;
					}
				}
				if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
					it->dir = 1;
				}
			}
			else if (it->dir == 1) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, 0, -1);
					if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
						it->dir = 0;
						break;
					}
				}
				if (if_enemy_touchup_side(it->name) || if_enemy_touchdown_side(it->name)) {
					it->dir = 0;
				}
			}
		}
		else if (it->edge == 3) {
			if (it->dir == 0) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, 1,0);
					if (if_enemy_touchleft_side(it->name) || if_enemy_touchright_side(it->name)) {
						it->dir = 1;
						break;
					}
				}
				if (if_enemy_touchleft_side(it->name) || if_enemy_touchright_side(it->name)) {
					it->dir = 1;
				}
			}
			else if (it->dir == 1) {
				for (int i = 0; i < speed; i++) {
					move_enemy(it->name, it->name_hp, -1,0);
					if (if_enemy_touchleft_side(it->name) || if_enemy_touchright_side(it->name)) {
						it->dir = 0;
						break;
					}
				}
				if (if_enemy_touchleft_side(it->name) || if_enemy_touchright_side(it->name)) {
					it->dir = 0;
				}
			}
		}
	}
}


bool battle::enemy_far_touchedgey(QPoint &enemy_pos)
{
	if (enemy_pos.y() < enemy_far_->get_Speed() || enemy_pos.y() > 900 - 53 - enemy_far_->get_Speed()) return true;
	return false;
}

bool battle::enemy_far_touchedgex(QPoint& enemy_pos)
{
	if (enemy_pos.x() < enemy_far_->get_Speed() || enemy_pos.x() > 1280 - 44 - enemy_far_->get_Speed()) return true;
	return false;
}

bool battle::player_touchleft_side(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		if (player1_pos.x() ==0) return true;
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		if (player2_pos.x() ==0) return true;
		else return false;
	}
}

bool battle::player_touchright_side(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		if ((player1_pos.x()==1280-39)) return true;
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		if ((player2_pos.x() == 1280 - 45 )) return true;
		else return false;
	}
}

bool battle::player_touchup_side(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		if (player1_pos.y() == 0) return true;
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		if (player2_pos.y()==0) return true;
		else return false;
	}
}

bool battle::player_touchdown_side(int flag)
{
	if (flag == 1) {
		QPoint player1_pos = ui->player1->pos();
		if ((player1_pos.y() == 900 - 53)) return true;
		else return false;
	}
	else if (flag == 2) {
		QPoint player2_pos = ui->player2->pos();
		if ((player2_pos.y() == 900-53)) return true;
		else return false;
	}
}

void battle::player_move(int flag, QKeyEvent* event,Player *player_)
{
	int speed = player_->get_speed();
	if (flag == 1) {
		QPoint player1_posi = ui->player1->pos();
		int x = player1_posi.x();
		int y = player1_posi.y();
		if (event->key() == Qt::Key_A) {
			if (if_touch_block(1) == 0 && player_touchleft_side(1) == 0) {
				for (int i = 0; i < speed; i++) {
					if (if_touch_block(1) == 0 && player_touchleft_side(1) == 0)
						move_player(1, -1, 0);
					else break;
				}
			}
		}
		else if (event->key() == Qt::Key_D) {
			for (int i = 0; i < speed; i++) {
				if (if_touchright_block(1) == 0 && player_touchright_side(1) == 0)
					move_player(1, 1, 0);
				else break;
			}
		}
		else if (event->key() == Qt::Key_W) {
			for (int i = 0; i < speed; i++) {
				if (if_touchup_block(1) == 0 && player_touchup_side(1) == 0)
					move_player(1, 0, -1);
				else break;
			}
		}
		else if (event->key() == Qt::Key_S) {
			for (int i = 0; i < speed; i++) {
				if (if_touchdown_block(1) == 0 && player_touchdown_side(1) == 0)
					move_player(1, 0, 1);
				else break;
			}
		}
	}
	else if (flag == 2) {
		QPoint player2_posi = ui->player2->pos();
		int x = player2_posi.x();
		int y = player2_posi.y();
		if (event->key() == Qt::Key_A) {
			for (int i = 0; i < speed; i++) {
				if (if_touch_block(2) == 0 && player_touchleft_side(2) == 0)
					move_player(2, -1, 0);
				else break;
			}
		}
		else if (event->key() == Qt::Key_D) {
			for (int i = 0; i < speed; i++) {
				if (if_touchright_block(2) == 0 && player_touchright_side(2) == 0)
					move_player(2, 1, 0);
				else break;
			}
		}
		else if (event->key() == Qt::Key_W) {
			for (int i = 0; i < speed; i++) {
				if (if_touchup_block(2) == 0 && player_touchup_side(2) == 0)
					move_player(2, 0, -1);
				else break;
			}
		}
		else if (event->key() == Qt::Key_S) {
			for (int i = 0; i < speed; i++) {
				if (if_touchdown_block(2) == 0 && player_touchdown_side(2) == 0)
					move_player(2, 0, 1);
				else break;
			}
		}
	}
}

int battle::Random_num(int size)
{
	srand(time(0));
	std::random_device rd;
	int num = rd() % size;
	return num;
}

void battle::enemy_close_attack(int flag)
{
	if (flag == 1) {
		QPoint player_pos = ui->player1->pos();
		for (std::vector<names>::iterator it = name_enemy_close.begin(); it != name_enemy_close.end(); it++) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(enemy_close_->get_attack_range(),2)) {
				int temp = ui->player1_hp->value();
				if (temp - enemy_close_->get_Attack_power() > 0) {
					ui->player1_hp->setValue(temp - enemy_close_->get_Attack_power());
					ui->player1_hp->update();
				}
				else {
					ui->player1_hp->setValue(0);
					ui->player1_hp->update();
				}
			}
			int temp1 = ui->player1_hp->value();
			if (temp1 == 0) {
				game_over();
			}
		}
	}
	else if (flag == 2) {
		QPoint player_pos = ui->player2->pos();
		for (std::vector<names>::iterator it = name_enemy_close.begin(); it != name_enemy_close.end(); it++) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(enemy_close_->get_attack_range(), 2)) {
				int temp = ui->player2_hp->value();
				ui->player2_hp->setValue(temp - enemy_close_->get_Attack_power());
				ui->player2_hp->update();
			}
			int temp1 = ui->player2_hp->value();
			if (temp1 == 0) {
				game_over();
			}
		}
	}
}

void battle::enemy_far_attack(int flag)
{
	if (flag == 1) {
		QPoint player_pos = ui->player1->pos();
		for (std::vector<names_far>::iterator it = name_enemy_far.begin(); it != name_enemy_far.end(); it++) {
			QPoint enemy_pos = it->name->pos();
			if (qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2) <= qPow(enemy_far_->get_attack_range(), 2)) {
				int temp = ui->player1_hp->value();
				ui->player1_hp->setValue(temp - enemy_far_->get_Attack_power());
				ui->player1_hp->update();
			}
			int temp1 = ui->player1_hp->value();
			if (temp1 == 0) {
				game_over();
			}
		}
	}
	else if (flag == 2) {
		QPoint player_pos = ui->player2->pos();
		for (std::vector<names_far>::iterator it = name_enemy_far.begin(); it != name_enemy_far.end(); it++) {
			QPoint enemy_pos = it->name->pos();
			if (qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2) <= qPow(enemy_far_->get_attack_range(), 2)) {
				int temp = ui->player2_hp->value();
				ui->player2_hp->setValue(temp - enemy_far_->get_Attack_power());
				ui->player2_hp->update();
			}
			int temp1 = ui->player2_hp->value();
			if (temp1 == 0) {
				game_over();
			}
		}
	}
}

void battle::player_close_attack(int flag)
{
	int num11 = 1;
	int num22 = 1;
	int num33 = 1;
	if (flag == 1) {
		QPoint player_pos = ui->player1->pos();
		for (std::vector<names>::iterator it = name_enemy_close.begin(); it != name_enemy_close.end();) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(10*player_->get_attack_range(),2)) {
				int temp = it->name_hp->value();
				if (temp - player_->get_attack_power() > 0) {
					it->name_hp->setValue(temp - player_->get_attack_power());
				}
				else it->name_hp->setValue(0);
				it->name_hp->update();
			}
			int temp1 = it->name_hp->value();
			if (temp1 == 0) {
				int num1 = Random_num(10000);
				int num2 = Random_num(10000);
				if (num1 % 5 == 1 || num1 % 5 == 3) {
					if (num2 % 6 == 0 || num2 % 6 == 5) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_exp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_exp0 = new QListView;
						drop_exp0 = it->name;
						drop_exps.push_back(drop_exp0);
						drop_exp0->show();
						QString name1 = QString("drop_exp" + QString::number(num11));
						drop_exp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num11++;
					}
					else if (num2 % 6 == 1 || num2 % 6 == 4) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_hp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_hp0 = new QListView;
						drop_hp0 = it->name;
						drop_hp0->show();
						drop_hps.push_back(drop_hp0);
						QString name1 = QString("drop_hp" + QString::number(num22));
						drop_hp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num22++;
					}
					else {
						it->name->resize(40, 32);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_coin.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_coin0 = new QListView;
						drop_coin0 = it->name;
						drop_coin0->show();
						drop_coins.push_back(drop_coin0);
						QString name1 = QString("drop_coin" + QString::number(num33));
						drop_coin0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num33++;
					}
				}
			}
			else it++;
		}
		for (std::vector<names_far>::iterator it = name_enemy_far.begin(); it != name_enemy_far.end(); ) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(10 * player_->get_attack_range(), 2)) {
				int temp = it->name_hp->value();
				if (temp - player_->get_attack_power() > 0) {
					it->name_hp->setValue(temp - player_->get_attack_power());
				}
				else it->name_hp->setValue(0);
				it->name_hp->update();
			}
			int temp2 = it->name_hp->value();
			if (temp2 == 0) {
				int num1 = Random_num(10000);
				int num2 = Random_num(10000);
				if (num1 % 5 == 1 || num1 % 5 == 3) {
					if (num2 % 6 == 0 || num2 % 6 == 5) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_exp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_exp0 = new QListView;
						drop_exp0 = it->name;
						drop_exps.push_back(drop_exp0);
						drop_exp0->show();
						QString name1 = QString("drop_exp" + QString::number(num11));
						drop_exp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num11++;
					}
					else if (num2 % 6 == 1 || num2 % 6 == 4) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_hp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_hp0 = new QListView;
						drop_hp0 = it->name;
						drop_hp0->show();
						drop_hps.push_back(drop_hp0);
						QString name1 = QString("drop_hp" + QString::number(num22));
						drop_hp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num22++;
					}
					else {
						it->name->resize(40, 32);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_coin.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_coin0 = new QListView;
						drop_coin0 = it->name;
						drop_coin0->show();
						drop_coins.push_back(drop_coin0);
						QString name1 = QString("drop_coin" + QString::number(num33));
						drop_coin0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num33++;
					}
				}
			}
			else it++;
		}
	}
	else if (flag == 2) {
		QPoint player_pos = ui->player2->pos();
		for (std::vector<names>::iterator it = name_enemy_close.begin(); it != name_enemy_close.end();) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(10*player_->get_attack_range(), 2)) {
				int temp = it->name_hp->value();
				if (temp - player_->get_attack_power() > 0) {
					it->name_hp->setValue(temp - player_->get_attack_power());
				}
				else it->name_hp->setValue(0);
				it->name_hp->update();
			}
			int temp3 = it->name_hp->value();
			if (temp3 <= 0) {
				int num1 = Random_num(10000);
				int num2 = Random_num(10000);
				if (num1 % 5 == 1 || num1 % 5 == 3) {
					if (num2 % 6 == 0 || num2 % 6 == 5) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_exp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_exp0 = new QListView;
						drop_exp0 = it->name;
						drop_exps.push_back(drop_exp0);
						drop_exp0->show();
						QString name1 = QString("drop_exp" + QString::number(num11));
						drop_exp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num11++;
					}
					else if (num2 % 6 == 1 || num2 % 6 == 4) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_hp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_hp0 = new QListView;
						drop_hp0 = it->name;
						drop_hp0->show();
						drop_hps.push_back(drop_hp0);
						QString name1 = QString("drop_hp" + QString::number(num22));
						drop_hp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num22++;
					}
					else {
						it->name->resize(40, 32);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_coin.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_coin0 = new QListView;
						drop_coin0 = it->name;
						drop_coin0->show();
						drop_coins.push_back(drop_coin0);
						QString name1 = QString("drop_coin" + QString::number(num33));
						drop_coin0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_close.erase(it);
						num33++;
					}
				}
			}
			else it++;
		}
		for (std::vector<names_far>::iterator it = name_enemy_far.begin(); it != name_enemy_far.end();) {
			QPoint enemy_pos = it->name->pos();
			if ((qPow(player_pos.x() - enemy_pos.x(), 2) + qPow(player_pos.y() - enemy_pos.y(), 2)) <= qPow(10 * player_->get_attack_range(), 2)) {
				int temp = it->name_hp->value();
				if (temp - player_->get_attack_power() > 0) {
					it->name_hp->setValue(temp - player_->get_attack_power());
				}
				else it->name_hp->setValue(0);
				it->name_hp->update();
			}
			int temp4 = it->name_hp->value();
			if (temp4 <= 0) {
				int num1 = Random_num(10000);
				int num2 = Random_num(10000);
				if (num1 % 5 == 1 || num1 % 5 == 3) {
					if (num2 % 6 == 0 || num2 % 6 == 5) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_exp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_exp0 = new QListView;
						drop_exp0 = it->name;
						drop_exps.push_back(drop_exp0);
						drop_exp0->show();
						QString name1 = QString("drop_exp" + QString::number(num11));
						drop_exp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num11++;
					}
					else if (num2 % 6 == 1 || num2 % 6 == 4) {
						it->name->resize(40, 40);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_hp.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_hp0 = new QListView;
						drop_hp0 = it->name;
						drop_hp0->show();
						drop_hps.push_back(drop_hp0);
						QString name1 = QString("drop_hp" + QString::number(num22));
						drop_hp0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num22++;
					}
					else {
						it->name->resize(40, 32);
						QString stylesheet = QString("QListView{background-image:url(:/new/prefix1/remenu/drop_coin.png);background-color:transparent;}");
						it->name->setStyleSheet(stylesheet);
						QListView* drop_coin0 = new QListView;
						drop_coin0 = it->name;
						drop_coin0->show();
						drop_coins.push_back(drop_coin0);
						QString name1 = QString("drop_coin" + QString::number(num33));
						drop_coin0->QObject::setObjectName(name1);
						delete it->name_hp;
						change_exp(50);
						ui->coin_num->display(player_->get_coin() + 20);
						player_->change_coin(20);
						it = name_enemy_far.erase(it);
						num33++;
					}
				}
			}
			else it++;
		}
	}
}


void battle::get_drops()
{
	if (player_->get_playernum() == 1) {
		QPoint player_pos = ui->player1->pos();
		int px = player_pos.x();
		int py = player_pos.y();
		for (std::vector<QListView*>::iterator it = drop_exps.begin(); it != drop_exps.end(); ) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				delete* it;
				change_exp(10);
				it = drop_exps.erase(it);
			}
			else it++;
		}
		for (std::vector<QListView*>::iterator it = drop_hps.begin(); it != drop_hps.end(); ) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				int temp = ui->player1_hp->value();
				int max = ui->player1_hp->maximum();
				if (temp + 100 > max) {
					ui->player1_hp->setValue(max);
				}
				else {
					ui->player1_hp->setValue(temp + 100);
				}
				delete* it;
				it = drop_hps.erase(it);
			}
			else it++;
		}
		for (std::vector<QListView*>::iterator it = drop_coins.begin(); it != drop_coins.end();) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				delete* it;
				player_->change_coin(50);
				ui->coin_num->display(player_->get_coin());
				it = drop_coins.erase(it);
			}
			else it++;
		}
	}
	else if (player_->get_playernum() == 2) {
		QPoint player_pos = ui->player2->pos();
		int px = player_pos.x();
		int py = player_pos.y();
		for (std::vector<QListView*>::iterator it = drop_exps.begin(); it != drop_exps.end();) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				delete* it;
				change_exp(10);
				it = drop_exps.erase(it);
			}
			else it++;
		}
		for (std::vector<QListView*>::iterator it = drop_hps.begin(); it != drop_hps.end(); ) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				int temp = ui->player1_hp->value();
				int max = ui->player1_hp->maximum();
				if (temp + 100 > max) {
					ui->player1_hp->setValue(max);
				}
				else {
					ui->player1_hp->setValue(temp + 100);
				}
				delete* it;
				it = drop_hps.erase(it);
			}
			else it++;
		}
		for (std::vector<QListView*>::iterator it = drop_coins.begin(); it != drop_coins.end(); ) {
			QPoint drops_pos = (*it)->pos();
			if (qPow(px - drops_pos.x(), 2) + qPow(py - drops_pos.y(), 2) <= qPow(player_->get_get_range() * 20, 2)) {
				delete* it;
				player_->change_coin(50);
				ui->coin_num->display(player_->get_coin());
				it = drop_coins.erase(it);
			}
			else it++;
		}
	}
}

void battle::change_exp(int num)
{
	int maxexp = (player_->get_level()) * 100;
	player_->change_Exp(num);
	if (player_->get_exp() >= maxexp) {
		player_->change_Exp(-maxexp);
		player_->change_Level(1);
		show_upgrade();
		player_->change_coin_get(1);
		enemy_close_->change_attack_range(1);
		enemy_far_->change_attack_range(10);
	}
	ui->exp_num->display(player_->get_exp());
	ui->level_num->display(player_->get_level());
}

void battle::show_upgrade()
{
	time_stop();
	ui->upgrade->show();
	int num = Random_num(10000);
	int flag = num % 7;
	int flag1 = 0;
	int flag2 = 0;
	QTextCursor cursor = ui->up1->textCursor();
	ui->up1->setText(select(flag));
	ui->up1->selectAll();
	ui->up1->setAlignment(Qt::AlignCenter);
	ui->up1->setTextCursor(cursor);
	while (1) {
		int num1 = Random_num(10000);
		if (num1 % 7 != flag) {
			flag1 = num1 % 7;
			QTextCursor cursor = ui->up2->textCursor();
			ui->up2->setText(select(flag1));
			ui->up2->selectAll();
			ui->up2->setAlignment(Qt::AlignCenter);
			ui->up2->setTextCursor(cursor);
			break;
		}
		else continue;
	}
	while (1) {
		int num2 = Random_num(10000);
		if (num2 % 7 != flag && num2 % 7 != flag1) {
			flag2 = num2 % 7;
			QTextCursor cursor = ui->up3->textCursor();
			ui->up3->setText(select(flag2));
			ui->up3->selectAll();
			ui->up3->setAlignment(Qt::AlignCenter);
			ui->up3->setTextCursor(cursor);
			break;
		}
		else continue;
	}
	nums.push_back(flag);
	nums.push_back(flag1);
	nums.push_back(flag2);
}
QString battle::select(int num)
{
	QString stylesheet1 = QString("\n\nATK\n\n""+5");
	QString stylesheet2 = QString("\n\nATK_RANGE\n\n""+5");
	QString stylesheet3 = QString("\n\nDURATION\n\n""+0.5");
	QString stylesheet4 = QString("\n\nCOOL_TIME\n\n""-0.5");
	QString stylesheet5 = QString("\n\nHP\n\n""+100");
	QString stylesheet6 = QString("\n\nGET_RANGE\n\n""+1");
	QString stylesheet0 = QString("\n\nSPEED\n\n""+1");
	switch (num)
	{
	case 1:
		return stylesheet1;
	case 2:
		return stylesheet2;
	case 3:
		return stylesheet3;
	case 4:
		return stylesheet4;
	case 5:
		return stylesheet5;
	case 6:
		return stylesheet6;
	case 0:
		return stylesheet0;
	default:
		break;
	}
}
void battle::change_coin()
{
	time4 = new QTimer(this);
	time4->start(10000);
	connect(time4, &QTimer::timeout, [=]() {
		player_->change_coin(player_->get_coin_get());
		ui->coin_num->display(player_->get_coin());
		});
}

void battle::time_start()
{
	timer->start();
	time0->start();
	time1->start();
	time2->start();
	time3->start();
	time4->start();
	time_enemy_close->start();
	time_enemy_far->start();
}


bool battle::if_enemy_touchup_side(QListView* &enemy_far)
{
	QPoint enemy_far_pos = enemy_far->pos();
	if (enemy_far_pos.y() ==0) {
		return true;
	}
	return false;
}

void battle::time_stop()
{
	timer->stop();
	time0->stop();
	time1->stop();
	time2->stop();
	time3->stop();
	time4->stop();
	time_enemy_close->stop();
	time_enemy_far->stop();
}

bool battle::if_enemy_touchdown_side(QListView*& enemy_far)
{
	QPoint enemy_far_pos = enemy_far->pos();
	if (enemy_far_pos.y() == 900-53) {
		return true;
	}
	return false;
}

bool battle::if_enemy_touchleft_side(QListView*& enemy_far)
{
	QPoint enemy_far_pos = enemy_far->pos();
	if (enemy_far_pos.x() ==0) {
		return true;
	}
	return false;
}

std::string battle::changetostring_int(const int &temp)
{
	QString temp1 = QString::number(temp);
	std::string str = temp1.toStdString();
	return str;
}

bool battle::if_enemy_touchright_side(QListView*& enemy_far)
{
	QPoint enemy_far_pos = enemy_far->pos();
	if (enemy_far_pos.x() == 1280-44) {
		return true;
	}
	return false;
}

void battle::save_game( Player*& player_, Enemy*& enemy_close_, Enemy*& enemy_far_)
{
	std::ofstream store_file("D:\\survivor_game-ÇØºÆéª-221900460\\sur\\file_temp.txt", std::ios::out);
	if (!store_file.is_open()) {
		exit(-1);
	}
	std::string player_file;
	std::string enemyclose_file;
	std::string enemyfar_file;
	player_file = "player\n"+changetostring_int(player_->get_playernum()) + "\n" + changetostring_int(player_->get_hp1()) + "\n" + changetostring_int(player_->get_hp2()) + "\n" + changetostring_int(player_->get_Hp())
		+ "\n" + changetostring_int(player_->get_attack_power()) + "\n" + changetostring_int(player_->get_speed()) +"\n" + changetostring_int(player_->get_get_range()) + "\n" + changetostring_int(player_->get_attack_range())
		+ "\n" + changetostring_float(player_->get_duration()) + "\n" + changetostring_float(player_->get_cool()) + "\n" + changetostring_int(player_->get_exp()) + "\n" + changetostring_int(player_->get_level()) + "\n" + changetostring_int(player_->get_coin())
		+ "\n" + changetostring_int(player_->get_coin_get()) + "\n" + changetostring_int(player_->get_reborn());
	enemyclose_file = "enemyclose\n"+changetostring_int(enemy_close_->get_Hp()) + "\n" + changetostring_int(enemy_close_->get_Attack_power()) + "\n" + changetostring_int(enemy_close_->get_Speed()) + "\n" + changetostring_int(enemy_close_->get_attack_range());
	enemyfar_file = "enemyfar\n"+changetostring_int(enemy_far_->get_Hp()) + "\n" + changetostring_int(enemy_far_->get_Attack_power()) + "\n" + changetostring_int(enemy_far_->get_Speed()) + "\n" + changetostring_int(enemy_far_->get_attack_range());
	store_file << player_file << std::endl;
	store_file << enemyclose_file << std::endl;
	store_file << enemyfar_file << std::endl;
	store_file.close();
}

std::string battle::changetostring_float(const float &temp)
{
	QString temp1;
	int a = (int)temp;
	float b = temp - a;
	if (b == 0.5) {
		temp1 = QString::number(a) + ".5";
	}
	else {
		temp1 = QString::number(a) + ".0";
	}
	std::string str = temp1.toStdString();
	return str;
}


void battle::upgrade1() {
	int num = nums[nums.size() - 3];
	switch (num)
	{
	case 0:
		player_->change_Speed(1);
		break;
	case 1:
		player_->change_Attack_power(5);
		break;
	case 2:
		player_->change_range_attack(5);
		break;
	case 3:
		player_->change_duration(0.5);
		break;
	case 4:
		player_->change_cooling_time(-0.5);
		break;
	case 5:
		if (player_->get_playernum() == 1) {
			int temp = ui->player1_hp->value();
			ui->player1_hp->setValue(temp + 100);
			ui->player1_hp->update();
		}
		else if (player_->get_playernum() == 2) {
			int temp = ui->player2_hp->value();
			ui->player2_hp->setValue(temp + 100);
			ui->player2_hp->update();
		}
		break;
	case 6:
		player_->change_get_range(1);
		break;
	default:
		break;
	}
	ui->upgrade->hide();
	time_start();
}

void battle::game_over()
{
	time_stop();
	ui->overpage->show();
	ui->stop->setEnabled(false);
	ui->btn2->setEnabled(true);
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:12pt 'Century';}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font:12pt 'Century';}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font:12pt 'Century';}");
	QString stylesheet0 = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font:12pt 'Century';}");
	ui->btn->setStyleSheet(stylesheet);
	if (player_->get_reborn() > 0) {
		ui->btn2->setStyleSheet(stylesheet);
		ui->btn2->setEnabled(true);
		QString text1 = QString("You have " + QString::number(player_->get_reborn()) + " times to reborn!");
		ui->times->setText(text1);
	}
	else {
		ui->btn2->setStyleSheet(stylesheet0);
		ui->btn2->setEnabled(false);
		QString text12 = QString("You have 0 times to upgrade!");
		ui->times->setText(text12);
	}
	QString stylesheet2 = QString("QTextEdit{background-color:transparent; font:40pt 'Century'; color:rgb(255, 0, 0); }");
	QString stylesheet3 = QString("QTextEdit{background-color:transparent; font:14pt 'Century'; color:rgb(0, 255, 0); }");
	ui->game_over->setStyleSheet(stylesheet2);
	ui->game_over->setAlignment(Qt::AlignHCenter);
	ui->game_over->setAlignment(Qt::AlignCenter);
	ui->times->setStyleSheet(stylesheet3);
	ui->times->setAlignment(Qt::AlignCenter);
}

void battle::upgrade2() {
	int num = nums[nums.size() - 2];
	switch (num)
	{
	case 0:
		player_->change_Speed(1);
		break;
	case 1:
		player_->change_Attack_power(5);
		break;
	case 2:
		player_->change_range_attack(5);
		break;
	case 3:
		player_->change_duration(0.5);
		break;
	case 4:
		player_->change_cooling_time(-0.5);
		break;
	case 5:
		if (player_->get_playernum() == 1) {
			int temp = ui->player1_hp->value();
			ui->player1_hp->setValue(temp + 100);
			ui->player1_hp->update();
		}
		else if (player_->get_playernum() == 2) {
			int temp = ui->player2_hp->value();
			ui->player2_hp->setValue(temp + 100);
			ui->player2_hp->update();
		}
		break;
	case 6:
		player_->change_get_range(1);
		break;
	default:
		break;
	}
	ui->upgrade->hide();
	time_start();
}

void battle::upgrade3() {
	int num = nums[nums.size() - 1];
	switch (num)
	{
	case 0:
		player_->change_Speed(1);
		break;
	case 1:
		player_->change_Attack_power(5);
		break;
	case 2:
		player_->change_range_attack(5);
		break;
	case 3:
		player_->change_duration(0.5);
		break;
	case 4:
		player_->change_cooling_time(-0.5);
		break;
	case 5:
		if (player_->get_playernum() == 1) {
			int temp = ui->player1_hp->value();
			ui->player1_hp->setValue(temp + 100);
			ui->player1_hp->update();
		}
		else if (player_->get_playernum() == 2) {
			int temp = ui->player2_hp->value();
			ui->player2_hp->setValue(temp + 100);
			ui->player2_hp->update();
		}
		break;
	case 6:
		player_->change_get_range(1);
		break;
	default:
		break;
	}
	ui->upgrade->hide();
	time_start();
}

void battle::get_pos()
{
	if (player_->get_playernum() == 1) {
		player1_pos = ui->player1->pos();
	}
	else if (player_->get_playernum() == 2) {
		player2_pos = ui->player2->pos();
	}
}

void battle::reborn_page()
{
	if (player_->get_playernum() == 1) {
		ui->player1_hp->setValue(player_->get_Hp());
		ui->player1_hp->setMaximum(player_->get_Hp());
		QPoint player_pos = ui->player1->pos();
		int a = 610 - player_pos.x();
		int b = 520 - player_pos.y();
		move_player(1, a, b);
		player_->change_reborn(-1);
	}
	else if (player_->get_playernum() == 2) {
		ui->player2_hp->setValue(player_->get_Hp());
		ui->player2_hp->setMaximum(player_->get_Hp());
		QPoint player_pos = ui->player2->pos();
		int a = 610 - player_pos.x();
		int b = 520 - player_pos.y();
		move_player(2, a, b);
		player_->change_reborn(-1);
	}
	setFocus();
	ui->overpage->hide();
	time_start();
	ui->stop->setEnabled(true);
	ui->btn2->setEnabled(false);
}

void battle::backtomenupage2()
{
	emit siga2();
	time_stop();
}

void battle::save()
{
	save_game(player_, enemy_close_, enemy_far_);
}

void battle::backtomenupage1()
{
	emit siga1();
	time_stop();
}
