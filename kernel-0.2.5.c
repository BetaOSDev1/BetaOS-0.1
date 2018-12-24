// Welcome to the OS-Project Kernel.
//
// This code was written by Levi Bradford.
// Created on: December 5, 2018.
//
// This is the first piece of code executed after the bootloader. This has basic text printing functionality.
// I am working on building a set of system libraries for kernel calls. This will significantly expedite the
// coding process. The components to be added, in order, are: User input, system calls, shell capability, 64
// bit mode, gcc ports, networking, and much much more.

//#####################################################################################################################################
// INCLUDES:
// This provide the only availible libraries to the "free C" compiler.
//#####################################################################################################################################

#include <stdbool.h>						// The kernel can make use of these basic system calls.
#include <stddef.h>						// stdbool.h controls basic boolean operations. stddef.h handles
#include <stdint.h>						// the definition of new functions. stdint.h is basic integer
								// control libraries. All other functions must be defined by the
								// kernel itself. Can I call other .c files? What about other .h?

// #include "login-0.2.5.h"
#include "VGA_header-0.2.5.h"
#include "kernel_functions-0.2.5.h"
#include "terminal_header-0.2.5.h"
// #include "boot_header-0.2.5.h"
// #include "scheduler_loops-0.2.5.h"

// HELPERS ###########################################################################################################################

void boot_start(void)
{
	terminal_initialize();
	terminal_writestring("Project 41 - Beta 0.2.4\n");
	terminal_writestring("All Rights Reserved\n");
	terminal_new_line();
}

void terminal_prompt(char* user, char* device, char* present_directory)
{
	terminal_colour = VGA_Colour_Entry(VGA_COLOUR_LIGHT_GREEN, VGA_COLOUR_BLACK);
	terminal_writestring(chars_adder(chars_adder(user, "@"), device));
	terminal_colour = VGA_Colour_Entry(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
	terminal_writestring(":");
	terminal_colour = VGA_Colour_Entry(VGA_COLOUR_LIGHT_BLUE, VGA_COLOUR_BLACK);
	terminal_writestring(present_directory);
	terminal_colour = VGA_Colour_Entry(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
	terminal_writestring("$ ");
	// User input
	terminal_new_line();
}

//#####################################################################################################################################
// KERNEL:
// The place where it all begins! Hoory for us! We made a bootable kernel. It only took ~3 hours. Pretty slow for scripting standards,
// but for OS development, that is exeptional! Yay us.
//#####################################################################################################################################

void kernel_main(void)				// Where execution starts!
{
	boot_start();
	// login
	char* u = "levibradford";		// Removed after login is added
	char* d = "computer";			// Ditto
	char* p = "/home/levi";			// Ditto
	// initialize
	// start scheduler			// sheduler starts default program (bash)
						// any kernel call will call sys_call_evalute();
						// this will decide what to do.
	terminal_prompt(u, d, p);
}
