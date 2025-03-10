#pragma once

#include <QWidget>
#include "ui_store.h"
#include"player.h"
#include"enemy.h"
#include<vector>

QT_BEGIN_NAMESPACE
namespace Ui { class storeClass; };
QT_END_NAMESPACE

class store : public QWidget
{
	Q_OBJECT

public:
	Ui::storeClass* ui;
	store(QWidget *parent = nullptr);
	~store();
	void closeEvent(QCloseEvent* event1);
	Player* player_upgrade;
	Enemy* enemy_close1;
	Enemy* enemy_far1;
	int set_price(QLCDNumber*& prices,int flag);
	bool if_affordable(int flag);
	void set_color(int flag);
	void set_text();
	void set_colors();
	void set_prices();
	void save();
	void set_levels();
	std::string changetostring_int(const int& temp);
	std::string changetostring_float(const float& temp);
	void save_game(Player*& player_, Enemy*& enemy_close_, Enemy*& enemy_far_);

private:
	std::vector<int> levels;

private slots:
	void change();
	void change2();
	void up1();
	void up2();
	void up3();
	void up4();
	void up5();
	void up6();
	void up7();
	void up8();
	void up9();
	void up10();

signals:
	void sig();
	void sig2();
};
