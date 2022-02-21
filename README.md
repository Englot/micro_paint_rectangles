# micro_paint-rectangles
ASCII art. A program that will read a configuration-file that contains rectangle parameters to produce a "painting" that is displayed in the terminal using characters.

## Table of contents
* [Introduction](#introduction)
* [Requirements](#requirements)
* [Launch](#launch)
* [Configuration-file](#configuration-file)
* [Example](#example)


## Introduction
Inspired by the 42 coding school exercise "micro_paint" (November 2021).


### Allowed functions
fopen, fread, fscanf, fclose, write, malloc, calloc, realloc, free, memset, powf, sqrtf


### Description
The aim of the exercise is to write a program that will read a "configuration-file" and display the result in the terminal.


#### Configuration-file
The "configuration-file" serves as the "blueprint" for the "drawing".

The first line of the file defines the drawing zone. The program should not display anything outside of it. The format is as follows:
```
WIDTH HEIGHT CHAR
```
* _WIDTH_: The horizontal number of characters to use for the draw zone. An int that has to be bigger than 0 and smaller or equal to 300.
* _HEIGHT_: The vertical number of characters to use for the draw zone. An int that has to be bigger than 0 and smaller or equal to 300.
* _CHAR_: The char used to fill the drawing zone (background).

The following lines of the file define the rectangles to be drawn. The format is as follows:
```
TYPE X Y WIDTH HEIGHT CHAR
```
* _TYPE_: Type of rectangle to be drawn. Two options are possible: 'r' or 'R'. Character 'r' stands for an empty rectangle (only its border is drawn). Whereas the character 'R' stands for a filled rectangle.
* _X_: The horizontal position of the top left corner of the rectangle. It is of type float.
* _Y_: The vertical position of the top left corner of the rectangle. It is of type float.
* _WIDTH_: The width of the rectangle (horizontal). A float bigger than 0.
* _HEIGHT_: The heighth of the rectangle (vertical). A float bigger than 0.
* _CHAR_: The char used to draw the rectangle.

#### Task
The program must take one argument, the path to the "configuration-file".
If the number of arguments doesn't meet these requirements the program must display "Error: argument" followed by a newline in STDOUT.

If any problem occure while you opening or reading the "configuration-file" the program must display "Error: Operation file corrupted" followed by a newline in STDOUT.

The "configuration-file" will contain one operation per line.
If a line is incorrect an error occurs.
If an error has occured the program must return 1.
If no error has occured it must return 0.
The last line of the "configuration-file" can be with or without a newline.
The lines must be read in order and the operations must be executed in the same order.
There must be at least one space between each variable in a line.

The draw zone is divided in rectangles that can contain one character each. They can be seen as "pixels".
Only the top left corner of the "pixels" will be used as point of reference to determine its position.
A "pixel" with a top left corner with a distance bigger or equal than 1 from the border of a rectangle is not part of an empty rectangle. A "pixel" with a top left corner with a distance lower than 1 from the border of a rectangle is part of an empty rectangle.

A point is defined as (Xa, Ya) and a rectangle by its top left corner (Xtl, Ytl) and its bottom right corner (Xbr, Ybr).
If ```Xtl <= Xa <= Xbr``` and ```Ytl <= Ya <= Ybr``` the point lies within the rectangle.


## Requirements
* gcc


## Launch
Compile the program as follows:

```
$ gcc micro_paint.c
```
Run it by giving it the path to the configuration-file as argument (in this case the file "blueprint2" within the directory "examples"):

```
$ ./a.out examples/blueprint2
```


## Example
![grafik](https://user-images.githubusercontent.com/80413516/154947014-ba733665-b516-411c-a596-e69abcea32c1.png)
 _Screenshot of the terminal output using the example configuration-file "blueprint2"_
