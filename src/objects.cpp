#include "game.h"

Object::Object(int x,int y,Game &game_ptr)//dodać parametr visible//dodac parameter destructable//
    :Over_object(x,y,'o',game_ptr)
{
}
Text_Object::Text_Object(int x,int y,std::string text,Game *game_ptr)
    :Object(x,y,*game_ptr)
{
  this->text=text;
}
void Text_Object::collision(Player *)
{
    narration(text);
}

Move_Object::Move_Object(int x,int y,Game *game_ptr)
    :Object(x,y,*game_ptr)
{
}
void Move_Object::collision(Player *gamer)
{
    std::cout<<"object collision"<<std::endl;
    int position_x=get_x()-(gamer->get_x());
    int position_y=get_y()-(gamer->get_y());
    std::cout<<position_x<<std::endl;
    std::cout<<position_y<<std::endl;

    if(position_x==0)
    {
        std::cout<<"error x"<<std::endl;
        if(position_y==-1)
           {
            if(!board_ptr()->_map[get_x()][get_y()-1].addres)
            {
            board_ptr()->_map[get_x()][get_y()].zero();
            set_y(get_y()-1);
            board_ptr()->_map[get_x()][get_y()].set(get_symbol(),*this);
            }
           }
        else if(position_y==1)
        {
            if(!board_ptr()->_map[get_x()][get_y()+1].addres)
            {
            board_ptr()->_map[get_x()][get_y()].zero();
            set_y(get_y()+1);
            board_ptr()->_map[get_x()][get_y()].set(get_symbol(),*this);
            }
        }
    }
    else if(position_y==0)
    {
        std::cout<<"error y"<<std::endl;

        if(position_x==-1)
           {
            if(!board_ptr()->_map[get_x()-1][get_y()].addres)
            {
            board_ptr()->_map[get_x()][get_y()].zero();
            set_x(get_x()-1);
            board_ptr()->_map[get_x()][get_y()].set(get_symbol(),*this);
           }
        }
        if(position_x==1)
           {
            if(!board_ptr()->_map[get_x()+1][get_y()].addres)
            {
            board_ptr()->_map[get_x()][get_y()].zero();
            set_x(get_x()+1);
            board_ptr()->_map[get_x()][get_y()].set(get_symbol(),*this);
            }
           }
    }
    else
        std::cout<<"error moveable object";
}
