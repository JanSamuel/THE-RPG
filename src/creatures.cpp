#include"game.h"

Creature::Creature(int x,int y,std::string name,char symbol, int h_point, int damage, int money,Game &game_ptr)
    :Over_object(x,y,symbol,game_ptr)
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
std::string Creature::get_name()const
{
    return name;
}
bool Creature::isDead()//do I need it??
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

Monster::Monster(int x,int y,std::string name,char symbol, int h_point, int damage, int money,Game *game_ptr)
    :Creature(x,y,name,symbol,h_point,damage,money,*game_ptr)
{
}

void Monster::collision(Player *gamer)
{
    gamer->figth(this);
}
void Monster::kill()
{
    board_ptr()->_map[get_x()][get_y()].zero();
}

Player::Player(std::string n, Game *game_ptr)
    :Creature(2,2,n,'@',10,1,0,*game_ptr)
{
    level=1;
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
void Player::collision(Player *nothing)//not planing to use it
{
    std::cout<<"the player stumbled over his own leg"<<std::endl;
}
void Player::action()
{
    char move=0;
    move=getch();
    Over_object *collided=nullptr;
    switch(move)
    {
    case 's':
    {
        if(board_ptr()->_map[get_x()][get_y()-1].addres)
        {
            collided=board_ptr()->_map[get_x()][get_y()-1].addres;
            collided->collision(this);
        }
        else
        {
            board_ptr()->_map[get_x()][get_y()].zero();
            set_y(get_y()-1);
            board_ptr()->_map[get_x()][get_y()].set('@',*this);
        }
    }
        break;
    case 'w':
    {
        {
            if(board_ptr()->_map[get_x()][get_y()+1].addres)
            {
                collided=board_ptr()->_map[get_x()][get_y()+1].addres;
                collided->collision(this);
            }
            else
            {
                board_ptr()->_map[get_x()][get_y()].zero();
                set_y(get_y()+1);
                board_ptr()->_map[get_x()][get_y()].set('@',*this);
            }
        }
        break;
    }
    case 'a':
    {
        {
            if(board_ptr()->_map[get_x()-1][get_y()].addres)
            {
                collided=board_ptr()->_map[get_x()-1][get_y()].addres;
                collided->collision(this);
            }
            else
            {
                board_ptr()->_map[get_x()][get_y()].zero();
                set_x(get_x()-1);
                board_ptr()->_map[get_x()][get_y()].set('@',*this);
            }
        }
        break;
    }
    case 'd':
    {
        {
            if(board_ptr()->_map[get_x()+1][get_y()].addres)
            {
                collided=board_ptr()->_map[get_x()+1][get_y()].addres;
                collided->collision(this);
            }
            else
            {
                board_ptr()->_map[get_x()][get_y()].zero();
                set_x(get_x()+1);
                board_ptr()->_map[get_x()][get_y()].set('@',*this);
            }
        }
        break;
    }
    default:
    {
        action();
        break;
    }
    }
}
void Player::figth (Monster *monster)
{
    std::cout<<"figth start"<<std::endl;
    std::cout<<"player "<<get_health()<<" Monster "<<monster->get_health()<<std::endl;
    while((monster->get_health()>0)&&(get_health()>=0))
    {
        monster->reduceHealth(get_dmg());
        reduceHealth(monster->get_dmg());
        std::cout<<"player "<<get_health()<<" Monster "<<monster->get_health()<<std::endl;
    }
    if(monster->get_health()<=0)
    {
        addGold(monster->get_gold());
        add_level();
        monster->kill();
        std::cout<<"You win";
    }
    else
    {
        std::cout<<"You died!"<<std::endl;
        std::cout<<"game lost"<<std::endl;
    }
    std::cin.get();
    std::cin.ignore();
}
