#pragma once

#include<iostream>
#include<vector>
struct fund_attribute
{
    int Hp1;           //生命值
    int Hp2;           //生命值
    int Hp;            //总生命值
    int Attack_power; // 攻击力
    int Speed;        // 移动速度
    int get_range;    // 拾取掉落物范围
};
struct weapon_attribute
{
    int range_attack; // 伤害区域
    float duration;       // 持续时间
    float cooling_time;   // 冷却时间
};
class Player
{
private:
    fund_attribute new_player;
    weapon_attribute  weapon;
    std::vector<weapon_attribute> extra_weapons;
    int Exp;   // 经验值
    int Level; // 玩家等级
    int playernum;
    int coin;
    int coin_get;
    int reborn;

public:
    ~Player();
    Player();
    Player(const int& playernum);
    Player(const int &playernum, fund_attribute &new_player, weapon_attribute &weapon);
    Player(const int &playernum, fund_attribute &new_player, weapon_attribute &weapon, const int& Exp, const int& Level,const int& coin,const int& coin_get,const int& reborn);
    Player operator =(Player& player) {
        Player new1(player.playernum, player.new_player, player.weapon, player.Exp, player.Level,player.coin,player.coin_get,player.reborn);
        return new1;
    }
    void change_Hp(int num);
    void change_Attack_power(int num);
    void change_Speed(int num);
    void change_get_range(int num);
    void change_range_attack(int num);
    void change_duration(float num);
    void change_cooling_time(float num);
    void change_Exp(int num);
    void change_Level(int num);
    void change_coin(int num);
    void change_coin_get(int num);
    void change_reborn(int num);
    void change_hp1(int num);
    void change_hp2(int num);
    void change_playernum(int num);
    bool if_Hp0();//检测血量是否为零
    int get_Hp();
    int get_playernum();
    int get_speed();
    int get_attack_power();
    int get_attack_range();
    int get_exp();
    int get_level();
    int get_coin();
    int get_coin_get();
    int get_reborn();
    int get_get_range();
    float get_duration();
    float get_cool();
    int get_hp1();
    int get_hp2();
};


