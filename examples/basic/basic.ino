/***************************

This is a simple example of how QP framework can be used with the Arduino core.
The example runs a test timer to print log messages to the uart and flashes the onboard LED

The example only contains one active object (the system object)

Note that this has only been tested on arm m0+

!!!YOU WILL PROBABLY NEED TO MODIFY YOUR GCC SCRIPT FOR THIS TO COMPILE PROPERLY!!!

this file is usually located at:
C:\Users\xxx\AppData\Local\Arduino15\packages\arduino\hardware\samd\1.6.14\packages\platform.txt

make sure that the compiler.S flags include the mcpu and mthumb

Example:
compiler.S.flags=-mcpu={build.mcu} -mthumb -c -g -x assembler-with-cpp -MMD

****************************/


#include <Arduino.h>

#include "qpcpp.h"
#include "qp_extras.h"

#include "System.h"
#include "event.h"
#include "bsp.h"

enum {
    EVT_SIZE_SMALL = 32,
    EVT_SIZE_MEDIUM = 64,
    EVT_SIZE_LARGE = 256,
    EVT_COUNT_SMALL = 128,
    EVT_COUNT_MEDIUM = 16,
    EVT_COUNT_LARGE = 4
};
uint32_t evtPoolSmall[ROUND_UP_DIV_4(EVT_SIZE_SMALL * EVT_COUNT_SMALL)];
uint32_t evtPoolMedium[ROUND_UP_DIV_4(EVT_SIZE_MEDIUM * EVT_COUNT_MEDIUM)];
uint32_t evtPoolLarge[ROUND_UP_DIV_4(EVT_SIZE_LARGE * EVT_COUNT_LARGE)];
QP::QSubscrList subscrSto[MAX_PUB_SIG];

static System sys;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  
  // Initialize QP. It must be done before BspInit() since the latter may enable
  // SysTick which will cause the scheduler to run.
  QF::init();
  QF::poolInit(evtPoolSmall, sizeof(evtPoolSmall), EVT_SIZE_SMALL);
  QF::poolInit(evtPoolMedium, sizeof(evtPoolMedium), EVT_SIZE_MEDIUM);
  QF::poolInit(evtPoolLarge, sizeof(evtPoolLarge), EVT_SIZE_LARGE);
  QP::QF::psInit(subscrSto, Q_DIM(subscrSto)); // init publish-subscribe
  
  BspInit();
  
  //Start active objects.
  sys.Start(PRIO_SYSTEM);
  
  //publish a start request
  Evt *evt = new SystemStartReq(0);
  QF::PUBLISH(evt, dummy);
  
  QP::QF::run();
}

