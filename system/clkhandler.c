/* clkhandler.c - clkhandler */

/* avr specific */

#include <xinu.h>

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned int avr_ticks=0;

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */

/* void clkhandler() */

ISR(TIMER0_COMPA_vect)
{

	/* Every ms: What TO DO */

	/* every second */
	/* if avr_ticks == 1000 then 1 second */

	avr_ticks ++;
	if (avr_ticks > 100) {
		avr_ticks=0;


	       /* Increment 1000ms counter */

		count1000++;

		/* After 1 sec, increment clktime */

		if(count1000 >= 1000) {
			clktime++;
			count1000 = 0;
		}

		/* check if sleep queue is empty */

		if(!isempty(sleepq)) {
			/* sleepq nonempty, decrement the key of */
			/* topmost process on sleepq             */

			if((--queuetab[firstid(sleepq)].qkey) == 0) {

				wakeup();
			}
		}

		/* Decrement the preemption counter */
		/* Reschedule if necessary          */

		if((--preempt) == 0) {
			preempt = QUANTUM;
			resched();
		}
	}

}

