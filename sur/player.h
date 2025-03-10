#pragma once

#include<iostream>
#include<vector>
struct fund_attribute
{
    int Hp1;           //����ֵ
    int Hp2;           //����ֵ
    int Hp;            //������ֵ
    int Attack_power; // ������
    int Speed;        // �ƶ��ٶ�
    int get_range;    // ʰȡ�����ﷶΧ
};
struct weapon_attribute
{
    int range_attack; // �˺�����
    float duration;       // ����ʱ��
    float cooling_time;   // ��ȴʱ��
};
class Player
{
private:
    fund_attribute new_player;
    weapon_attribute  weapon;
    std::vector<weapon_attribute> extra_weapons;
    int Exp;   // ����ֵ
    int Level; // ��ҵȼ�
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
    bool if_Hp0();//���Ѫ���Ƿ�Ϊ��
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


