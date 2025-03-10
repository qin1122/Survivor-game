#include "store.h"
#include<fstream>
#include<qstring.h>
#include<qtextedit.h>

store::store(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::storeClass())
{
	ui->setupUi(this);
	setFixedSize(1280, 900);
	QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;}");
	ui->back->setStyleSheet(stylesheet);
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(change()));
	QObject::connect(ui->back, SIGNAL(clicked()), this, SLOT(change2()));
	player_upgrade = new Player;
	enemy_close1 = new Enemy;
	enemy_far1 = new Enemy;
	levels = { 1,1,1,1,1,1,1,1,1,1 };
	set_text();
	set_prices();
	set_colors();
	QObject::connect(ui->atk_btn, SIGNAL(clicked()), this, SLOT(up1()));
	QObject::connect(ui->duration_btn, SIGNAL(clicked()), this, SLOT(up2()));
	QObject::connect(ui->cool_btn, SIGNAL(clicked()), this, SLOT(up3()));
	QObject::connect(ui->chestplate_btn, SIGNAL(clicked()), this, SLOT(up4()));
	QObject::connect(ui->belt_btn, SIGNAL(clicked()), this, SLOT(up5()));
	QObject::connect(ui->speed_btn, SIGNAL(clicked()), this, SLOT(up6()));
	QObject::connect(ui->get_range_btn, SIGNAL(clicked()), this, SLOT(up7()));
	QObject::connect(ui->attack_range_btn, SIGNAL(clicked()), this, SLOT(up8()));
	QObject::connect(ui->coin_get_btn, SIGNAL(clicked()), this, SLOT(up9()));
	QObject::connect(ui->reborn_btn, SIGNAL(clicked()), this, SLOT(up10()));
}

store::~store()
{
	delete ui;
	delete player_upgrade;
	levels.clear();
}

void store::change() {
	emit sig();
}

void store::change2() {
	emit sig2();
}

void store::up1()
{
	if (if_affordable(0)) {
		player_upgrade->change_Attack_power(5);
		player_upgrade->change_coin(-*(levels.begin())*100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin()) += 1;
		set_price(ui->atk_, 0);
		set_colors();
		set_text();
	}
}

void store::up2()
{
	if (if_affordable(1)) {
		player_upgrade->change_duration(0.5);
		player_upgrade->change_coin(-*(levels.begin()+1) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 1) += 1;
		set_price(ui->duration_, 1);
		set_colors();
		set_text();
	}
	
}

void store::up3()
{
	if (if_affordable(2)) {
		player_upgrade->change_cooling_time(-0.5);
		player_upgrade->change_coin(-*(levels.begin()+2) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 2) += 1;
		set_price(ui->coo_, 2);
		set_colors();
		set_text();
	}
	
}

void store::up4()
{
	if (if_affordable(3)) {
		player_upgrade->change_hp1(100);
		player_upgrade->change_Hp(100);
		player_upgrade->change_coin(-*(levels.begin()+3) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 3) += 1;
		set_price(ui->chestplate_, 3);
		set_colors();
		set_text();
	}
	
}

void store::up5()
{
	if (if_affordable(4)) {
		player_upgrade->change_hp2(100);
		player_upgrade->change_Hp(100);
		player_upgrade->change_coin(-*(levels.begin()+4) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 4) += 1;
		set_price(ui->belt_, 4);
		set_colors();
		set_text();
	}
	
}

void store::up6()
{
	if (if_affordable(5)) {
		player_upgrade->change_Speed(1);
		player_upgrade->change_coin(-*(levels.begin()+5) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 5) += 1;
		set_price(ui->speed_, 5);
		set_colors();
		set_text();
	}

}

void store::up7()
{
	if (if_affordable(6)) {
		player_upgrade->change_get_range(1);
		player_upgrade->change_coin(-*(levels.begin()+6)* 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 6) += 1;
		set_price(ui->get_range_, 6);
		set_colors();
		set_text();
	}

}

void store::up8()
{
	if (if_affordable(7)) {
		player_upgrade->change_range_attack(5);
		player_upgrade->change_coin(-*(levels.begin()+7) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 7) += 1;
		set_price(ui->attack_range_, 7);
		set_colors();
		set_text();
	}

}

void store::up9()
{
	if (if_affordable(8)) {
		player_upgrade->change_coin_get(1);
		player_upgrade->change_coin(-*(levels.begin()+8) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 8) += 1;
		set_price(ui->coin_get_, 8);
		set_colors();
		set_text();
	}
}

