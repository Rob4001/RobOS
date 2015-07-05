
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_BLACK     0
#define FB_GREEN     2
#define FB_DARK_GREY 8

#define CONSOLE_WIDTH  80
#define CONSOLE_HEIGHT 25


/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
  char *fb = (char *) 0x000B8000;
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void fb_write_line(char* string, unsigned char fg, unsigned char bg){
  unsigned int i = 0;
  while(string[i]!='\n'){
    fb_write_cell(i*2,string[i],fg,bg);
    i++;
  }
}

    /** fb_move_cursor:
     *  Moves the cursor of the framebuffer to the given position
     *
     *  @param pos The new position of the cursor
     */
    void fb_move_cursor(unsigned short pos)
    {
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT,    pos & 0x00FF);
    }


    void clear_screen(){
      int i = 0;
      while(i < CONSOLE_WIDTH*CONSOLE_HEIGHT){
        fb_write_cell(i*2, ' ', FB_BLACK, FB_BLACK);
        i++;
      }
    }

/* The C function */
void write_welcome()
{
  //fb_write_line("RobOS Initialising...",FB_GREEN,FB_BLACK);
  char string[22] = "RobOS Initialising...";
  unsigned int i = 0;
  while(i < 22){
    fb_write_cell(i*2,string[i],FB_GREEN,FB_BLACK);
    i++;
  }
}
