// Welcome to the OS-Project Kernel.
//
// This code was written by Levi Bradford.
// Created on: December 19, 2018

#ifndef KERNEL_FUNCTIONS_
#define KERNEL_FUNCTIONS_

size_t strlen(const char* str)          // This is a function that calculates the length of any input string.
{                                       // It uses a loop, along with the array of characters to find the length.
        size_t len = 0;                 // This value is returned as a size_t. (size_t is a format of number that
        while (str[len])                // contains a tally of the number of bytes in any specified object. In this
                len++;                  // case, a string's total number of characters.)
        return len;
}

int exponent(int base, int power)               // The mathematical exponent function. If you don't know what this is. Google it.
{                                               // It should be self explanatory, but the function takes the base and power values,
        int i, result = 1;                      // then returns the correct result.
        for (i = 0; i < power; i++)
                result *= base;
        if (power == 0)
        {
                result = 1;
        }
        return result;
}

char* integer_to_chars(int integ)                                       // Converts integers under 1 billion to an array of characters
{                                                                       // rather poorly. I can't figure out how to improve this, but
        int max = 0;                                                    // the algorithm needs a major rewrite.
        int power = 0;
        char* outer = {(char*) '0'};
        integ = integ + 1;
        for (int digit = 8; digit >= 0; digit--)
        {
                power = exponent(10, digit);
                for (int current = 0; current <= 9; current++)
                {
                        if (integ > (power*current))
                        {
                                max = current;
                        }
                }
                outer[10 - digit] = (char) max + '0';
                integ = integ - (power*max);
        }
        outer[0] = '0';
        outer[1] = '0';
        outer[11] = '\0';
        for (int set = 0; set < 13; set++)
        {
                if ((outer[0]) == '0')
                {
                        for (int mover = 0; mover < 13; mover++)
                        {
                                outer[mover] = outer[mover+1];
                        }
                }
        }
        return outer;
}

char* chars_adder(char* first, char* second)
{
        char* sum = 0;
        int len1 = strlen(first);
        int len2 = strlen(second);
        for (int position = 0; position <= len1; position++)
        {
                sum[position] = first[position];
        }
        for (int position2 = 0; position2 <= len2; position2++)
        {
                sum[position2 + len1] = second[position2];
        }
        return sum;
}

#endif
