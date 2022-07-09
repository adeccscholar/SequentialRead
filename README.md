# SequentialRead
Example for the evolution of C++ to read a sequantial file with C++

This project contains the prepared examples for the lecture "Evolution of C++ using a (very) simple example". The task was to read in a larger sequential file in the national character set.

You find the lecture here: https://www.youtube.com/watch?v=2Vw273Rxyh8

There are several variants showing the evolution, each provided for Embarcadero and Visual Studio. Thereby the independent parts are in separate folders, and should also be usable with any other C++ compiler.

The Classic C++ App use the chrono library for measuring to make all variants comparable. When you want use this project with an old compiler should you use the boost time library  instead.

Attention: Data are not part of this project and have a separate license.
The used file "berlin_infos.dat" is about 10 years old and was provided in the context of OpenData under the license "Datenlizenz Deutschland - Namensnennung - Version 2.0" https://www.govdata.de/dl-de/by-2-0. It still contains the internationally used WGS84 coordinates.  
For this program is the location of the file in directory d:\\test. You need to change this when you adapt this program on your computer. You find the file in this repository in the directory ./Data.

