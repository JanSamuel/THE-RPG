//THE RPG by Jan Samuel Owczarek
//Simple rpg/logic console game
//you move by W,S,A,D after each move you need to press enter
//this is project in progress so not everything is working
//for now you can only move so enjoy

#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <memory>

class Player;
class Monster;
class Game;
class Wall;

class Over_object//every object on map must inherit after this object
{
private:
    char symbol;
    int x;
    int y;
    Game * board;
public:
    Over_object(int,int,char,Game &);
    int get_x()const;
    int get_y()const;
    char get_symbol()const;
    Game* board_ptr()const;
    void set_x(int);
    void set_y(int);
    virtual ~Over_object(){}
    virtual void collision(Player *)=0;//reaction trigered if player walks over specfic field
};

class Object :public Over_object
{
public:
    Object();
    Object(const Object &other);
    Object(int ,int ,Game &);
    virtual void collision(Player *)=0;
    virtual ~Object(){}
};

class Move_Object :public Object
{
public:
    Move_Object(int ,int ,Game *);
    virtual void collision(Player *);
    virtual ~Move_Object(){}
};

class Text_Object :public Object
{
    std::string text;
public:
    Text_Object(int ,int ,std::string ,Game *);
    virtual void collision(Player *);
    virtual ~Text_Object(){}
};

struct Field//smallest part of map
{
    char symbol;
    Over_object *addres;
    Field();
    void set(char x,Over_object &);//seting field
    void zero();//reseting field to empty state
private:
    int x,y;
};

class Game
{
    int size_x;
    int size_y;
    std::vector<std::unique_ptr<Monster> >monster_list;
    std::vector<std::unique_ptr<Wall> >wall_list;
    std::vector<std::unique_ptr<Object> >object_list;
public:
    ~Game();
    std::vector< std::vector<Field> >_map;
    // bool finnish();
    void set_map();
    void start();
    void play(Player *);
    void map_print(Player *);
    void monster_maker(std::string,int,int);
    void monster_maker(std::string,int,int,char,int,int,int);
    std::unique_ptr<Monster> newcreature(std::string,int,int);
    void wall_maker(int,int);
    void wall_maker(int,int,int,int);
    void MoveObj_maker(int x,int y);
    void TextObj_maker(int x,int y,std::string text);

};

class Wall :public Over_object
{
public:
    Wall(int ,int ,Game *);
    virtual void collision(Player *);
    virtual ~Wall(){}
};

class Creature :public Over_object
{
protected:
    std::string name;
    int health_points;
    int dmg;
    int gold;
public:
    virtual ~Creature(){}
    Creature();
    Creature(int,int,std::string,char, int, int, int,Game &);
    Creature(const Creature &other);
    int get_gold()const;
    int get_dmg()const;
    int get_health()const;
    std::string get_name()const;
    virtual bool isDead();
    virtual void reduceHealth(int);
    virtual void collision(Player *)=0;
};

class Monster :public Creature
{
public:
    virtual ~Monster(){}
    void kill();
    Monster(int x,int y,std::string name,char symbol, int h_point, int damage, int money,Game *game_ptr);
    virtual void collision(Player *);
};

class Player :public Creature//player starts on position 2,2
{
    int level;
public:
    virtual ~Player(){}
    Player(std::string,Game *);  
    void action();
    int get_leve()const;
    void add_level();
    void addGold(int);
    void addDMG();
    void figth (Monster *);
    virtual void collision(Player *);
};

void clear();
char getch();
void narration(std::string text);
