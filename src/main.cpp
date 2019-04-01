/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

/*
 * CURRENT STATE:
 * 
 * Ugh, I started out with just C, then moved to C++ and took some concepts.
 * It's still cleaner than the old preprocessor firmware, in my opinion,
 * but I do need to go back through at some point and redefine a
 * bunch of my interfaces.
 *
 * 3-Channel ADC is theoretically working,
 *
 * Overall TODO:
 * - Change peak detector timing to microseconds from milliseconds
 * - Get UAVCAN integrated/working
 * - Clear out old variable changing stuff (there's only really 4 or 5 necessary ones)
 *
 * Long term stuff:
 * - Write USB library and integrate into comms
 */
#include <stdbool.h>

// Uncomment for four ADC channels vs 3
//#define ADC_FOUR_CHANNELS

#include "stm32f3xx.h"
#include "main.h"
#include "clocks.h"
#include "comms.h"
#include "timers.h"
#include "gain_control.h"
#include "dma.h"
#include "uart.h"
#include "adc.h"

CommInterface* comm_interface;

// Flags
bool ping_started = false;
bool ping_active = false;

// Input buffers
uint16_t channel_ref_buffer[SAMPLE_LEN];
uint16_t channel_a_buffer[SAMPLE_LEN];
uint16_t channel_b_buffer[SAMPLE_LEN];
#ifdef ADC_FOUR_CHANNELS
uint16_t channel_c_buffer[SAMPLE_LEN];
#endif

static void check_incoming_message();

int main(void)
{
	// Initialize clocks
	systemclock_config();
	periph_clocks_init();

	// Peripheral init
	setup_adc_gpio();
	trigger_timer_init();
	setup_adc();
	setup_dma();

	I2C i2c(1, 100000, 42);

	MCP3021 peak_adc(i2c.get_i2c_handle(), 72);
	Filter band_pass_filter(i2c);
	*comm_interface = CommInterface();


	gain_control_init(&peak_adc);


	band_pass_filter.setCenterFreq(27);
	comm_interface->setFilterPointer(band_pass_filter);
	// Set method to write out over communications interface
	comm_interface->writeOut = uart_send;

	/*
	 * Currently, this will run a transfer every 2s, and do nothing with it
	 *
	 * First steps are probably to piggyback and use signals from existing teensy.
	 *
	 * Once that's verified working, we can pull the peak detector signal and
	 * implement everything in here.
	 *
	 * Program flow plan: (why am I writing python?)
	 * Everything in main should be async, meaning we should be able to do other useful
	 * stuff if we are waiting for something to complete.
	 * Maybe implement a state machine? idk
	 *
	 * Init
	 *
	 * loop:
	 * 		handle_gain_control
	 * 		if (ping_complete):
	 *				for buffer in buffers:
	 *						wait for previous buffer to finish transferring
	 *						convert first x samples to float
	 *						start_sending (sets up CAN_DONE interrupt)
	 *						finish converting to float
	 *
	 * CAN_DONE_IRQ:
	 * 		send next n values in frame
	 *
	 *
	 * handle_gain_control:
	 * 			do gain stuff, idk
	 * 			start sampling once we have stable signal
	 */
	while(1) {
		// Start pulling ADC values if we have a ping
		// This should actually go in peak detection/gain control
		if (ping_started) {
			dma_start_xfer();
			trigger_timer_start();

			// Don't call this loop again
			ping_started = false;
			ping_active = true;
		}

		check_incoming_message();

		gain_control_run();
	}
}

static void check_incoming_message() {
	if (receive_finished_flag) {
		// If we are finished receiving, parse message
		comm_interface->parseMessage(incoming_message);
		incoming_message_len = 0; // Reset length so reception can work
		receive_finished_flag = false; // Done receiving, lower flag
	}
}