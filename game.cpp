#include "game.h"
#include <iostream>
#include <vector>

void Game::set_map()//loading objects on map
{
    size_x=10;
    size_y=10;
    _map.resize(size_x, std::vector<Field>(size_y));
    Creature(5,5,"monster",'M',5,1,5,this);
    Wall w01(0,0,this);
    Wall w02(0,1,this);
    Wall w03(0,2,this);
    Wall w04(0,3,this);
    Wall w05(0,4,this);
    Wall w06(0,5,this);
    Wall w07(0,6,this);
    Wall w08(0,7,this);
    Wall w09(0,8,this);
    Wall w10(0,9,this);
    Wall w91(9,0,this);
    Wall w92(9,1,this);
    Wall w93(9,2,this);
    Wall w94(9,3,this);
    Wall w95(9,4,this);
    Wall w96(9,5,this);
    Wall w97(9,6,this);
    Wall w98(9,7,this);
    Wall w99(9,8,this);
    Wall w910(9,9,this);
}
void Game::map_print()
{
    for (int i=0;i<10;++i)
    {
        for(int j=0;j<10;++j)
        {
            std::cout<<_map[j][i].symbol;
        }
        std::cout<<std::endl;
    }
}

void Game::start()
{
    std::string name;
    set_map();
    std::cout<<"Player name:"<<std::endl;
    std::cin>>name;
    Player one(name,this);
    clear();
    play( &one);
}
void Game::play(Player *one)
{
    while(1)//finnish()==0)creat fininsh function checking if player finnish stage
    {
        map_print();
        one->action(this);
        clear();
    }
}
void Field::zero()
{
    symbol=' ';
    addres=nullptr;
}
Field::Field()
{
    zero();
}

void Field::set(char x, Over_object *pointer)
{
    symbol=x;
    addres=&pointer;
}

void clear()
{
    printf("\e[1;1H\e[2J");
}
