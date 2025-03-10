#include"enemy.h"

Enemy::Enemy() {
    Hp = 0;
    Attack_power = 0;
    Speed = 0;
    attack_range = 0;
}
Enemy::~Enemy() {
    Hp = 0;
    Attack_power = 0;
    Speed = 0;
    attack_range = 0;
}
Enemy::Enemy(const int& HP_, const int& Attack_power_, const int& Speed_, const int& attack_range) {
    Hp = HP_;
    Attack_power = Attack_power_;
    Speed = Speed_;
    this->attack_range = attack_range;
}
int Enemy::get_Hp() {
    return Hp;
}
int Enemy::get_Attack_power() {
    return Attack_power;
}
int  Enemy::get_Speed() {
    return Speed;
}
int Enemy::get_attack_range()
{
    return attack_range;
}
void Enemy::change_Hp(const int& temp) {
    Hp += temp;
}

void Enemy::change_speed(const int& temp)
{
    Speed += temp;
}

void Enemy::change_attack_range(const int& temp)
{
    attack_range += temp;
}
