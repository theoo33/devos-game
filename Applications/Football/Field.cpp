#include "Field.h"
#include "Ball.h"


Field :: Field(
    unsigned char* data,
    EcranBochs* vga_entry
) :
    data(data),
    vga(vga_entry)
{};

void Field :: set_borders(ZONE dimensions) {
    field_dimensions = dimensions;
}

void Field :: set_left_goal(ZONE dimensions) {
    left_goal = dimensions;
}

void Field :: set_right_goal(ZONE dimensions) {
    right_goal = dimensions;
}

bool Field :: has_scored(Ball* b) {
    if (
        (b->get_x() >= left_goal.left_upper_x) &&
        (b->get_x() <= left_goal.left_upper_x + left_goal.WIDTH) &&
        (b->get_y() >= left_goal.left_upper_y) &&
        (b->get_y() <= left_goal.left_upper_y + left_goal.HEIGHT)
    ) {
        return true;
    }
    return false;
}

bool Field :: outside_field(Ball* b) {
    if (
        (b->get_x() < field_dimensions.left_upper_x) ||
        (b->get_x() > field_dimensions.left_upper_x + field_dimensions.WIDTH) ||
        (b->get_y() < field_dimensions.left_upper_y) ||
        (b->get_y() > field_dimensions.left_upper_y + field_dimensions.HEIGHT)
    ) {
        return true;
    }
    return false;
}