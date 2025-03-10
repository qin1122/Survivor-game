#pragma once

#include <iostream>
class Enemy {
private:
    int Hp;           // 生命值
    int Attack_power; // 攻击力
    int Speed;// 移动速度
    int attack_range;//攻击范围
public:
    Enemy();
    Enemy(const int& HP_, const int& Attack_power_, const int& Speed_,const int& attack_range);
    ~Enemy();
    Enemy& operator =(Enemy& enemy) {
        this->Hp = enemy.Hp;
        this->Attack_power = enemy.Attack_power;
        this->Speed = enemy.Speed;
        this->attack_range = enemy.attack_range;
        return *this;
    }
    int get_Hp();
    int get_Attack_power();
    int get_Speed();
    int get_attack_range();
    void change_Hp(const int& temp);
    void change_speed(const int& temp);
    void change_attack_range(const int& temp);
};

