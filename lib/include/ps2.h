#ifndef PS2_H
#define PS2_H

/* PS2 ATT/CS (attention/select) pin definition - for the DATA/CMD/CLK pins, refer to your SPI interface selection */
#define PS2_PORT_ATT                    4
#define PS2_PIN_ATT                     0
/* wiring for the other three communication pins:
 *  MSP430    PS2
 *   SOMI <-- DATA
 *   SIMO --> CMD
 *   UCLK --> CLK
 */

/* PS2 controller timing configuration - change this if you're having issues */
#define PS2_DELAY_BYTE                  10 // delay duration between ATT becoming active and first byte read/between byte reads (in uS)
#define PS2_DELAY_PACKET                16 // delay duration between packets (between ATT becoming inactive and becoming active again) (in mS) - set to playstation.txt value

extern unsigned char ps2_buffer[32]; // PS2 packet payload transmit/receive buffer (excluding the header of course), 32 bytes long so that in the worst case scenario (16 word transfer, which won't happen anyway) we won't run into buffer overruns

/* helper macros for reading ps2_transfer() return value */
#define ps2_transfer_mode(ret)          ((ret) >> 4)
#define ps2_transfer_words(ret)         ((ret) & 0x0F)

unsigned char ps2_transfer(unsigned char command);
void ps2_init(void);

#endif