//THE RPG by Jan Samuel Owczarek
//Simple rpg/logic console game
//you move by W,S,A,D after each move you need to press enter
//this is project in progress so not everything is working
//for now you can only move so enjoy

#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>

class Player;
class Game;

struct Over_object//every object on map must inherit after this object
{
    char symbol;
    int x;
    int y;
    Over_object(int,int,char,Game *);
    int get_x()const;
    int get_y()const;
    void set_x(int);
    void set_y(int);
    virtual void collision(Player *,Game *)=0;//reaction trigered if player walks over specfic field
};

struct Field//smallest part of map
{
    char symbol;
    Over_object **addres;
    Field();
    void set(char x,Over_object *);//seting field
    void zero();//reseting field to empty state
private:
    int x,y;
};

class Game
{
    int size_x;
    int size_y;
public:
    std::vector< std::vector<Field> >_map;
    // bool finnish();
    void set_map();
    void start();
    void play(Player *);
    void map_print();
};

class Wall :public Over_object
{
public:
    Wall(int ,int ,Game *);
    virtual void collision(Player *,Game *);
};

class Creature :public Over_object
{
    std::string name;
    int health_points;
    int dmg;
    int gold;
public:
    Creature();
    Creature(int,int,std::string,char, int, int, int,Game *);
    int get_gold()const;
    int get_dmg()const;
    int get_health()const;
    char get_symbol()const;
    std::string get_name()const;
    bool isDead();
    void reduceHealth(int);
    void kill(Game *);
    virtual void collision(Player *,Game *);
};

class Player :public Over_object//player starts on position 2,2
{
    std::string name;
    int health_points;
    int dmg;
    int gold;
    int level;
public:
    Player(std::string,Game *);
    void action(Game *);
    int get_leve()const;
    void add_level();
    void reduceHealth(int);
    void addGold(int);
    void addDMG();
    std::string get_name()const;
    int get_gold()const;
    int get_dmg()const;
    int get_health()const;
    char get_symbol()const;
    void figth (Creature *);
    virtual void collision(Player *,Game *);
};

void clear();
