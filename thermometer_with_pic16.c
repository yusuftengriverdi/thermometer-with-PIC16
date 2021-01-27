// '-', 'C' and 'F', characters which will be used on 7-segment display
char neg = 0b01000000;
char cel = 0b00111001;
char fah = 0b01110001;

// This array stores binary bit pattern that will be send to PORTD
unsigned char binary_pattern[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; // without Dp turn
unsigned char display1[10]= {0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xE7};    // with dp turn on

// defining name to each control signal for 7-segment
sbit digit1 at PORTC.B0;
sbit digit2 at PORTC.B1;
sbit digit3 at PORTC.B2;
sbit digit4 at PORTC.B3;

// defining name to led pin
sbit led at PORTC.B4;

// variables to store digits, digital value and output voltage
unsigned int a1,a2,a3,a4; // temporary variables to store data of adc
int adc_value;            //store output value from Analog Read functoion
unsigned int number;
long tlong;
unsigned int voltage;

// variables to store buttons' analog values
int button1_value;
int button2_value;
int unit_flag = 0;

// variables to store threshold values read from potentiometer
int threshold_value1;
int threshold_value2;
unsigned int TH1;
unsigned int TH2;
unsigned int LOW_value;
unsigned int HIGH_value;

// this function retrive each digita that will displayed on device
void get_digits(unsigned int value)
  {
           a1 =  (value/1000u)%10u;  // holds first digit
           a2 = ((value/100u)%10u);  // holds second digit
           a3 = ((value/10u)%10u);   // holds third digit
   }

// this function displays measured voltage on seven-segments
void display_voltage()
{
            PORTD=binary_pattern[a1];  // send unit place data to 1st digit
            digit1 = 0;  //  turn on 1st display unit
            delay_ms(3);
            digit1 = 1;  //  turn off 1st display unit

            PORTD = binary_pattern[a2]; // send 1000's place data to fourth digit
            digit2 = 0;   //  turn on forth display unit
            delay_ms(3);
            digit2 = 1;   //  turn off forth display unit

            PORTD = binary_pattern[a3];  // send 100's place data to 3rd digit
            digit3 = 0;    //  turn on 3rd display unit
            delay_ms(3);
            digit3 = 1;  //  turn off 3rd display unit

            if (unit_flag !=0) {PORTD = fah;}
            else PORTD = cel;
            digit4 = 0;
            delay_ms(3);
            digit4 = 1;
}
   
unsigned int convertCtoF(unsigned int temp)
{
   temp = (9 * temp / 5 ) + 320 ;
   return temp;
}

void thresholding()
{
     if(voltage < LOW_value || voltage > HIGH_value)
     {
           led = 1;
           delay_ms(3);
     }
     else {led = 0; delay_ms(3);}
}

void interrupt()
{
     thresholding();
     
     if(button1_value ==0 && button2_value == 0) 
     { 
       delay_ms(10);
       unit_flag = 0;
       get_digits(voltage);
       display_voltage();
     }
     if(button1_value ==0 && button2_value != 0)
     { 
       delay_ms(10);
       voltage=convertCtoF(voltage);
       unit_flag = 1;
       get_digits(voltage);
       display_voltage();
     }
     if(button1_value !=0 && button2_value == 0)
     {  
        delay_ms(10);
        unit_flag = 0;
        get_digits(TH1);
        display_voltage();
      }
     if(button1_value !=0 && button2_value != 0)
     { 
       delay_ms(10);
       unit_flag = 0;
       get_digits(TH2);
       display_voltage();
     }


  T0IF_bit = 0;  // clear source of timer0 interrupt
}

void main(void)
{
    TMR0   = 0;         // timer0 reset bit
    OPTION_REG = 0x83;  // select prescalar value 1:16 for timer0
    INTCON = 0xA0;      // turn on global interrupt and timer0 overflow interrupt
    TRISD = 0x00;       //define PORTD as a output port
    PORTD=0x00;         // initialize PORTD pins to active low
    TRISC=0x00;         // Set PORTB as a output port
    PORTA=0x00;
    TRISA=1;
    // set control pins pins initially active high
    digit1 = 1;
    digit2 = 1;
    digit3 = 1;
    digit4 = 1;
    // set led pin initally active low
    led = 0;
    
    while(1)
    {

            adc_value = ADC_Read(0);  // read data from channel 0
            button1_value = ADC_Read(1);  // read data from channel 1
            button2_value = ADC_Read(2);  // read data from channel 2
            tlong = (float)adc_value*4.88768555; //converts voltage into temperature
            voltage = tlong;

            
            // read data from potentiometers
            threshold_value1 = (float) ADC_Read(3)*4.88768555;
            threshold_value2 = (float) ADC_Read(4)*4.88768555;
            TH1 = threshold_value1 * 10;
            TH2 = threshold_value2 * 10;
            
            if (TH1 < TH2)
            {
             LOW_value = TH1;
             HIGH_value = TH2;
            }
            else if (TH2 < TH1)
            {
             LOW_value = TH2;
             HIGH_value = TH1;
            }
    }

}