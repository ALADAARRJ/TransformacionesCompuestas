# Basic GLUT Template using with VS 2019

This is a basic template to use GLUT under Windows using Visual Studio 2019. The code shows a colored triangle (one different color per vertex), using the legacy OpenGL style. Also, it is base to be used on Visual Studio compiler due that contains

    #pragma comment(lib, "glut32.lib")
at beginning of code. The .lib and .dll are as part of this repo (32 bits version).

The projection is perspective (angle `45`, fov `70`, near `0.001`, far `40`), and the window size is `800x600`. Press `'q'` to exit.

A more complete explanation is written in Spanish in [this link](https://elcodigografico.wordpress.com/2017/07/31/opengl-glut-con-visual-studio-2017/)

###### If you want to contribute to this project and make it better, your help is very welcome.