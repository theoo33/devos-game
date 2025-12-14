#include "Field.h"
#include "Ball.h"

void paint_circle(int x_center, int y_center, int radius, EcranBochs* vga) {
    for (int x = x_center - radius; x < x_center + radius; x++) {
        for (int y = y_center - radius; y < y_center + radius; y++) {
            int dx = x_center - x;
            int dy = y_center - y;
            int distance_squared = (dx * dx) + (dy * dy);
            int radius_squared = radius * radius;
            int tolerance = 95;
            if ((distance_squared <= radius_squared  + tolerance) && (distance_squared >= radius_squared - tolerance)) {
                vga->paint(x, y, 255);
            }
        }
    }
}

void paint_zone(const ZONE& zone, EcranBochs* vga) {
    for (int x = zone.left_upper_x; x < zone.right_lower_x; x++) {
        vga->paint(
            x,
            zone.left_upper_y,
            255
        );
        vga->paint(
            x,
            zone.right_lower_y,
            255
        );
    }
    for (int y = zone.left_upper_y; y < zone.right_lower_y; y++) {
        vga->paint(
            zone.left_upper_x,
            y,
            255
        );
        vga->paint(
            zone.right_lower_x,
            y,
            255
        );
	}
}


Field :: Field(
    EcranBochs* vga_entry,
    const ZONE& borders,
    const ZONE& left_goal_zone,
    const ZONE& right_goal_zone
) :
    vga(vga_entry)
{
    // Initialize ZONE members directly
    field.left_upper_x = borders.left_upper_x;
    field.left_upper_y = borders.left_upper_y;
    field.right_lower_x = borders.right_lower_x;
    field.right_lower_y = borders.right_lower_y;
    
    left_goal.left_upper_x = left_goal_zone.left_upper_x;
    left_goal.left_upper_y = left_goal_zone.left_upper_y;
    left_goal.right_lower_x = left_goal_zone.right_lower_x;
    left_goal.right_lower_y = left_goal_zone.right_lower_y;
    
    right_goal.left_upper_x = right_goal_zone.left_upper_x;
    right_goal.left_upper_y = right_goal_zone.left_upper_y;
    right_goal.right_lower_x = right_goal_zone.right_lower_x;
    right_goal.right_lower_y = right_goal_zone.right_lower_y;
};

int Field :: has_scored(int x, int y, int width, int height) {
    if (
        (x < left_goal.left_upper_x) &&
        (y > left_goal.left_upper_y) &&
        (y + height < left_goal.right_lower_y)
    ) {
        return 1;
    }
    if (
        (x + width > right_goal.right_lower_x) &&
        (y > right_goal.left_upper_y) &&
        (y + height < right_goal.right_lower_y)
    ) {
        return 2;
    }
    return 0;
}

bool Field :: outside_field(int x, int y, int width, int height) {
    if (
        (x < field.left_upper_x) ||
        (x + width > field.right_lower_x) ||
        (y < field.left_upper_y) ||
        (y + height > field.right_lower_y)
    ) {
        return true;
    }
    return false;
}

void Field :: paint() {
    vga->clear(197); // Green field color
    paint_circle(
        (field.left_upper_x + field.right_lower_x) /2,
        (field.left_upper_y + field.right_lower_y) /2,
        40,
        vga
    );
    // Field borders
    paint_zone(field, vga);
    // Left goal
    paint_zone(left_goal, vga);
    // Right goal
    paint_zone(right_goal, vga);
    // Middle line
    for (int y = field.left_upper_y; y < field.right_lower_y; y++) {
        vga->paint(
            (field.left_upper_x + field.right_lower_x) /2,
            y,
            255
        );
	}
}