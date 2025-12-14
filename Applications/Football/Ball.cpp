#include "Ball.h"
#include "Player.h"
#include <drivers/EcranBochs.h>

extern int FRAME_SKIP;

Ball :: Ball(
    int x, 
    int y, 
    int acc, 
    int friction,
    unsigned char* data, 
    Player* p1, 
    Player* p2,
    EcranBochs* vga_entry,
    Field* field_entry
) :
    x(x),
    y(y),
    speed(0),
    acc(acc),
    friction(friction),
    counter_till_next_speed(0),
    data(data),
    p1(p1),
    p2(p2),
    vga(vga_entry),
    field(field_entry)
{};

bool Ball :: isColliding(Player* p) {
    // first we calculate a possible contact on each side of the ball
    bool contact_left = (
        (p->get_x() + p->PLAYER_WIDTH >= x) &&
        (p->get_x() + p->PLAYER_WIDTH <= x + BALL_WIDTH)
    );
    bool contact_right = (
        (p->get_x() >= x) &&
        (p->get_x() <= x + BALL_WIDTH)
    );
    bool contact_up = (
        (p->get_y() + p->PLAYER_HEIGHT >= y) &&
        (p->get_y() + p->PLAYER_HEIGHT <= y + BALL_HEIGHT)
    );
    bool contact_down = (
        (p->get_y() >= y) &&
        (p->get_y() <= y + BALL_HEIGHT)
    );
    if ((contact_left || contact_right) && (contact_down || contact_up))
        return true;
    return false;
}

void Ball :: bresenhamInit() {
    dx = (x_diff > 0) - (x_diff < 0);  // signum : -1, 0 ou 1
    dy = (y_diff > 0) - (y_diff < 0);
    if (x_diff < 0) x_diff = -x_diff;
    if (y_diff < 0) y_diff = -y_diff;
    err = x_diff - y_diff;

    x_bounce = 1;
    y_bounce = 1;
};

void Ball :: bresenhamGetOrientation() {
    int e2 = 2 * err;
    towards_x = 0;
    towards_y = 0;

    if (e2 > -y_diff) {
        err -= y_diff;
        towards_x = dx;   // vers_x
    }
    if (e2 < x_diff) {
        err += x_diff;
        towards_y = dy;   // vers_y
    }
}


void Ball :: move() {
    bresenhamGetOrientation();
    int new_x = x + (towards_x * speed) * x_bounce;
    int new_y = y + (towards_y * speed) * y_bounce;

    if ((field->outside_field_x(new_x, new_y, BALL_WIDTH, BALL_HEIGHT))
    && field->has_scored(new_x, new_y, BALL_WIDTH, BALL_HEIGHT) == 0) {
        x_bounce = -1;
    }

    if ((field->outside_field_y(new_x, new_y, BALL_WIDTH, BALL_HEIGHT))
    && field->has_scored(new_x, new_y, BALL_WIDTH, BALL_HEIGHT) == 0) {
        y_bounce = -1;
    }

    if (counter_till_next_speed > 0) {
        x = new_x;
        y = new_y;
        counter_till_next_speed -= 1;
    }
    else {
        speed -= friction;
        if (speed < 0) speed = 0;
        counter_till_next_speed = speed;
    }
}

void Ball :: run() {
    int frame = 0;
    const int FRAME_SKIP = 5; // only update movement once every 5 frames
    while (true) {
        if ((frame % FRAME_SKIP) == 0) {
            {
                Player* players[2] = {p1, p2};
                for (Player* p : players) {
                    if (isColliding(p)) {
                        speed = acc;
                        counter_till_next_speed = speed;

                        x_diff = x - p->get_x();
                        y_diff = y - p->get_y();
                        bresenhamInit();
                    }
                }
            }
            move();
        }
        frame++;
        vga->plot_sprite(get_data(), BALL_WIDTH, BALL_HEIGHT, get_x(), get_y());
        thread_yield();
    }
    thread_exit();
}