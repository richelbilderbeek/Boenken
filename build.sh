#!/bin/bash
cd ..
pwd
ls
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
cd Boenken
qmake BoenkenConsole.pro
make
qmake BoenkenDesktop.pro
make