#include "game.h"

Over_object::Over_object(int a, int b,char sign, Game *board)
{
    x=a;
    y=b;
    symbol=sign;
    board->_map[x][y].set(symbol,this);
}
int Over_object::get_x() const
{
    return x;
}
int Over_object::get_y() const
{
    return y;
}
void Over_object::set_x(int a)
{
    x=a;
}
void Over_object::set_y(int b)
{
    y=b;
}

Creature::Creature(int x,int y,std::string name,char symbol, int h_point, int damage, int money,Game *board)
    :Over_object(x,y,symbol,board)
{
    this->name=name;
    health_points=h_point;
    dmg=damage;
    gold=money;
}
int Creature::get_gold()const
{
    return gold;
}
int Creature::get_dmg()const
{
    return dmg;
}
int Creature::get_health()const
{
    return health_points;
}
char Creature::get_symbol()const
{
    return symbol;
}
std::string Creature::get_name()const
{
    return name;
}
bool Creature::isDead()
{
    if(health_points<1)
        return 1;
    else
        return 0;
}
void Creature::reduceHealth(int enemy_dmg)
{
    health_points-=enemy_dmg;
}
void Creature::kill(Game *board)
{
    board->_map[x][y].zero();
}
void Creature::collision(Player *gamer, Game *game)
{
     gamer->figth(this);
     game->play(gamer);
}

Wall::Wall(int x, int y, Game *board)
    :Over_object(x,y,'#',board)
{

}
void Wall::collision(Player *gamer, Game *game)
{
    std::cout<<"collided";
    game->play(gamer);
}
