#include "game.h"

Over_object::Over_object(int a, int b,char sign, Game &game_ptr)
{
    x=a;
    y=b;
    symbol=sign;
    board=&game_ptr;
    if(!(board->_map[x][y].addres))
    {
    board->_map[x][y].set(symbol,*this);
    }
    else
    {
        std::cout<<"error filed taken"<<std::endl;
    }
}
Game* Over_object::board_ptr()const
{
    return board;
}
char Over_object::get_symbol()const
{
    return symbol;
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

Wall::Wall(int x, int y, Game *game_ptr)
    :Over_object(x,y,'#',*game_ptr)
{
}
void Wall::collision(Player *gamer)
{

}
