![screenshot](http://grab.by/grabs/277f5872d206510712c3df084b65ef22.png)

This is a [Chip-8](http://en.wikipedia.org/wiki/CHIP-8) emulator I made back in 2005 as a learning exercise. I recently dug it out and tried compiling on my mac. Lo and behold with only a few simple tweaks (Changed GLUT header file, and use afplay instead of apply) it works!

**To compile:**

gcc -framework GLUT -framework OpenGL *.c -o chip8


**To run:**

./chip8 games/Brix.ch8
