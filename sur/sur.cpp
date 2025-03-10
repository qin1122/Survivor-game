#include "sur.h"
#include<QPushButton>
#include<QString>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

sur::sur(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setFixedSize(1280, 900);
    continue_game();
    player_continue=new Player;
    enemyclose_continue=new Enemy;
    enemyfar_continue=new Enemy;
    QString stylesheet = QString("QPushButton{color:rgba(255,255,255,100);background-color:transparent;font: 11pt \"Century\";}"
        "QPushButton:hover{color:rgba(255,255,255,200);background-color:transparent;font: 11pt \"Century\";}"
        "QPushButton:pressed{color:rgba(255,255,255,200);background-color:transparent;font: 11pt \"Century\";}");
    ui.new_game->setStyleSheet(stylesheet);
    ui.exit->setStyleSheet(stylesheet);
    ui.continue_2->setStyleSheet(stylesheet);
    QObject::connect(ui.continue_2, SIGNAL(clicked()), this, SLOT(continue_game()));
    QObject::connect(&sub, SIGNAL(mysignal()), this, SLOT(tosur()));
    QObject::connect(ui.new_game, SIGNAL(clicked()), this, SLOT(tomenupage()));
}

sur::~sur()
{
    delete player_continue;
    delete enemyclose_continue;
    delete enemyfar_continue;
}

int sur::stringtoint(std::string temp)
{
    QString temp1 = QString::fromStdString(temp);
    return temp1.toInt();
}

float sur::stringtofloat(std::string temp)
{
    QString temp1 = QString::fromStdString(temp);
    return temp1.toFloat();
}

void sur::tomenupage() {
    this->hide();
    sub.show();
    int mainx = this->geometry().x();
    int mainy = this->geometry().y();
    sub.setGeometry(mainx, mainy, 1280, 900);
}

void sur::tosur() {
    sub.hide();
    this->show();
    int mainx = sub.geometry().x();
    int mainy = sub.geometry().y();
    this->setGeometry(mainx, mainy, 1280, 900);
}

void sur::continue_game()
{
    std::ifstream put_file("D:\\survivor_game-ÇØºÆéª-221900460\\sur\\file_temp.txt",std::ios::in);
    if (!put_file) exit(-1);
    std::vector<std::string> text;
    std::vector<std::string> player_strings;
    std::vector<std::string> enemy_close_strings;
    std::vector<std::string> enemy_far_strings;
    std::string line;
    while (getline(put_file, line)) {
        text.push_back(line);
    }
    for (int i = 1; i < 16; i++) {
        player_strings.push_back(text[i]);
    }
    for (int i = 17; i < 21; i++) {
        enemy_close_strings.push_back(text[i]);
    }
    for (int i = 22; i <= 25; i++) {
        enemy_far_strings.push_back(text[i]);
    }
    fund_attribute new_player{ stringtoint(player_strings[1]),stringtoint(player_strings[2]),stringtoint(player_strings[3]),stringtoint(player_strings[4]),stringtoint(player_strings[5]),stringtoint(player_strings[6])};
    weapon_attribute new_player_weapon{ stringtoint(player_strings[7]) ,stringtofloat(player_strings[8]) ,stringtofloat(player_strings[9]) };
    player_continue = new Player(stringtoint(player_strings[0]), new_player, new_player_weapon, stringtoint(player_strings[10]), stringtoint(player_strings[11]), stringtoint(player_strings[12]), stringtoint(player_strings[13]), stringtoint(player_strings[14]));
    enemyclose_continue = new Enemy(stringtoint(enemy_close_strings[0]), stringtoint(enemy_close_strings[1]), stringtoint(enemy_close_strings[2]), stringtoint(enemy_close_strings[3]));
    enemyfar_continue = new Enemy(stringtoint(enemy_far_strings[0]), stringtoint(enemy_far_strings[1]), stringtoint(enemy_far_strings[2]), stringtoint(enemy_far_strings[3]));
    if (stringtoint(player_strings[0]) == 1) {
        twocontinue = new player2_menu;
        onecontinue = new player1_menu(player_continue, enemyclose_continue, enemyfar_continue);
        QObject::connect(ui.continue_2, SIGNAL(clicked()), this, SLOT(toplayermenu1()));
    }
    else {
        onecontinue = new player1_menu;
        twocontinue = new player2_menu(player_continue, enemyclose_continue, enemyfar_continue);
        QObject::connect(ui.continue_2, SIGNAL(clicked()), this, SLOT(toplayermenu2()));
    }
    
}

void sur::toplayermenu1()
{
    this->hide();
    onecontinue->show();
    int mainx = this->geometry().x();
    int mainy = this->geometry().y();
    onecontinue->setGeometry(mainx, mainy, 1280, 900);
}

void sur::toplayermenu2()
{
    this->hide();
    twocontinue->show();
    int mainx = this->geometry().x();
    int mainy = this->geometry().y();
    twocontinue->setGeometry(mainx, mainy, 1280, 900);
}
