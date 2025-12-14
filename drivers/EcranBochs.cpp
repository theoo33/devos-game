#include "EcranBochs.h"

#include <hal/fonctionsES.h>
#include <hal/pci.h>
#include <sextant/types.h>
#include <drivers/Ecran.h>

ui8_t* EcranBochs::VRAM;

EcranBochs::EcranBochs(ui16_t width, ui16_t height, VBE_MODE mode): width(width), height(height), mode(mode), topBuffer(false), framebuffer(VRAM) {

}

void EcranBochs::init() {
    Ecran e;
    ui16_t detectScreen = lireRegistre(VBE_INDEX::ID);

    if (detectScreen != 0xB0C5) {
        // error should print to serial port ?
        e.afficherMot("No card found");
    }

    // disable card
    ecrireRegistre(VBE_INDEX::ENABLE, VBE_DISPI_DISABLED);

    // set size & bit depth
    ecrireRegistre(VBE_INDEX::XRES, width);
    ecrireRegistre(VBE_INDEX::YRES, height);
    ecrireRegistre(VBE_INDEX::BPP, mode);

    // set virtual width for double buffering
    ecrireRegistre(VBE_INDEX::VIRT_WIDTH, width);
    ecrireRegistre(VBE_INDEX::X_OFFSET, 0);
    ecrireRegistre(VBE_INDEX::Y_OFFSET, 0);

    // enable screen
    ecrireRegistre(VBE_INDEX::ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
}

void EcranBochs::swapBuffer() {
    ecrireRegistre(VBE_INDEX::Y_OFFSET, topBuffer ? 0 : height);

    if (!topBuffer) {
        framebuffer = VRAM;
    }
    else {
        framebuffer = VRAM + width * height * bytesPerPixel();
    }

    topBuffer = !topBuffer;
}

void EcranBochs::clear(ui8_t color) {
    for (ui16_t y = 0; y < height; y++) {
        for (ui16_t x = 0; x < width; x++) {
            paint(x, y, color);
        }
    }
}

void EcranBochs::clear(ui8_t r, ui8_t g, ui8_t b) {
    for (ui16_t y = 0; y < height; y++) {
        for (ui16_t x = 0; x < width; x++) {
            paint(x, y, r, g, b);
        }
    }
}

ui16_t EcranBochs::getWidth() {
    return width;
}

ui16_t EcranBochs::getHeight() {
    return height;
}

void EcranBochs::set_palette(ui8_t palette_vga[256][3]) {
    ecrireOctet(0, 0x3C8);
    for (int i = 0; i < 256; ++i) {
        ecrireOctet(palette_vga[i][0], 0x3C9);
        ecrireOctet(palette_vga[i][1], 0x3C9);
        ecrireOctet(palette_vga[i][2], 0x3C9);
    }
}



void EcranBochs::paint(unsigned int x, unsigned int y, char color) {
    if (mode == VBE_MODE::_8) {
        ui32_t offset = y * width + x; 
        framebuffer[offset] = color;
    }
}

void EcranBochs::paint(unsigned int x, unsigned int y, ui8_t r, ui8_t g, ui8_t b) {

    switch (mode)
    {
    case _8:
        break;

    case _15:
    case _16: {
        ui16_t color =    ((r & 0x1F ) << (9 + (mode == _16))) 
                        | ((g & (mode == _16 ? 0x3F : 0x1F) ) << 4)
                        | (b & 0x1F); 
        ((ui16_t*)framebuffer)[x + width * y] = color;
        break;
    }
    
    case _24:
        framebuffer[    x + 3 * width * y] = b;
        framebuffer[1 + x + 3 * width * y] = g;
        framebuffer[2 + x + 3 * width * y] = r;
        break;

    case _32:
        ((ui32_t*) framebuffer)[x + width * y] = (r << 16) | (g << 8) | b; 
        break;
    }
}

void EcranBochs::plot_square(int x, int y, int size, ui8_t color) {
    for (int row = 0; row < size; row++) {
        ui32_t base = (y + row) * width + x;
        for (int col = 0; col < size; col++) {
            framebuffer[base + col] = color;
        }
    }
}

void EcranBochs::plot_square(int x, int y, int size, ui8_t r, ui8_t g, ui8_t b) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            paint(x + col, y + row, r, g, b);
        }
    }
}

void EcranBochs::plot_palette(int x, int y, int size) {
    int row, col;
    for (row = 0; row < 16; row++) {
        for (col = 0; col < 16; col++) {
            plot_square(x+col*size,y+row*size,size,row*16+col);
        }
    }
}


