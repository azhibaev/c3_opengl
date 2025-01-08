# C³ OpenGL
Draw graph with OpenGL

![Screen 1](https://azhibaev.github.io/images/screen1.png)

## Build in LInux
First, you need to compile the _mod_to_h_ program to get the header files in the _include_ folder from the _*.mod.h_ module files:
```
cd mod_to_h
make mod_to_h
```
Then, compile the _graph3_ program:
```
cd ..
make test/graph3
```
And run the program:
```
test/graph3
```
To move, use the arrows on the additional numeric keypad in numlock mode. The "+" and "-" keys zoom in and out. The "5" key makes the initial scale.
