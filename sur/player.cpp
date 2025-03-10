#include"player.h"
Player::~Player()
{
    extra_weapons.clear();
    Exp = 0;
    Level = 0;
    playernum = 0;
    coin = 0;
    coin_get = 0;
    reborn = 0;
}
Player::Player() 
{
    playernum = 0;
    Exp = 0;
    Level = 0;
    this->new_player.Hp = 0;
    this->new_player.Attack_power = 0;
    this->new_player.Speed = 0;
    this->new_player.get_range = 0;
    this->new_player.Hp1 = 0;
    this->new_player.Hp2 = 0;
    this->weapon.range_attack = 0;
    this->weapon.duration = 0;
    this->weapon.cooling_time = 0;
    coin = 0;
    coin_get = 0;
    reborn = 0;

}
Player::Player(const int& playernum)
{
    this->playernum = playernum;
    Exp = 0;
    Level = 0;
    this->new_player.Hp = 0;
    this->new_player.Attack_power = 0;
    this->new_player.Speed = 0;
    this->new_player.get_range = 0;
    this->new_player.Hp1 = 0;
    this->new_player.Hp2 = 0;
    this->weapon.range_attack = 0;
    this->weapon.duration = 0;
    this->weapon.cooling_time = 0;
    coin = 0;
    coin_get = 0;
    reborn = 0;
}
Player::Player(const int& playernum, fund_attribute& new_player, weapon_attribute& weapon) {
    this->new_player.Hp = new_player.Hp;
    this->new_player.Attack_power = new_player.Attack_power;
    this->new_player.Speed = new_player.Speed;
    this->new_player.get_range = new_player.get_range;
    this->new_player.Hp1 = new_player.Hp1;
    this->new_player.Hp2 = new_player.Hp2;
    this->weapon.range_attack = weapon.range_attack;
    this->weapon.duration = weapon.duration;
    this->weapon.cooling_time = weapon.cooling_time;
    Exp = 0;
    Level = 0;
    this->playernum = playernum;
    coin = 0;
    coin_get = 0;
    reborn = 0;
}

Player::Player(const int& playernum, fund_attribute& new_player, weapon_attribute& weapon, const int& Exp, const int& Level,const int& coin,  const int& coin_get, const int& reborn)
{
    this->new_player.Hp = new_player.Hp;
    this->new_player.Attack_power = new_player.Attack_power;
    this->new_player.Speed = new_player.Speed;
    this->new_player.get_range = new_player.get_range;
    this->new_player.Hp1 = new_player.Hp1;
    this->new_player.Hp2 = new_player.Hp2;
    this->weapon.range_attack = weapon.range_attack;
    this->weapon.duration = weapon.duration;
    this->weapon.cooling_time = weapon.cooling_time;
    this->Exp = Exp;
    this->Level = Level;
    this->playernum = playernum;
    this->coin = coin;
    this->coin_get = coin_get;
    this->reborn = reborn;
}

void Player::change_Hp(int num)
{
    new_player.Hp += num;
}

void Player::change_Attack_power(int num)
{
    new_player.Attack_power += num;
}

void Player::change_Speed(int num)
{
    new_player.Speed += num;
}

void Player::change_get_range(int num)
{
    new_player.get_range += num;
}

void Player::change_range_attack(int num)
{
    weapon.range_attack += num;
}

void Player::change_duration(float num)
{
    weapon.duration += num;
}

void Player::change_cooling_time(float num)
{
    weapon.cooling_time += num;
}

void Player::change_Exp(int num)
{
    Exp += num;
}

void Player::change_Level(int num)
{
    Level += num;
}

void Player::change_coin(int num)
{
    coin += num;
}

void Player::change_coin_get(int num)
{
    coin_get += num;
}

void Player::change_reborn(int num)
{
    reborn = reborn + num;
}

void Player::change_hp1(int num)
{
    new_player.Hp1 += num;
}

void Player::change_hp2(int num)
{
    new_player.Hp2 += num;
}

void Player::change_playernum(int num)
{
    playernum = num;
}

bool Player::if_Hp0()
{
    if (new_player.Hp == 0)
        return true;
    else
        return false;
}

int Player::get_Hp()
{
    return this->new_player.Hp;
}

int Player::get_playernum()
{
    return this->playernum;
}

int Player::get_speed()
{
    return this->new_player.Speed;
}

int Player::get_attack_power()
{
    return this->new_player.Attack_power;
}

int Player::get_attack_range()
{
    return this->weapon.range_attack;
}

int Player::get_exp()
{
    return this->Exp;
}

int Player::get_level()
{
    return Level;
}

int Player::get_coin()
{
    return coin;
}

int Player::get_coin_get()
{
    return coin_get;
}

int Player::get_reborn()
{
    return reborn;
}

int Player::get_get_range()
{
    return new_player.get_range;
}

float Player::get_duration()
{
    return weapon.duration;
}

float Player::get_cool()
{
    return weapon.cooling_time;
}

int Player::get_hp1()
{
    return new_player.Hp1;
}

int Player::get_hp2()
{
    return new_player.Hp2;
}
