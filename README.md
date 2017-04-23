# qp_arduino
QP framework for arm core arduino boards

This library allows use of QP framework with QXK kernel with arduino arm core.
It has been tested with the arduino samd core (arm m0+)

<b>!!!YOU WILL PROBABLY NEED TO MODIFY YOUR GCC SCRIPT FOR THIS TO COMPILE PROPERLY!!!</b>

this file is usually located at:
C:\Users\xxx\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.14\packages\platform.txt

make sure that the compiler.S flags include the mcpu and mthumb

Example:
compiler.S.flags=-mcpu={build.mcu} -mthumb -c -g -x assembler-with-cpp -MMD
