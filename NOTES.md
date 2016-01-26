2016-01-12
==============
Basic language features in c

operators
------------------

 - arithmetic `+ - * / % ++ --`
 - relational `== != < > <= >=`
 - bitwise `~ & | ^ >> <<`
 - logical `&& || !`
 - conditional `?:`
 - assignment `= += -+ *= /= %=`

operator characteristics
----------------------------
 - arity (unary,binary, ternary)
 - precedence
 - associativity: order in which orperators of the same predecence execute
    
expressions, statements, blocks
------------
 - expression: sequence of operators that resolves to a single value
 - statement: expression terminated by a semi-colon
 - block: sequence of statements between a pair of matches braces { }
 - scope: part of the program where a variable can be used:
    - local: inside a block
    - global: outside blocks

control structures, data structures:
---------
- conditional - if/else
- selective - switch statement
- iterative - for, while, do-while (segfaults often)
- jump - break, continue



2016-01-19
================
commenting
--------------
- you need to document sideeffects of a function: unintended/unexpected
- do not document every line of code or i will CHRISTINE you

section 2:  data representation
----------------------
- 2.1. primitives DTs
- 2.2. compound DTs
- 2.3. pointers

s. 2.1.1 Bit models
-------------------------------
- bit: (0|1)
- byte: 8 consecutive bits
- nibble: 4 consecutive bits; maps to one hexadecimal digit

- base conversion: 
    - binary base 2
    - octal base 8
    - hexadecimal base 16

- magnitude-only bit model
    - unsigned non-negative whole numbers
    - each bit represents non-negative integer power of 2
    - 8 bits → 2^8 ⇒ 256 max val 
    - least significant bits → lowest powers of 2 ("lower order bits")
    - most significant bits → highest powers of 2 ("higher order bits")
    1. unsigned char is 1 byte
    2. unsigned int is 4 bytes (on 32bit arch)
    3. unsigned short int is 2 bytess

- in c **{int, char} is always signed int**

- two's complement
    - positive integers and zero - use magnitude-only bit model
    - negative integers: write bits for positive number; invert; add 1


- fixed point: NOT USED ANYMORE
    - number of digits in fraction are fixed
    - inefficient use of avialable bits
    - fine for fraction powers of 2 but imprecise for powers of 10

- floating point:
    - format: +/- 1.f x 2^e
        

2016-01-21
===============================

- two's complement: only applies when you put in a negative number
    - to reverse, run the procedure again

floating point
----------------------
float 
- 4 bytes

double
- 8 bytes

bitwise operations
-----------------------
- why? store data that is only one bit long; modify
- smallest c data type is 8 bits, so if we have single-bit data, we waste 7 bits
- bitwise ops allow using those 7 bits
- can use bitwise ops on literals and vars
- bit-shift operators are not 'circular'
    - `<< 3` left shift by 3 (adding zeros to end)
    - `>> 2` right shift by 2 
      - (if twos complement, adding sign bit to beginning)
      - (if otherwise, adding zeros to begninng )
                              