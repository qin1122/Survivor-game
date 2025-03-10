#pragma once

#include <QWidget>
#include "ui_player2_menu.h"
#include"store.h"
#include"battle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class player2_menuClass; };
QT_END_NAMESPACE

class player2_menu : public QWidget
{
	Q_OBJECT

public:
	player2_menu(QWidget *parent = nullptr);
	player2_menu(Player*& player, Enemy*& enemyclose, Enemy*& enemyfar, QWidget* parent = nullptr);
	~player2_menu();
	void closeEvent(QCloseEvent* event);
	void save2();
	store twotostore;
	battle *twotobattle;
	Player* player_menu;
	Enemy* enemyclose_menu;
	Enemy* enemyfar_menu;

private:
	Ui::player2_menuClass *ui;

private slots:
	void changeslot2();
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
	void sig2();
};