void EcranBochs::plot_sprite(void* buffer, ui16_t width, ui16_t height, ui16_t x, ui16_t y) {
    switch (mode)
    {
    case _8: {
        ui8_t * buf = (ui8_t*)buffer;
        for (ui16_t row = 0; row < height; row++) {
            ui32_t base = (y + row) * getWidth() + x;
            for (ui16_t col = 0; col < width; col++) {
                ui8_t color = *buf++;
                if (color != 0) {
                    framebuffer[base + col] = color;
                }
            }
        }
    }
        break;

    case _15:
    case _16: {
        ui16_t * buf = (ui16_t*)buffer;
        for (ui16_t row = 0; row < height; row++) {
            ui32_t base = (y + row) * getWidth() + x;
            for (ui16_t col = 0; col < width; col++) {
                ui16_t color = *buf++;
                if (color != 0) {
                    ((ui16_t*)framebuffer)[base + col] = color;
                }
            }
        }
    }
        break;

    case _24: {
        ui8_t * buf = (ui8_t*)buffer;
        for (ui16_t row = 0; row < height; row++) {
            ui32_t base = ((y + row) * getWidth() + x ) * 3;
            for (ui16_t col = 0; col < width; col++) {
                ui8_t b = buf[0];
                ui8_t g = buf[1];
                ui8_t r = buf[2];
                buf += 3;
                if (r != 0 || g != 0 || b != 0) {
                    framebuffer[base + 3 * col    ] = b;
                    framebuffer[base + 3 * col + 1] = g;
                    framebuffer[base + 3 * col + 2] = r;
                }
            }
        }
    }
        break;

    case _32: {
        ui32_t * buf = (ui32_t*)buffer;
        for (ui16_t row = 0; row < height; row++) {
            ui32_t base = (y + row) * getWidth() + x;
            for (ui16_t col = 0; col < width; col++) {
                ui32_t color = *buf++;
                if (color != 0) {
                    ((ui32_t*)framebuffer)[base + col] = color;
                }
            }
        }
    }
        break;
    
    default:
        break;
    }
}


ui16_t EcranBochs::lireRegistre(VBE_INDEX id) {
    ecrireMot(id, VBE_DISPI_IOPORT_INDEX);
    return lireMot(VBE_DISPI_IOPORT_DATA);
}

void EcranBochs::ecrireRegistre(VBE_INDEX id, ui16_t value) {
    ecrireMot(id, VBE_DISPI_IOPORT_INDEX);
    ecrireMot(value, VBE_DISPI_IOPORT_DATA);
}

ui8_t EcranBochs::bytesPerPixel() {
    if (mode == VBE_MODE::_15) return 2;
    return mode / 8;
}

// Simple 4x8 font bitmap for digits 0-9 and special characters
static const ui8_t digit_font[12][8] = {
    // 0
    {0x0F, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x0F},
    // 1
    {0x02, 0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07},
    // 2
    {0x0F, 0x09, 0x01, 0x02, 0x04, 0x08, 0x08, 0x0F},
    // 3
    {0x0F, 0x09, 0x01, 0x07, 0x01, 0x01, 0x09, 0x0F},
    // 4
    {0x09, 0x09, 0x09, 0x0F, 0x01, 0x01, 0x01, 0x01},
    // 5
    {0x0F, 0x08, 0x08, 0x0F, 0x01, 0x01, 0x09, 0x0F},
    // 6
    {0x07, 0x08, 0x08, 0x0F, 0x09, 0x09, 0x09, 0x0F},
    // 7
    {0x0F, 0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08},
    // 8
    {0x0F, 0x09, 0x09, 0x0F, 0x09, 0x09, 0x09, 0x0F},
    // 9
    {0x0F, 0x09, 0x09, 0x0F, 0x01, 0x01, 0x01, 0x0F},
    // - (minus/dash) at index 10
    {0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00},
    // : (colon) at index 11
    {0x00, 0x02, 0x02, 0x00, 0x02, 0x02, 0x00, 0x00},
};

void EcranBochs::draw_char(unsigned int x, unsigned int y, char c, ui8_t color, int scale) {
    int font_index = -1;
    
    // Map character to font index
    if (c >= '0' && c <= '9') {
        font_index = c - '0';  // 0-9 at indices 0-9
    } else if (c == '-') {
        font_index = 10;  // minus sign at index 10
    } else if (c == ':') {
        font_index = 11;  // colon at index 11
    } else {
        return;  // Unsupported character
    }
    
    const ui8_t* font = digit_font[font_index];
    
    // Draw 4x8 character with scaling
    for (int row = 0; row < 8; row++) {
        ui8_t bitmap = font[row];
        for (int col = 0; col < 4; col++) {
            if (bitmap & (1 << (3 - col))) {
                // Draw scaled pixel as a square
                for (int sy = 0; sy < scale; sy++) {
                    for (int sx = 0; sx < scale; sx++) {
                        paint(x + col * scale + sx, y + row * scale + sy, color);
                    }
                }
            }
        }
    }
}

void EcranBochs::draw_string(unsigned int x, unsigned int y, const char* str, ui8_t color, int scale) {
    int offset = 0;
    while (*str != '\0') {
        draw_char(x + offset, y, *str, color, scale);
        offset += (4 + 1) * scale;  // (4 pixels width + 1 space) * scale
        str++;
    }
}

void EcranBochs::draw_number(unsigned int x, unsigned int y, int num, ui8_t color, int scale) {
    // Handle negative numbers
    if (num < 0) {
        draw_char(x, y, '-', color, scale);
        num = -num;
        x += (4 + 1) * scale;
    }
    
    // Convert number to string and draw
    char buffer[12];
    int pos = 0;
    
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
    } else {
        // Extract digits in reverse order
        int temp = num;
        while (temp > 0) {
            buffer[pos++] = '0' + (temp % 10);
            temp /= 10;
        }
        buffer[pos] = '\0';
        
        // Reverse the string
        for (int i = 0; i < pos / 2; i++) {
            char t = buffer[i];
            buffer[i] = buffer[pos - 1 - i];
            buffer[pos - 1 - i] = t;
        }
    }
    
    draw_string(x, y, buffer, color, scale);
}