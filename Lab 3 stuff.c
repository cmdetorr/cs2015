
/*
// ACTIVITY 1: Programming PWM Module to Generate Periodic 
// Output Waveforms with Varying Duty Cycle/Frequencies
In HCS12, the PWM module can be programmed to generate periodic waveforms on 8 channels 
of the PORTP output pins with different periods and duty cycles. In this lab exercise, 
you will develop a program that can read the voltage from a potentiometer 
(e.g., the on-board potentiometer used in previous labs) and use the value to change 
the PWM period, or the duty cycle of the waveform as follows:

1. Produce a 60Hz square waveform on PP5 such that its duty cycle can be varied 
   by an input coming from the potentiometer.
   
2. Connect PP5 to the buzzer.

// ACTIVITY 2: Open-loop Speed Control of a DC Motor using PWM and H-Bridge

Using the PWM module of HCS12 and the onboard H-bridge, develop a program that reads
an analog input voltage in the range 0 to 5V (from a potentiometer, e.g., VR2 on the
board) and converts it to a proportional speed that is applied to a 9V DC motor.

*/

// I've made a change to this

const unsigned char seven_seg[16] = {0x3F,0x06, 0x5B, 0x4F, 0x66,
                                     0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
									 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
									 
const unsigned char PWM_PERIOD = 256;
volatile unsigned char PWM_DUTY = 128;		// This is a number between 0 - 256 (0% - 100%)

void Initialize(void);

void main(void){
	unsigned char ADC_val;
	
	// Initialize routine
	Initialize();
	
	while(1==1){
		// Read from the ADC
		ATD0CTL5 = 0x87; 				// Channel 7 (right justified, unsigned, single-conversion)
		while(!(ATD0STAT0 & 0x80));		// Wait for the conversion to finish

		// Display ADC value on Port J LED's
		ADC_val = ATD0DR0L;
		PORTB = ADC_val;
		
		// Change the PWM duty cycle for  on that value
		PWM_DUTY = ADC_val;
	}
	
	while(1==1); // Stay here when the program ends
}//endmain

void Initialize(){
	// General IO Initialization
	DDRB = 0xFF; 	//Set PORTB as output
	DDRJ = 0xFF; 	//Set PTJ as output for Dragon12+ LEDs
	PTJ = 0x0; 		//Enable LEDs to display data on PORTB pins
	DDRT = 0x20; 	//Make PTT5 output for buzzer

	// ADC Initialization
	ATD0CTL2 = 0x80; 	//Turn on ADC and possibly wait awhile
	ATD0CTL3 = 0x08; 	//One conversion, no FIFO
	ATD0CTL4 = 0xEB; 	//Set resolution to 8 bits, frequency, etc
	
	// PWM Initialization
	// Port P 5 is connected to clock A. PWM Channel 5
	PWMPRCLK = 0x04; 	// Divide the Prescaler for CLK_A by 4. CLK_A = Fbus/16 . The most signficant nibble controls A. Fbus/(2^n) where n is a number between 0 - 7
	PWMSCLA = 125;		// Use Clock A / (2x125)
	PWMCLK = 0x20;		// Use CLK_A on channel 5
	PWMPOL = 0x20;		// Active high output for channel 5
	PWMCTL = 0x00;		// Left align PWM
	PWMPER5 = PWM_PERIOD;		// PWM freq = CLK_A / PWM_PERIOD = about 60Hz
	PWDTY5 = PWM_DUTY;			// 50% duty cycle
	PWMCNT5 = 0;		// clear counter
	PWME = 0x20;		// Enable PWM channel 5
}//end Initialize()


/*
The purpose of this function is to read from the 
*/

/*
interrupt (((0x10000-Vrti)/2)-1) void RTI_ISR (void) {
	countValue++; //Increment counter
	x=countValue/10;
	d1=countValue%10;
	d2=x%10;
	d3=x/10;
	CRGFLG = CRGFLG | CRGFLG_RTIF_MASK; //Clear flag
}
*/