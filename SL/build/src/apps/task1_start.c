/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2002, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module       : task1_start.c
 * Description  : Shell TASK routine that toggles the LED2
 * Platform     : e7t
 * History      :
 *
 * 2000-03-27 Andrew N. Sloss
 * - implemented on Evalautor7T
 * - added header and changed the delay time
 *
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "../core/mutex.h"

#include "../headers/api_types.h"
#include "../devices/ddf_io.h"
#include "../LDS2000/devices/ddf_types.h"

#include "../LDS2000/events/swis.h"
#include "../headers/api_device.h"

#define LED 0


/*****************************************************************************
 * STATICS
 *****************************************************************************/

device_treestr *led_host;
UID led;
int ledValue=0;


/*****************************************************************************
 * ROTUINES
 *****************************************************************************/

/* -- openRedLED --------------------------------------------------------------
 *
 * Description   : opens the communication port to the red LED
 *
 * Parameters    : none..
 * Return        : BOOLean - successful | unsucessful 
 * Notes         :
 *
 */

BOOL openLED(void) 
{ 
unsigned int delay;
/* --------------------------------------------------------------
 *
 * eventIODeviceOpen - 
 *
 * open the LED driver node...
 * 
 * --------------------------------------------------------------
 */

led_host = eventIODeviceOpen(&led,DEVICE_LED_LDS2000,LED);


  /* check that a device driver is found ... */

  
  if (led_host==0) {
    while (1) 
    {
    delay=0xBEEF0401;
    };
  return FALSE;
  }
  
  	
return TRUE; 
}

/* -- switchOnRedLED ----------------------------------------------------------
 *
 * Description  : switches on the RED LED
 *
 * Parameter    : none...
 * Return       : none...
 * Notes	:
 *
 */

void switchLED(BYTE value)
{eventIODeviceWriteByte(led_host,led,(BYTE)value);}

/* -- switchOffRedLED ---------------------------------------------------------
 *
 * Description  : switches off the RED LED
 *
 * Parameter    : none...
 * Return       : none...
 * Notes	:
 *
 */

/* -- C_EntryTask1 ------------------------------------------------------------
 *
 * Description  : C entry to Task1
 *
 * Parameter    : none...
 * Return       : none...
 * Notes	:
 *
 * Never terminates
 */

void C_EntryTask1(void)
{
volatile int delay;
  if (openLED()==TRUE)
  {
    while (1) 
    {
	bWAIT;
    	for (delay=0; delay<0x0Affff; delay++) {}
		if(ledValue>=255)
			ledValue=0;
		else ledValue++;
		switchLED((BYTE)ledValue);
    }
  }

  /* 
   * error loop
   */

  while (1) 
  {
  delay=0xBEEF0001;
  };
}

