#include "display.h"
#include "display_macros.h"


#include <stdint.h>
#include <avr/io.h>

// The initialisation for the display pins and SPI peripheral  
void display_init(void)
{
    // PB1 = global display enable
    PORTB.DIRSET = PIN1_bm;
    PORTB.OUTSET = PIN1_bm;

    // PA1 = display latch
    PORTA.DIRSET = PIN1_bm;
    PORTA.OUTCLR = PIN1_bm;

    // Route SPI0 to alternate pins on PORTC
    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;

    // PC0 = SCK, PC2 = MOSI, PC3 = SS
    PORTC.DIRSET = PIN0_bm | PIN2_bm | PIN3_bm;
    PORTC.OUTSET = PIN3_bm;

    SPI0.CTRLB = 0;
    SPI0.INTCTRL = 0;

    SPI0.CTRLA = SPI_MASTER_bm | SPI_ENABLE_bm;
}

// Leveraging the spi peripheral for sending the segments and success and failure patterns on the 7 segment display 
void spi_display(uint8_t data)
{
    SPI0.DATA = data; // data is for the segment display macros mentioned in display_macro.h and the score board values in output.c 

    // Polling is used instead of SPI interrupts because display writes are short and blocking.
    while (!(SPI0.INTFLAGS & SPI_IF_bm))
    {
        ;
    }

    SPI0.INTFLAGS = SPI_IF_bm;

    PORTA.OUTSET = PIN1_bm;
    PORTA.OUTCLR = PIN1_bm;
}



    volatile uint8_t display_left = DISP_OFF;
    volatile uint8_t display_right = DISP_OFF;


// Refreshes one side of the multiplexed display.
// Called every 5 ms by timer.c, alternating between left and right digits at speed  which makes both appear to the human eye. This is used in the success and failure patterns 
void display_flicker(void)
{

    static uint8_t show_left = 0; // Remembers which side we showed last

    if (show_left) 
    {
        // Bit 7 = 1 (Left Digit Select), Bits 0-6 = Segment Pattern
        spi_display(DISP_LHS | display_left);
    } 
    else 
    {
        // Bit 7 = 0 (Right Digit Select), Bits 0-6 = Segment Pattern
        spi_display(display_right);
    }

    // Toggle for the next 5ms tick
    show_left = !show_left;

}

// updating the segments patterns on the display 
void update_display(uint8_t left, uint8_t right)
{
    display_left = left;
    display_right = right;
}