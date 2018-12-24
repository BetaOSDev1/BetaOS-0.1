#ifndef VGA_HEADER_
#define VGA_HEADER_

//#####################################################################################################################################
// DATA:
// This provides easily accessible data for later use. Rather than use a cryptic number, we use a well defined name.
// It serves the same purpose, but is much cleaner. This also provides layers of abstraction for further up the chain.
//#####################################################################################################################################

enum VGA_Colour                                                 // This sets the table of VGA colours. We can call these values
{                                                               // later, by their names, not just a number void of context.
                                                                // I assume they will be handy to continue the shell building
        VGA_COLOUR_BLACK                = 0,                    // process. I plan to add system calls next. Then, I can deal with
        VGA_COLOUR_BLUE                 = 1,                    // the challenge of building a full shell.
        VGA_COLOUR_GREEN                = 2,
        VGA_COLOUR_CYAN                 = 3,
        VGA_COLOUR_RED                  = 4,
        VGA_COLOUR_MAGENTA              = 5,
        VGA_COLOUR_BROWN                = 6,
        VGA_COLOUR_LIGHT_GREY           = 7,
        VGA_COLOUR_DARK_GREY            = 8,
        VGA_COLOUR_LIGHT_BLUE           = 9,
        VGA_COLOUR_LIGHT_GREEN          = 10,
        VGA_COLOUR_LIGHT_CYAN           = 11,
        VGA_COLOUR_LIGHT_RED            = 12,
        VGA_COLOUR_LIGHT_MAGENTA        = 13,
        VGA_COLOUR_LIGHT_BROWN          = 14,
        VGA_COLOUR_WHITE                = 15,

};

static const size_t     VGA_WIDTH = 80;                                 // Sets up the window size of the shell.
static const size_t     VGA_HEIGHT = 25;                                // Can these parameters be changed?

size_t          terminal_row;                                           // Sets the current position of the character to write.
size_t          terminal_column;                                        // A coordinate system, if you will.

uint8_t         terminal_colour;                                        // Store the values returned by VGA_Colour_Entry.
uint16_t*       terminal_buffer;                                        // The VGA charater array. This defines what is on the screen
                                                                        // at any given time. The printing of the charaters is handled
                                                                        // by the graphics processor (GPU or integrated) by default.

//#####################################################################################################################################
// FUNCTIONS:
// These define all the calls that the main program (kernel_main) will make. They provide simple frameworks to
// adhere to. I will continue building this, and eventually make a separate set of files to house the system calls.
// I ommitted the terminal_setcolor function, as it was not called whatsoever. Is this important?
//#####################################################################################################################################


// COLOURS AND VGA STANDARDS #########################################################################################################

static inline uint8_t VGA_Colour_Entry(enum VGA_Colour FG, enum VGA_Colour BG)          // This sets the colours required in a proper
{                                                                                       // format. The bitwise OR compares the two, and
        return  FG      |       BG << 4;                                                // the shift left puts them into the proper bit
}                                                                                       // positions. This is the correct format for
                                                                                        // all systems, not just this one. Very odd,
                                                                                        // but it is now standard CPU convention, as
                                                                                        // defined by the VGA standards.

                                                                                        // The 8 bit integer returned will contain all
                                                                                        // the VGA colouring information for the shell.

static inline uint16_t VGA_Entry(unsigned char UC, uint8_t Colour)      // This sets the current character to be
{                                                                       // printed to the VGA standard. It puts the
        return  (uint16_t) UC   |       (uint16_t) Colour << 8;         // character, along with its respective
}                                                                       // colour in the returned unsigned 16 bit
                                                                        // integer. This is a vital part of the VGA
                                                                        // standard.
#endif
