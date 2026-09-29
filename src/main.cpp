#include <bn_backdrop.h>
#include <bn_core.h>
#include <bn_keypad.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bun.h"

#define FLOOR (80 - 8)

int main()
{
    bn::core::init();

    bn::backdrop::set_color(bn::color(15, 0, 30));

    auto dot = bn::sprite_items::bun.create_sprite(0, 0);
    
    //These are the min and max variables that will
    //outline the borders of the screen (240x160 pixels,
    //and contrary to the Environment Learning tutorial,
    //the screen size is actually not 240x180. I tested it
    //myself already.)
    bn::fixed min_x = -120;
    bn::fixed max_x = 120;
    bn::fixed min_y = -80;
    bn::fixed max_y = 80;

    bn::fixed speed = 1.5;

    bn::fixed dy = 0;
    bn::fixed gravity = 0.03;

    bn::fixed jump_strength = 1;

    while (true)
    {   
        //Create 2 variables for the Sprites current x and y coordinates
        bn::fixed x = dot.x();
        bn::fixed y =  dot.y();

        //Now, if the dot/character walks beyond the set min/max boundary set,
        //the dots x/y current y value will also be set to the max/min
        //so that they can never go beyond that point.
        //So as an example, if the dot goes beyond the max x value of 120, 
        //then they would have their current x value set to the max value of 120.
        //Hence never letting them go beyond the boundaries of the screen.
        //I assume that there is a more effective method but I don't know much
        //about how to code using this yet, so using my basic knowledge I
        //made a simple if/else statement that works.
  
        if(x < min_x)
        {
            x = min_x;
        }
        else if(x > max_x)
        {
            x = max_x;
        }

        if(y < min_y)
        {
            y = min_y;
        }
        else if(y > max_y)
        {
            y = max_y;
        }

        //These will basically just set the dots x/y value AFTER running through
        //the if/else statements. I was really confused as first because without these
        //the code didn't work at all, so it seemes like I have to manually
        //update the values after processing them for it to actually work.
        dot.set_x(x);
        dot.set_y(y);

        if (bn::keypad::left_held())
        {
            dot.set_x(dot.x() - speed);
        }
        if (bn::keypad::right_held())
        {
            dot.set_x(dot.x() + speed);
        }
        if (bn::keypad::a_pressed())
        {
            dy -= jump_strength;
        }

        dy += gravity;

        dot.set_y(dot.y() + dy);

        if (dot.y() > FLOOR)
        {
            dot.set_y(FLOOR);
            dy = 0;
        }

        bn::core::update();
    }
}