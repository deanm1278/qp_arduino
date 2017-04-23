///***************************************************************************
// Product: DPP example, STM32 NUCLEO-L152RE board, preemptive QK kernel
// Last updated for version 5.6.5
// Last updated on  2016-07-05
//
//                    Q u a n t u m     L e a P s
//                    ---------------------------
//                    innovating embedded systems
//
// Copyright (C) Quantum Leaps, LLC. All rights reserved.
//
// This program is open source software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Alternatively, this program may be distributed and modified under the
// terms of Quantum Leaps commercial licenses, which expressly supersede
// the GNU General Public License and are specifically designed for
// licensees interested in retaining the proprietary status of their code.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Contact information:
// http://www.state-machine.com
// mailto:info@state-machine.com
//****************************************************************************

#include <string.h>
#include "qpcpp.h"
#include "bsp.h"
#include "Arduino.h"

//Q_DEFINE_THIS_FILE

#define ENABLE_BSP_PRINT

volatile bool initialized = false;

//this is for the arduino core, but it actually never runs
void loop() {
}

void BspInit() {

#ifdef ENABLE_BSP_PRINT
	SERIAL_OBJECT.begin(9600);
	char const *test = "BspInit success\n\r";
	BspWrite(test, strlen(test));
#endif // ENABLE_BSP_PRINT

	initialized = true;
}

void BspWrite(char const *buf, uint32_t len) {
	SERIAL_OBJECT.print(buf);
}

uint32_t GetSystemMs() {
	return millis();
}

extern "C" {
	int sysTickHook(void) {
		//don't run the sched until we've initialized
		if(initialized){
			QXK_ISR_ENTRY();
			QP::QF::tickX_(0);
			QXK_ISR_EXIT();
		}
		return 0;
	}
}

// namespace QP **************************************************************
namespace QP {

// QF callbacks ==============================================================
void QF::onStartup(void) {
	
    // assigning all priority bits for preemption-prio. and none to sub-prio.
    //NVIC_SetPriorityGrouping(0U);
	
	SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);
	NVIC_SetPriority(SysTick_IRQn, SYSTICK_PRIO);
    
    // set priorities of ALL ISRs used in the system, see NOTE00
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!! CAUTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // Assign a priority to EVERY ISR explicitly by calling NVIC_SetPriority().
    // DO NOT LEAVE THE ISR PRIORITIES AT THE DEFAULT VALUE!
    //NVIC_SetPriority(EXTI0_1_IRQn,   DPP::EXTI0_1_PRIO);
    // ...

    // enable IRQs...
    //NVIC_EnableIRQ(EXTI0_1_IRQn);
	
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QXK::onIdle(void) {
    // toggle the User LED on and then off (not enough LEDs, see NOTE01)
    QF_INT_DISABLE();
    //digitalWrite(13, HIGH);       // turn LED[n] on
    //digitalWrite(13, LOW);  // turn LED[n] off
    QF_INT_ENABLE();


#if defined NDEBUG
    // Put the CPU and peripherals to the low-power mode.
    // you might need to customize the clock management for your application,
    // see the datasheet for your particular Cortex-M3 MCU.
    //
    // !!!CAUTION!!!
    // The WFI instruction stops the CPU clock, which unfortunately disables
    // the JTAG port, so the ST-Link debugger can no longer connect to the
    // board. For that reason, the call to __WFI() has to be used with CAUTION.
    //
    // NOTE: If you find your board "frozen" like this, strap BOOT0 to VDD and
    // reset the board, then connect with ST-Link Utilities and erase the part.
    // The trick with BOOT(0) is it gets the part to run the System Loader
    // instead of your broken code. When done disconnect BOOT0, and start over.
    //
    //__WFI();   Wait-For-Interrupt
#endif
}

//............................................................................
extern "C" void Q_onAssert(char const * const module, int loc) {
	//
    // NOTE: add here your application-specific error handling
    //

    QF_INT_DISABLE();
	SERIAL_OBJECT.print("**** ASSERT: ");
	SERIAL_OBJECT.print(module);
	SERIAL_OBJECT.print(" ");
	SERIAL_OBJECT.print(loc);
	SERIAL_OBJECT.println("****");
	while(1);
}

extern "C" void assert_failed(char const *module, int loc) {
	SERIAL_OBJECT.println("assert failed!");
	while(1);
}


} // namespace QP

