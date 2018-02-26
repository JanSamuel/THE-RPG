#include"game.h"


Player::Player(std::string n, Game *board)
    :Over_object(2,2,'@',board)
{
    name=n;
    health_points=10;
    dmg=1;
    gold=0;
    level=1;
}
int Player::get_gold()const
{
    return gold;
}
int Player::get_dmg()const
{
    return dmg;
}
int Player::get_health()const
{
    return health_points;
}
char Player::get_symbol()const
{
    return symbol;
}
std::string Player::get_name()const
{
    return name;
}

void Player::reduceHealth(int enemy_dmg)
{
    health_points-=enemy_dmg;
}
void Player::addGold(int coins)
{
    gold+=coins;
}
void Player::addDMG()
{
    dmg++;
}

int Player::get_leve()const
{
    return level;
}
void Player::add_level()
{
    level++;
    addDMG();
}

void Player::collision(Player *nothing, Game *game)//not planing to use it
{
    std::cout<<"the player stumbled over his own leg"<<std::endl;
    game->play(nothing);
}

void Player::action(Game *board)
{
    char move=0;
    move=getchar();
    Over_object ***collided=nullptr;
    switch(move)
    {
    case 's':
    {
        if(board->_map[get_x()][get_y()+1].addres)
        {
            collided=&(board->_map[get_x()][get_y()+1].addres);
            (**collided)->collision(this,board);
        }
        else
        {
            board->_map[get_x()][get_y()].zero();
            set_y(get_y()+1);
            board->_map[get_x()][get_y()].set('@',this);
        }
    }
        break;
    case 'w':
    {
        {
            if(board->_map[get_x()][get_y()-1].addres)
            {

                collided=&board->_map[get_x()][get_y()-1].addres;
                (**collided)->collision(this,board);
            }
            else
            {
                board->_map[get_x()][get_y()].zero();
                set_y(get_y()-1);
                board->_map[get_x()][get_y()].set('@',this);
            }
        }
        break;
    }
    case 'a':
    {
        {
            if(board->_map[get_x()-1][get_y()].addres)
            {
                collided=&board->_map[get_x()-1][get_y()].addres;
                (**collided)->collision(this,board);
            }
            else
            {
                board->_map[get_x()][get_y()].zero();
                set_x(get_x()-1);
                board->_map[get_x()][get_y()].set('@',this);
            }
        }
        break;
    }
    case 'd':
    {
        {
            if(board->_map[get_x()+1][get_y()].addres)
            {
                collided=&board->_map[get_x()+1][get_y()].addres;
                (**collided)->collision(this,board);
            }
            else
            {
                board->_map[get_x()][get_y()].zero();
                set_x(get_x()+1);
                board->_map[get_x()][get_y()].set('@',this);
            }
        }
        break;
    }
    default:
    {
        action(board);
        break;
    }
    }

}

void Player::figth (Creature *monster)
{
    while((monster->get_health()!=0)||(get_health()!=0))
    {
        monster->reduceHealth(get_dmg());
        reduceHealth(monster->get_dmg());
    }
    if(!monster->isDead())
    {
        addGold(monster->get_gold());
        add_level();
        //monster->kill();
    }
    else
    {
        std::cout<<"You died!"<<std::endl;
        std::cout<<"game lost"<<std::endl;
    }
}
