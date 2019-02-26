# Calculator: The Game Solver

This is a simple program that takes details about a specific level and prints out all possible solutions.

# Usage

The available operations throughout the whole game are as follows:

sig, rev, sum, del, shr, shl, mir, inv, sto
add, sub, mul, div, ndg, pow, ext
rep

In the context of this program, the first row takes no additional numbers, the second row takes one additional number, the third row takes two additional numbers.

The full names and associated buttons are as follows:

sig - (+/-)change sign
rev - (Reverse) reverse number
sum - (SUM) sum of digits
del - (<<) delete digit
shr - (Shift >) shift right
shl - (< Shift) shift left
mir - (Mirror) mirror digits
inv - (Inv10) subtract each digit from 10 mod 10
sto - (Store) use stored number
add - (+ n) add n
sub - (- n) subtract n
mul - (x n) multiply n
div - (/ n) divide n
ndg - (n) new digit
pow - (x^n) raise to power of n
ext - ([+] n) add n to all buttons
rep - (n1 => n2) replace n1 with n2

The input style is shown as follows:
beg;fin;mov;pin;pot;ops;op1_num11_num12;op2_num21_num22;op3_num31_num32;op4_num41_num42;op5_num51_num52;

beg - beginning number
fin - goal number
mov - number of moves allowed
pin - portal in
pot - portal out
ops - number of available operations

When inputting, no spaces can appear in the input; must be one continuous string. All semicolons up to and including the one after ops are required. Explained more below, but if no portals exist in a level, do not fill in, have three semicolons in a row. For operations, only the number specified by ops are needed. If ops = 2 and no portals;

beg;fin;mov;;;ops;op1_num11_num12;op2_num21_num22;

is all that is required. Just like portals, both spaces for numbers are required, that means both underscores and the semicolon after. The following could be the operations section for an inverse button, an add 5 button, and a replace button.

inv__;add_5_;rep_11_22;

The order in which the operations are given does not matter.

## Extra notes

### Store

Note that with sto, as input, it takes no extra numbers, but when printed, it will show one number, this is the number it wants you to have stored and use at that location

### Portals

If no portals, leave blank. If there are portals, use the location number as in the following example (assume the arrows are flipped):

   ^
    123
      ^

pin = 3, pot = 0

# To do

* Add proper commenting