#include "bn_core.h"
#include "bn_regular_bg_ptr.h"
#include "bn_fixed.h"
#include "bn_sprite_ptr.h"
#include "bn_keypad.h"

#include "bn_regular_bg_items_background.h"
#include "bn_sprite_items_bird.h"
#include "bn_sprite_items_top_pipe.h"
#include "bn_sprite_items_bottom_pipe.h"

using namespace bn;

//constants
constexpr int SCREEN_WIDTH = 256;
constexpr int SCREEN_HEIGHT = 256;
constexpr fixed GRAVITY = fixed(.1);
constexpr fixed JUMP_STRENGTH = fixed(-2);
constexpr int PIPE_WIDTH = 32;
constexpr int PIPE_GAP = 50;


int main() {
    core::init();

    regular_bg_ptr background = regular_bg_items::background.create_bg(0,0);
    sprite_ptr bird = sprite_items::bird.create_sprite(0,0);
    sprite_ptr top_pipe = sprite_items::top_pipe.create_sprite(88, -50);
    sprite_ptr bottom_pipe = sprite_items::bottom_pipe.create_sprite(88, 60);

    fixed bird_velocity_y = 0;
    fixed gravity = GRAVITY;
    fixed jump_strength = JUMP_STRENGTH;
    int score = 0;
    bool game_over_flag = false;




    while (true) {
        bn::core::update();
        if (keypad::a_pressed()) {
            bird_velocity_y = jump_strength;
        }

        bird_velocity_y += gravity;
        bird.set_y(bird.y() + bird_velocity_y);
        top_pipe.set_x(top_pipe.x() - 1);
        bottom_pipe.set_x(bottom_pipe.x() - 1);
        if (top_pipe.x() < -150) {
            top_pipe.set_x(128);
            bottom_pipe.set_x(128);
        }

        if (bird.y() < -73 || bird.y() > 73) {
            bird.set_y(73);
        }

        if (bird.x() > bottom_pipe.x() && bird.x() - 8 < bottom_pipe.x() + 32) {
            if (bird.y() + 32 > bottom_pipe.y() || bird.y() - 32 < top_pipe.y()) {
                bird.set_y(70);
            }
        }
        // background.set_x(background.x() - 1);
    }
}