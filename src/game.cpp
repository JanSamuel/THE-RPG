#include "game.h"

std::unique_ptr<Monster> Game::newcreature(std::string name, int x, int y)
{
    //for addition of new monster add to this list
    // else if(name==""){return new Creature tmp(x,y,name,M,health points,damage,gold on monster,this)}

    if(name=="rat"){return std::unique_ptr<Monster>(new Monster(x,y,name,'M',5,1,5,this));}
    else if(name=="bat"){return std::unique_ptr<Monster>(new Monster(x,y,name,'M',2,3,1,this));}
    else if(name=="orc"){return std::unique_ptr<Monster>(new Monster(x,y,name,'M',10,1,5,this));}
    else if(name=="troll"){return std::unique_ptr<Monster>(new Monster(x,y,name,'M',10,4,8,this));}
    else return 0;
}
void Game::monster_maker(std::string name,int x,int y)
{
    std::unique_ptr<Monster>newMonster=newcreature(name,x,y);
    monster_list.push_back(std::move(newMonster));
}
void Game::monster_maker(std::string name,int x, int y,char symbol,int health_points,int damage,int gold)
{
    std::unique_ptr<Monster> newMonster=std::unique_ptr<Monster>(new Monster(x,y,name,symbol,health_points,damage,gold,this));
    monster_list.push_back(std::move(newMonster));
}
void Game::wall_maker(int x,int y)
{
    std::unique_ptr<Wall> newWall=std::unique_ptr<Wall>(new Wall(x,y,this));
    wall_list.push_back(std::move(newWall));
}
void Game::wall_maker(int x1,int y1,int x2, int y2)
{
    if(x1==x2)
    {
        if(y1>=y2)
        {
            for(int i=y2;i<=y1;++i)
            {
                std::unique_ptr<Wall> newWall=std::unique_ptr<Wall>(new Wall(x1,i,this));
                wall_list.push_back(std::move(newWall));            }
        }
        else
        {
            for(int i=y1;i<=y2;++i)
            {
                std::unique_ptr<Wall> newWall=std::unique_ptr<Wall>(new Wall(x1,i,this));
                wall_list.push_back(std::move(newWall));            }
        }
    }
    else if(y1==y2)
    {
        if(x1>=x2)
        {
            for(int i=x2;i<=x1;++i)
            {
                std::unique_ptr<Wall> newWall=std::unique_ptr<Wall>(new Wall(i,y1,this));
                wall_list.push_back(std::move(newWall));            }
        }
        else
        {
            for(int i=x1;i<=x2;++i)
            {
                std::unique_ptr<Wall> newWall=std::unique_ptr<Wall>(new Wall(i,y1,this));
                wall_list.push_back(std::move(newWall));            }
        }
    }
    else
        std::cout<<"Error: wall maker"<<std::endl;
}
void Game::MoveObj_maker(int x,int y)
{
    std::unique_ptr<Move_Object> newObj=std::unique_ptr<Move_Object>(new Move_Object(x,y,this));
    object_list.push_back(std::move(newObj));
}
void Game::TextObj_maker(int x,int y,std::string text)
{
    std::unique_ptr<Text_Object> newObj=std::unique_ptr<Text_Object>(new Text_Object(x,y,text,this));
    object_list.push_back(std::move(newObj));
}

void Game::set_map()//loading objects on map
{
    size_x=150;
    size_y=200;
    _map.resize(size_x, std::vector<Field>(size_y));
    monster_maker("bat",5,5);
    MoveObj_maker(8,5);
    TextObj_maker(10,11,"sample text");
    wall_maker(0,0,0,199);
    wall_maker(1,0,148,0);
    wall_maker(3,2,3,50);


}
void Game::map_print(Player *one)
{
    const int view_y=8;
    const int view_x=view_y*2;
    int y_max,y_min;
    int x_max,x_min;
    {
        if(one->get_x()<=view_x){x_min=0;}
        if(one->get_y()<=view_y){y_min=0;}
        if(one->get_x()>=view_x){x_min=one->get_x()-view_x;}
        if(one->get_y()>=view_y){y_min=one->get_y()-view_y;}
        if(one->get_x()+view_x>size_x){x_max=size_x;}
        if(one->get_y()+view_y>size_y){y_max=size_y;}
        if(one->get_x()+view_x<size_x){x_max=one->get_x()+view_x;}
        if(one->get_y()+view_y<size_y){y_max=one->get_y()+view_y;}
    }
    for (int i=y_max-1;i>=y_min;--i)
    {
        for(int j=x_min;j<x_max;++j)
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
    narration("You are in compleat darknes, no sound, no smell, nothing you can fell, you are part of darkness as it is part of you. You don't feel passage of time almost like even time dosent exist here. With no thouge at all you are suspended as part of this plane. You almoste don't exist");
    narration("Sparkel. Singel sparkel inside you. You can fell it. Evrything comes back to you, you can fell.\nYou fell coldness and felling of loss. But you can not rember what was lost/nYou look at your hands only to see your white bare bones. So I really died You thouge. ther whern't any meat on your animeted bones. You had died long ago ");
    play( &one);
}
void Game::play(Player *one)
{
    while(1)//finnish()==0)creat fininsh function checking if player finnish stage
    {
        map_print(one);
        one->action();
        clear();
    }
}
Game::~Game()
{
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
void Field::set(char x, Over_object &pointer)
{
    symbol=x;
    addres=&pointer;
}
void clear()
{
    printf("\e[1;1H\e[2J");
}
char getch()
{
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}
void narration(std::string text)
{
    clear();
    std::cout<<text<<std::endl;
    std::cin.get();
    std::cin.ignore();
}
