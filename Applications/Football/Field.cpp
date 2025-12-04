#include "Field.h"
#include "Ball.h"


Field :: Field(
    unsigned char* data,
    EcranBochs* vga_entry,
    const ZONE& borders,
    const ZONE& left_goal_zone,
    const ZONE& right_goal_zone
) :
    background_data(data),
    vga(vga_entry)
{
    // Initialize ZONE members directly
    field_dimensions.left_upper_x = borders.left_upper_x;
    field_dimensions.left_upper_y = borders.left_upper_y;
    field_dimensions.WIDTH = borders.WIDTH;
    field_dimensions.HEIGHT = borders.HEIGHT;
    
    left_goal.left_upper_x = left_goal_zone.left_upper_x;
    left_goal.left_upper_y = left_goal_zone.left_upper_y;
    left_goal.WIDTH = left_goal_zone.WIDTH;
    left_goal.HEIGHT = left_goal_zone.HEIGHT;
    
    right_goal.left_upper_x = right_goal_zone.left_upper_x;
    right_goal.left_upper_y = right_goal_zone.left_upper_y;
    right_goal.WIDTH = right_goal_zone.WIDTH;
    right_goal.HEIGHT = right_goal_zone.HEIGHT;
};

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

bool Field :: outside_field(int x, int y, int width, int height) {
    if (
        (x < field_dimensions.left_upper_x) ||
        (x + width > field_dimensions.left_upper_x + field_dimensions.WIDTH) ||
        (y < field_dimensions.left_upper_y) ||
        (y + height > field_dimensions.left_upper_y + field_dimensions.HEIGHT)
    ) {
        return true;
    }
    return false;
}