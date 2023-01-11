#include <system.h>
#include <altera_avalon_pio_regs.h>

int irq = 0, count_manual = 0;

int main(int argc, char *argv[])
{
    while(1){
        if (count_manual < 9){
            count_manual = count_manual + 1;
        }
        else {
            count_manual = 0;
        }

        //Write the number on the 7 segment
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,count_manual);
        usleep(100000);
	}

    return 0;
}
