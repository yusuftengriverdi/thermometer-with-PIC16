# thermometer-with-PIC16

Developers: Berkay Pala

            Yusuf Tanrıverdi
            
The project is consists designing a thermometer which has different functionalities that required to be satisfied. We intended to design the circuit on circuit design program, Proteus and first component that we placed is the microcontroller, PIC16F877A.  It has 30 pins; two of them oscillator pins, one of them input voltage pin and other 27 pins can be used as I/O pins with different tasks. One of the significant part of the microcontroller that it is programmable. With deploying a hex extensioned file into the controller, it is possible to configure its pins and perform various operations. We wrote our code in C language on MikroC Pro IDE and then converted into the hex file to deploy it into controller.
The required functionalities when designing the circuit are; 

•	ADC conversion of analog temperature’s voltage value, 

•	Providing two adjustable threshold values and when temperature value does not between these values, there need to be a visual indicator (LED) to demonstrate this condition, 

•	Celcius-to-Fahrenheit conversion of temperature value,

•	Displaying temperature value, threshold values and temperature unit on a 7-segment display.

Below figure (Figure 1) demonstrates the circuit that designed on the Proteus. As mentioned before, we used PIC16F877A as the controller. Besides of the controller, we used a 4-digit 7-segment display to display temperature values / threshold values on 3 digits and the unit (Celcius or Fahrenheit) on one digit. Segments (A, B, C, D, E, F, G and DP) are connected to RD pins (0 to 7), digits are connected to the RC pins (0 to 3) and then they configured as output pins via the code. RA pins are configured as input pins and input components are connected to the RA part. We used LM35 as an analog thermometer sensor and connected it to the RA0 pin (which is an analog pin); we used two buttons to provide 4 different display options on 4-digit seven-segment display and connected them to the RA1 and RA2 pins; we used two potentiometers (4k ohm) to be able to determine two different threshold values and connected them to RA3 and RA5 pins. Lastly, a LED is connected to the RC4 pin as a visual indicator which will be used when the temperature value is not between threshold values.
