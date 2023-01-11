#include <system.h>
#include <altera_avalon_pio_regs.h>

int count_manual = 0;
int c0 = 0, c1 = 0, c2 = 0;
int send;

int main(int argc, char *argv[])
{
    while(1){
        if (count_manual < 999){
            count_manual = count_manual + 1;
        }
        else {
            count_manual = 0;
        }

        c2 = count_manual / 100;
        c1 = (count_manual /10) % 10;
        c0 = count_manual % 10;

        send = (c2 << 8) + (c1 <<4) + c0;

        //Write the number on the 7 segment
        IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE,send);
        usleep(100000);
	}

    return 0;
}
