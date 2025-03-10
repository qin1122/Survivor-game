#pragma once

#include <iostream>
class Enemy {
private:
    int Hp;           // ����ֵ
    int Attack_power; // ������
    int Speed;// �ƶ��ٶ�
    int attack_range;//������Χ
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

