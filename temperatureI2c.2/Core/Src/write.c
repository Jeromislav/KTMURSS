#include "stm32f4xx_hal.h"

// overloaded write function for redirecting output to SWV
int _write(int file, char *ptr, int len)
{
  (void)file;
  int DataIdx;

  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
	ITM_SendChar(*ptr++);	// print to debug port instead
  }
  return len;

  // in project config, under System Core choose SYS and put the Debug into "Trace Asynchronous SW"
  // generate the code

  // copy-paste this _write function to override the weak one in the syscalls.c

  // in debug config use the SWD interface, enable the ST-LINK SN check and press scan
  // (if it cannot scan or when starting the debug it complains about not being able to start the GDB server,
  // powercycle the stm, disable avast and restart the CUBE IDE)
  // then enable the SWD, default clock of 84 is okay

  // to see the output, in Window/Show View/SWV enable the data console
  // start the debug, go to Data Console tab, click the settings icon, put a check on port 0, click ok
  // then enable the trace with the red circle button and resume the program
}
