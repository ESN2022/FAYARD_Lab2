#include <system.h>
#include <altera_avalon_pio_regs.h>
#include <sys/alt_irq.h>
#include <sys/alt_sys_init.h>
#include <alt_types.h>
#include <altera_avalon_timer_regs.h>
#include <altera_avalon_timer.h>
#include <unistd.h>
#include <sys/alt_stdio.h>


int count = 0;
int irq = 0;
int c0 = 0, c1 = 0, c2 = 0;
int send;

static void timer_ISR (void * context, alt_u32 id)
{
    //Counter
    if (count < 999){
        count = count + 1;
    }
    else {
        count = 0;
    }

    //Irq flag raised
    irq = 1;

	//Clear the interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0x00);
}

int main(int argc, char *argv[])
{
    //Clear the interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0x00);

	//Settle parameters : continous count, IRQ request + Start
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE , ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | ALTERA_AVALON_TIMER_CONTROL_START_MSK | ALTERA_AVALON_TIMER_CONTROL_ITO_MSK);

	//Register the ISR to the corresponding interrupt
	alt_irq_register (TIMER_0_IRQ , NULL, (void*) timer_ISR);

    while(1){
        //If a change occured
        if (irq == 1){
            c2 = count / 100;
            c1 = (count /10) % 10;
            c0 = count % 10;

            send = (c2 << 8) + (c1 <<4) + c0;

            //Write the number on the 7 segment
            IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,send);
            usleep(100000);

            //Irq flag down
            irq = 0;
        }
	}

    return 0;
}
