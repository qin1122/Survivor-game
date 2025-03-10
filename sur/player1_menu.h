#pragma once

#include <QWidget>
#include "ui_player1_menu.h"
#include"store.h"
#include"battle.h"
#include"player.h"
#include<vector>

QT_BEGIN_NAMESPACE
namespace Ui { class player1_menuClass; };
QT_END_NAMESPACE



class player1_menu : public QWidget
{
	Q_OBJECT

public:
	player1_menu(QWidget *parent = nullptr);
	player1_menu(Player*& player,Enemy*& enemyclose,Enemy*& enemyfar,QWidget* parent = nullptr);
	~player1_menu();
	void closeEvent(QCloseEvent* event);
	void save1();
	store onetostore;
	battle *onetobattle;
	std::vector<battle> battles;
	Player* player_menu;
	Enemy* enemyclose_menu;
	Enemy* enemyfar_menu;

private:
	Ui::player1_menuClass *ui;
	int num;

private slots:
	void changeslot1();
	void see_weapon();
	void see_necklace();
	void see_gloves();
	void see_chestpate();
	void see_belt();
	void see_boot();
	void see_attribute();
	void tostore();
	void tobattle();
	void toplayer_menu();
	void backtomenu();

signals:
	void sig1();
};
