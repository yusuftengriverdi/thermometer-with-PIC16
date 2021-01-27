# thermometer-with-PIC16

Developers: Berkay Pala, Yusuf Tanrıverdi
            
The project is consists designing a thermometer which has different functionalities that required to be satisfied. We intended to design the circuit on circuit design program, Proteus and first component that we placed is the microcontroller, PIC16F877A.  It has 30 pins; two of them oscillator pins, one of them input voltage pin and other 27 pins can be used as I/O pins with different tasks. One of the significant part of the microcontroller that it is programmable. With deploying a hex extensioned file into the controller, it is possible to configure its pins and perform various operations. We wrote our code in C language on MikroC Pro IDE and then converted into the hex file to deploy it into controller.
The required functionalities when designing the circuit are; 

•	ADC conversion of analog temperature’s voltage value, 

•	Providing two adjustable threshold values and when temperature value does not between these values, there need to be a visual indicator (LED) to demonstrate this condition, 

•	Celcius-to-Fahrenheit conversion of temperature value,

•	Displaying temperature value, threshold values and temperature unit on a 7-segment display.

Below figure (Figure 1) demonstrates the circuit that designed on the Proteus. As mentioned before, we used PIC16F877A as the controller. Besides of the controller, we used a 4-digit 7-segment display to display temperature values / threshold values on 3 digits and the unit (Celcius or Fahrenheit) on one digit. Segments (A, B, C, D, E, F, G and DP) are connected to RD pins (0 to 7), digits are connected to the RC pins (0 to 3) and then they configured as output pins via the code. RA pins are configured as input pins and input components are connected to the RA part. We used LM35 as an analog thermometer sensor and connected it to the RA0 pin (which is an analog pin); we used two buttons to provide 4 different display options on 4-digit seven-segment display and connected them to the RA1 and RA2 pins; we used two potentiometers (4k ohm) to be able to determine two different threshold values and connected them to RA3 and RA5 pins. Lastly, a LED is connected to the RC4 pin as a visual indicator which will be used when the temperature value is not between threshold values.

TEMPERATURE

To read temperature from real-world analogically, LM35 thermometer is used. The LM35 series are integrated-circuit analog thermometers with an analog output voltage linearly-proportional to Centigrade temperature. On Figure 4, schematic draw of a 3-pin LM35 model, the one it is used in project, can be seen clearly. The value +Vs is the reference voltage and is adjusted to 5 Volt in project. Vout is connected to PORTA’s first pin of PIC16, called A/N converter RA0 pin.  An simple LM35 usage as Centigrade thermometer can be seen on Figure 5, where it is connected ground directly and output voltage is seen as  Centigrade per 10.0 mV. 
 
Temperature is read by ADC_read(0) command, which converts analog to digital value according to Equation 1[2]. 
 
𝑉𝑖𝑛 = 𝐴𝐷𝐶𝑅𝑒𝑎𝑑( ) ×  ( (𝑉𝑟𝑒𝑓 +) − (𝑉𝑟𝑒𝑓 −) 2𝑛 − 1 )    (Equation 1) 
 
 
Where Vref is the reference voltage value and n is the number of bits in ADC. The multiplier term is calculated as 𝟓𝟎𝟎𝟎𝐦𝐕/ (𝟐𝟏𝟎 − 𝟏) = 𝟒.𝟖𝟖𝟕𝟔𝟖𝟓𝟓𝟓, hence replaced by that number in the code. Vin is the analog voltage measured by the unit milivolts. Rather than having this value divided by 10mV (see Figure 5) , we only displayed the first two digits in display function.  For example, the analog voltage output is 0,27176 V when temperature is adjusted 27.0 Celcius degrees (see Figure 6 for simulation). This is 271.7 mV approximately. So, as result of Equation 1, Vin is 271.7 mV. This value is stored into voltage unsigned int variable in code.  
In code, temperature change, along with the possible button pressures and potentiometer adjustmenst, is being checked continuously in an infinite while  loop. Equation 1 is applied as formula. tlong and voltage variables are used (see Figure 7).  
In simulation on Proteus we can always increase and decrease temperature by simply putting minus and plus symbol on the device. Changes will be displayed on 7-segment displays immediately. 
Figure 
