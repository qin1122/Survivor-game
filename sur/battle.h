#pragma once

#include <QWidget>
#include "ui_battle.h"
#include<QKeyEvent>
#include"player.h"
#include"enemy.h"
#include<Vector>
#include<string>
#include<qmath.h>

QT_BEGIN_NAMESPACE
namespace Ui { class battleClass; };
QT_END_NAMESPACE

struct names {
	QListView* name;
	QProgressBar* name_hp;
};

struct names_far {
	QListView* name;
	QProgressBar* name_hp;
	int edge;//enemy在哪个边缘，1表示左边，2表示右边，3表示下边
	int dir;//移动方向
};


class battle : public QWidget
{
	Q_OBJECT

public:
	Ui::battleClass* ui;
	Player* player_;
	Enemy* enemy_close_;
	Enemy* enemy_far_;
	QPoint player1_pos;
	QPoint player2_pos;
	QTimer* time11;
	QTimer* timer;
	QTimer* time0;
	QTimer* time1;
	QTimer* time2;
	QTimer* time3;
	QTimer* time4;
	QTimer* time_enemy_close;
	QTimer* time_enemy_far;
	QTimer* store;
	std::vector<names> name_enemy_close;
	std::vector<names_far> name_enemy_far;
	std::vector<QListView*> drop_exps;
	std::vector<QListView*> drop_hps;
	std::vector<QListView*> drop_coins;
	std::vector<int> nums;
	int flag;
	battle(int flag, Player*& player_, Enemy*& enemyclose_, Enemy*& enemyfar_, QWidget *parent = nullptr);
	battle(QWidget* parent = nullptr);
	~battle();
	void keyPressEvent(QKeyEvent* event);
	void closeEvent(QCloseEvent* event);
	void set_enemy();
	void set_Hp();
	bool if_touch_block(int flag);
	bool if_touchright_block(int flag);
	bool if_touchup_block(int flag);
	bool if_touchdown_block(int flag);
	bool if_enemytouch_block(QListView*& enemy,int flag);
	bool if_enemytouchright_block(QListView*& enemy,int flag);
	bool if_enemytouchup_block(QListView*& enemy, int flag);
	bool if_enemytouchdown_block(QListView*& enemy, int flag);
	void move_player(int flag, int a, int b);
	void move_enemy(QListView*& enemy, QProgressBar*& enemy_hp, int a, int b);
	void move_enemy_close(int speed);
	void move_enemy_far(int speed);
	bool enemy_far_touchedgey(QPoint& enemy_pos);
	bool enemy_far_touchedgex(QPoint& enemy_pos);
	bool player_touchleft_side(int flag);
	bool player_touchright_side(int flag);
	bool player_touchup_side(int flag);
	bool player_touchdown_side(int flag);
	void player_move(int flag, QKeyEvent* event,Player *player_);
	int Random_num(int size);
	void enemy_close_attack(int flag);
	void enemy_far_attack(int flag);
	void player_close_attack(int flag);
	void get_drops();
	void change_exp(int num);
	void show_upgrade();
	QString select(int num);
	void change_coin();
	bool if_enemy_touchup_side(QListView*& enemy_far);
	bool if_enemy_touchdown_side(QListView*& enemy_far);
	bool if_enemy_touchleft_side(QListView*& enemy_far);
	bool if_enemy_touchright_side(QListView*& enemy_far);
	void game_over();
	void time_start();
	void time_stop();
	std::string changetostring_int(const int &temp);
	std::string changetostring_float(const float &temp);
	void save_game( Player* &player_,Enemy* &enemy_close_, Enemy* &enemy_far_);

private slots:
	void upgrade1();
	void upgrade2();
	void upgrade3();
	void get_pos();
	void backtomenupage1();
	void backtomenupage2();
	void reborn_page();
	void save();
signals:
	void siga1();
	void siga2();
private:
	int kill;
	int expupnum;
};
