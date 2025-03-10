#pragma once

#include <QtWidgets/QWidget>
#include "ui_sur.h"
#include"menupage.h"

class sur : public QWidget
{
    Q_OBJECT

public:
    sur(QWidget *parent = nullptr);
    ~sur();
    Player* player_continue;
    Enemy* enemyclose_continue;
    Enemy* enemyfar_continue;
    menupage sub;
    player1_menu* onecontinue;
    player2_menu* twocontinue;
    int stringtoint(std::string temp);
    float stringtofloat(std::string temp);
    void continue_game();

private:
    Ui::surClass ui;
private slots:
    void tomenupage();
    void tosur();
    void toplayermenu1();
    void toplayermenu2();
};
