// Welcome to the OS-Project Kernel.
//
// This code was written by Levi Bradford.
// Created on: December 19, 2018.

#ifndef TERMINAL_H_
#define TERMINAL_H_

void terminal_initialize(void)                                                          // This blanks out the terminal. It uses a loop
{                                                                                       // to get to all the availible spots and fills
        terminal_row            = 0;                                                    // them with ' '. This clears it out.
        terminal_column         = 0;
        terminal_colour = VGA_Colour_Entry(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
        terminal_buffer = (uint16_t*) 0xB8000;                                          // What is terminal buffer doing? I think it is
                                                                                        // an array that corresponds to the map that
        for (size_t y = 0; y < VGA_HEIGHT; y++)                                         // the VGA protocol uses. How does the VGA
        {                                                                               // driver implicitly know that the full table
                for (size_t x = 0; x < VGA_WIDTH; x++)                                  // is set here? This is held at location
                {                                                                       // 0xB8000. VGA drivers will look here.
                        const size_t    index = y * VGA_WIDTH + x;
                        terminal_buffer[index] = VGA_Entry(' ', terminal_colour);       // terminal_buffer is the character location on
                }                                                                       // the screen. BUT WHY?
        }
}

void terminal_put_entry_at(char c, uint8_t colour, size_t x, size_t y)          // This outputs the character specified to the x and y
{                                                                               // coordinates. It also uses the VGA colour standard.
        const size_t index = y * VGA_WIDTH + x;                                 // This is the lowest level of character printing
        terminal_buffer[index] = VGA_Entry(c, colour);                          // availible in this kernelspace. Wow.
}

void terminal_scroll(void)                                                                      // This function allows the kernel to
{                                                                                               // relocate all characters up one line.
        for (size_t newlocation = 0; newlocation <= (VGA_WIDTH*VGA_HEIGHT); newlocation++)      // Pretty cool. How will it be used?
        {                                                                                       // I'm not sure.
                terminal_buffer[newlocation] = terminal_buffer[newlocation + VGA_WIDTH];
        }
}

void terminal_put_char(char c)                                                          // This prints a character at the current
{                                                                                       // location before incrementing the location's
        terminal_put_entry_at(c, terminal_colour, terminal_column, terminal_row);       // position. If it gets to the end of the row
        if (++terminal_column == VGA_WIDTH)                                             // (runs out of column space) it increments the
        {                                                                               // line position (the row it is in) and resets
                terminal_column = 0;                                                    // the column position. If it runs out of lines
                if (++terminal_row == VGA_HEIGHT)                                       // it begins to scroll.
                {
                        terminal_row = terminal_row - 1;
                        terminal_scroll();
                }
        }
}

void terminal_new_line(void)                    // Adds a new line by incrementing the terminal's row. If it is at the bottom, it
{                                               // jump the writing position back to the top of the terminal buffer. Kinda cool.
        terminal_row++;
        if (terminal_row == VGA_HEIGHT)
        {
                terminal_scroll();
                terminal_row = terminal_row - 1;
        }
        terminal_column = 0;
}

void terminal_writestring(const char* data)                     // This function adds support for writing full strings. The kernel
{                                                               // can now write more than one character at a time. I will add newline
        size_t size = strlen(data);                             // support with the '\n' command later. Right now, this is most
        for (size_t i = 0; i < size; i++)                       // similar to a poor man's version of the 'printf' function. Cool.
        {
                if (data[i] != '\n')
                {
                        terminal_put_char(data[i]);
                }
                if (data[i] == '\n')
                {
                        terminal_new_line();
                }
        }
}

#endif