void store::up10()
{
	if (if_affordable(9)) {
		player_upgrade->change_reborn(1);
		player_upgrade->change_coin(-*(levels.begin()+9) * 100);
		ui->coin_num->display(player_upgrade->get_coin());
		ui->coin_num->update();
		*(levels.begin() + 9) += 1;
		set_price(ui->reborn_, 9);
		set_colors();
		set_text();
	}
}

int store::set_price(QLCDNumber*& prices,int flag)
{
	int price = (levels[flag]) * 100;
	prices->display(price);
	prices->update();
	return price;
}

bool store::if_affordable(int flag)
{
	int price =(levels[flag]) * 100;
	if (ui->coin_num->value() >= price) {
		return true;
	}
	else return false;
}

void store::set_color(int flag)
{
	QString stylesheetbtn_red = QString("QPushButton{color:rgba(255,0,0,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(255,0,0,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(255,0,0,200);background-color:transparent;}");
	QString stylesheetbtn_green = QString("QPushButton{color:rgba(0,255,0,100);background-color:transparent;}"
		"QPushButton:hover{color:rgba(0,255,0,200);background-color:transparent;}"
		"QPushButton:pressed{color:rgba(0,255,0,200);background-color:transparent;}");
	QString stylesheetlcd_red = QString("QLCDNumber{color:rgb(255,0,0);}");
	QString stylesheetlcd_green = QString("QLCDNumber{color:rgb(0,255,0);}");
	QString stylesheettext_red = QString("QTextEdit{color:rgba(255,0,0,100);background-color:transparent;}");
	QString stylesheettext_green = QString("QTextEdit{color:rgba(0,255,0,100);background-color:transparent;}");
	switch (flag)
	{
	case 0:
		if (if_affordable(0)) {
			ui->atk_num->setStyleSheet(stylesheettext_green);
			ui->atk_->setStyleSheet(stylesheetlcd_green);
			ui->atk_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->atk_num->setStyleSheet(stylesheettext_red);
			ui->atk_->setStyleSheet(stylesheetlcd_red);
			ui->atk_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 1:
		if (if_affordable(1)) {
			ui->duration_num->setStyleSheet(stylesheettext_green);
			ui->duration_->setStyleSheet(stylesheetlcd_green);
			ui->duration_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->duration_num->setStyleSheet(stylesheettext_red);
			ui->duration_->setStyleSheet(stylesheetlcd_red);
			ui->duration_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 2:
		if (if_affordable(2)) {
			ui->cool_num->setStyleSheet(stylesheettext_green);
			ui->coo_->setStyleSheet(stylesheetlcd_green);
			ui->cool_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->cool_num->setStyleSheet(stylesheettext_red);
			ui->coo_->setStyleSheet(stylesheetlcd_red);
			ui->cool_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 3:
		if (if_affordable(3)) {
			ui->chestplate_num->setStyleSheet(stylesheettext_green);
			ui->chestplate_->setStyleSheet(stylesheetlcd_green);
			ui->chestplate_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->chestplate_num->setStyleSheet(stylesheettext_red);
			ui->chestplate_->setStyleSheet(stylesheetlcd_red);
			ui->chestplate_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 4:
		if (if_affordable(4)) {
			ui->belt_num->setStyleSheet(stylesheettext_green);
			ui->belt_->setStyleSheet(stylesheetlcd_green);
			ui->belt_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->belt_num->setStyleSheet(stylesheettext_red);
			ui->belt_->setStyleSheet(stylesheetlcd_red);
			ui->belt_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 5:
		if (if_affordable(5)) {
			ui->speed_num->setStyleSheet(stylesheettext_green);
			ui->speed_->setStyleSheet(stylesheetlcd_green);
			ui->speed_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->speed_num->setStyleSheet(stylesheettext_red);
			ui->speed_->setStyleSheet(stylesheetlcd_red);
			ui->speed_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 6:
		if (if_affordable(6)) {
			ui->get_range_num->setStyleSheet(stylesheettext_green);
			ui->get_range_->setStyleSheet(stylesheetlcd_green);
			ui->get_range_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->get_range_num->setStyleSheet(stylesheettext_red);
			ui->get_range_->setStyleSheet(stylesheetlcd_red);
			ui->get_range_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 7:
		if (if_affordable(7)) {
		ui->attack_range_num->setStyleSheet(stylesheettext_green);
		ui->attack_range_->setStyleSheet(stylesheetlcd_green);
		ui->attack_range_btn->setStyleSheet(stylesheetbtn_green);
	    }
		else {
		ui->attack_range_num->setStyleSheet(stylesheettext_red);
		ui->attack_range_->setStyleSheet(stylesheetlcd_red);
		ui->attack_range_btn->setStyleSheet(stylesheetbtn_red);
	    }
	case 8:
		if (if_affordable(8)) {
			ui->coin_get_num->setStyleSheet(stylesheettext_green);
			ui->coin_get_->setStyleSheet(stylesheetlcd_green);
			ui->coin_get_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->coin_get_num->setStyleSheet(stylesheettext_red);
			ui->coin_get_->setStyleSheet(stylesheetlcd_red);
			ui->coin_get_btn->setStyleSheet(stylesheetbtn_red);
		}
	case 9:
		if (if_affordable(9)) {
			ui->reborn_num->setStyleSheet(stylesheettext_green);
			ui->reborn_->setStyleSheet(stylesheetlcd_green);
			ui->reborn_btn->setStyleSheet(stylesheetbtn_green);
		}
		else {
			ui->reborn_num->setStyleSheet(stylesheettext_red);
			ui->reborn_->setStyleSheet(stylesheetlcd_red);
			ui->reborn_btn->setStyleSheet(stylesheetbtn_red);
		}
	default:
		break;
	}
}

void store::set_text()
{
	QString atk_text = QString(QString::number(player_upgrade->get_attack_power()) + " (60)");
	QString duration_text = QString(QString::number(player_upgrade->get_duration(), 'g', 2) + " (3)");
	QString cool_text = QString(QString::number(player_upgrade->get_cool(), 'g', 2) + " (0.5)");
	QString chest_text = QString(QString::number(player_upgrade->get_hp1()) + " (2000)");
	QString belt_text = QString(QString::number(player_upgrade->get_hp2()) + " (1000)");
	QString speed_text = QString(QString::number(player_upgrade->get_speed()) + " (10)");
	QString get_range_text = QString(QString::number(player_upgrade->get_get_range()) + " (5)");
	QString attack_range_text = QString(QString::number(player_upgrade->get_attack_range()) + " (30)");
	QString coin_get_text = QString(QString::number(player_upgrade->get_coin_get()) + " (10)");
	QString reborn_text = QString(QString::number(player_upgrade->get_reborn()) + " (10)");
	ui->atk->setText(atk_text);
	ui->atk->setAlignment(Qt::AlignCenter);
	ui->duration->setText(duration_text);
	ui->duration->setAlignment(Qt::AlignCenter);
	ui->cool->setText(cool_text);
	ui->cool->setAlignment(Qt::AlignCenter);
	ui->chestplate->setText(chest_text);
	ui->chestplate->setAlignment(Qt::AlignCenter);
	ui->belt_2->setText(belt_text);
	ui->belt_2->setAlignment(Qt::AlignCenter);
	ui->speed->setText(speed_text);
	ui->speed->setAlignment(Qt::AlignCenter);
	ui->get_range_2->setText(get_range_text);
	ui->get_range_2->setAlignment(Qt::AlignCenter);
	ui->attack_range_2->setText(attack_range_text);
	ui->attack_range_2->setAlignment(Qt::AlignCenter);
	ui->coin_get_2->setText(coin_get_text);
	ui->coin_get_2->setAlignment(Qt::AlignCenter);
	ui->reborn_2->setText(reborn_text);
	ui->reborn_2->setAlignment(Qt::AlignCenter);
}

void store::set_colors()
{
	set_color(0);
	set_color(1);
	set_color(2);
	set_color(3);
	set_color(4);
	set_color(5);
	set_color(6);
	set_color(7);
	set_color(8);
	set_color(9);
}

void store::set_prices()
{
	set_price(ui->atk_, 0);
	set_price(ui->duration_, 1);
	set_price(ui->coo_, 2);
	set_price(ui->chestplate_, 3);
	set_price(ui->belt_, 4);
	set_price(ui->speed_, 5);
	set_price(ui->get_range_, 6);
	set_price(ui->attack_range_, 7);
	set_price(ui->coin_get_, 8);
	set_price(ui->reborn_, 9);
}

void store::closeEvent(QCloseEvent* event1)
{
	save();
}

void store::save()
{
	save_game(player_upgrade, enemy_close1, enemy_far1);
}

void store::set_levels()
{
	if (player_upgrade->get_playernum() == 1) {
		int level1 = (player_upgrade->get_attack_power() - 20) / 5;
		int level2 = (player_upgrade->get_duration() -0.5) / 0.5;
		int level3 = (3-player_upgrade->get_cool()) / 0.5;
		int level4 = (player_upgrade->get_hp1() - 700) / 100;
		int level5 = (player_upgrade->get_hp2() - 300) / 100;
		int level6 = (player_upgrade->get_speed() - 4) / 1;
		int level7 = (player_upgrade->get_get_range() - 1) / 1;
		int level8 = (player_upgrade->get_attack_range() - 5) / 5;
		int level9 = (player_upgrade->get_coin_get() - 1) / 1;
		int level10 = (player_upgrade->get_reborn() - 0) / 1;
		level1++; level2++; level3++; level4++; level5++; level6++; level7++; level8++; level9++; level10++;
		levels[0] = level1;
		levels[1] = level2;
		levels[2] = level3;
		levels[3] = level4;
		levels[4] = level5;
		levels[5] = level6;
		levels[6] = level7;
		levels[7] = level8;
		levels[8] = level9;
		levels[9] = level10;
	}
	else if (player_upgrade->get_playernum() == 2) {
		int level1 = (player_upgrade->get_attack_power() - 25) / 5;
		int level2 = (player_upgrade->get_duration() - 0.5) / 0.5;
		int level3 = (2 - player_upgrade->get_cool()) / 0.5;
		int level4 = (player_upgrade->get_hp1() - 800) / 100;
		int level5 = (player_upgrade->get_hp2() - 400) / 100;
		int level6 = (player_upgrade->get_speed() - 4) / 1;
		int level7 = (player_upgrade->get_get_range() - 1) / 1;
		int level8 = (player_upgrade->get_attack_range() - 5) / 5;
		int level9 = (player_upgrade->get_coin_get() - 1) / 1;
		int level10 = (player_upgrade->get_reborn() - 0) / 1;
		level1++; level2++; level3++; level4++; level5++; level6++; level7++; level8++; level9++; level10++;
		levels[0] = level1;
		levels[1] = level2;
		levels[2] = level3;
		levels[3] = level4;
		levels[4] = level5;
		levels[5] = level6;
		levels[6] = level7;
		levels[7] = level8;
		levels[8] = level9;
		levels[9] = level10;
	}
}

std::string store::changetostring_int(const int& temp)
{
	QString temp1 = QString::number(temp);
	std::string str = temp1.toStdString();
	return str;
}

std::string store::changetostring_float(const float& temp)
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

void store::save_game(Player*& player_, Enemy*& enemy_close_, Enemy*& enemy_far_)
{
	std::ofstream store_file("D:\\survivor_game-ÇØºÆéª-221900460\\sur\\file_temp.txt", std::ios::out);
	if (!store_file.is_open()) {
		exit(-1);
	}
	std::string player_file;
	std::string enemyclose_file;
	std::string enemyfar_file;
	player_file = "player\n" + changetostring_int(player_->get_playernum()) + "\n" + changetostring_int(player_->get_hp1()) + "\n" + changetostring_int(player_->get_hp2()) + "\n" + changetostring_int(player_->get_Hp())
		+ "\n" + changetostring_int(player_->get_attack_power()) + "\n" + changetostring_int(player_->get_speed()) + "\n" + changetostring_int(player_->get_get_range()) + "\n" + changetostring_int(player_->get_attack_range())
		+ "\n" + changetostring_float(player_->get_duration()) + "\n" + changetostring_float(player_->get_cool()) + "\n" + changetostring_int(player_->get_exp()) + "\n" + changetostring_int(player_->get_level()) + "\n" + changetostring_int(player_->get_coin())
		+ "\n" + changetostring_int(player_->get_coin_get()) + "\n" + changetostring_int(player_->get_reborn());
	enemyclose_file = "enemyclose\n" + changetostring_int(enemy_close_->get_Hp()) + "\n" + changetostring_int(enemy_close_->get_Attack_power()) + "\n" + changetostring_int(enemy_close_->get_Speed()) + "\n" + changetostring_int(enemy_close_->get_attack_range());
	enemyfar_file = "enemyfar\n" + changetostring_int(enemy_far_->get_Hp()) + "\n" + changetostring_int(enemy_far_->get_Attack_power()) + "\n" + changetostring_int(enemy_far_->get_Speed()) + "\n" + changetostring_int(enemy_far_->get_attack_range());
	store_file << player_file << std::endl;
	store_file << enemyclose_file << std::endl;
	store_file << enemyfar_file << std::endl;
	store_file.close();
}


