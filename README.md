# THERMOMETER WITH PIC-16

Developers: Berkay Pala, Yusuf Tanrıverdi
            
The project is consists designing a thermometer which has different functionalities that required to be satisfied. We intended to design the circuit on circuit design program, Proteus and first component that we placed is the microcontroller, PIC16F877A.  It has 30 pins; two of them oscillator pins, one of them input voltage pin and other 27 pins can be used as I/O pins with different tasks. One of the significant part of the microcontroller that it is programmable. With deploying a hex extensioned file into the controller, it is possible to configure its pins and perform various operations. We wrote our code in C language on MikroC Pro IDE and then converted into the hex file to deploy it into controller.
The required functionalities when designing the circuit are; 

•	ADC conversion of analog temperature’s voltage value, 

•	Providing two adjustable threshold values and when temperature value does not between these values, there need to be a visual indicator (LED) to demonstrate this condition, 

•	Celcius-to-Fahrenheit conversion of temperature value,

•	Displaying temperature value, threshold values and temperature unit on a 7-segment display.

We used PIC16F877A as the controller. Besides of the controller, we used a 4-digit 7-segment display to display temperature values / threshold values on 3 digits and the unit (Celcius or Fahrenheit) on one digit. Segments (A, B, C, D, E, F, G and DP) are connected to RD pins (0 to 7), digits are connected to the RC pins (0 to 3) and then they configured as output pins via the code. RA pins are configured as input pins and input components are connected to the RA part. We used LM35 as an analog thermometer sensor and connected it to the RA0 pin (which is an analog pin); we used two buttons to provide 4 different display options on 4-digit seven-segment display and connected them to the RA1 and RA2 pins; we used two potentiometers (4k ohm) to be able to determine two different threshold values and connected them to RA3 and RA5 pins. Lastly, a LED is connected to the RC4 pin as a visual indicator which will be used when the temperature value is not between threshold values.



## TEMPERATURE

To read temperature from real-world analogically, LM35 thermometer is used. The LM35 series are integrated-circuit analog thermometers with an analog output voltage linearly-proportional to Centigrade temperature. The value +Vs is the reference voltage and is adjusted to 5 Volt in project. Vout is connected to PORTA’s first pin of PIC16, called A/N converter RA0 pin.  An simple LM35 usage as Centigrade thermometer can be seen on its datasheet[1], where it is connected ground directly and output voltage is seen as  Centigrade per 10.0 mV. 
 
Temperature is read by ADC_read(0) command, which converts analog to digital value according to Equation 1[2]. 
 
𝑉𝑖𝑛 = 𝐴𝐷𝐶𝑅𝑒𝑎𝑑( ) ×  ( (𝑉𝑟𝑒𝑓 +) − (𝑉𝑟𝑒𝑓 −) 2𝑛 − 1 )    (Equation 1) 
 
 
Where Vref is the reference voltage value and n is the number of bits in ADC. The multiplier term is calculated as 𝟓𝟎𝟎𝟎𝐦𝐕/ (𝟐𝟏𝟎 − 𝟏) = 𝟒.𝟖𝟖𝟕𝟔𝟖𝟓𝟓𝟓, hence replaced by that number in the code. Vin is the analog voltage measured by the unit milivolts. Rather than having this value divided by 10mV , we only displayed the first two digits in display function.  For example, the analog voltage output is 0,27176 V when temperature is adjusted 27.0 Celcius degrees. This is 271.7 mV approximately. So, as result of Equation 1, Vin is 271.7 mV. This value is stored into voltage unsigned int variable in code.  
In code, temperature change, along with the possible button pressures and potentiometer adjustmenst, is being checked continuously in an infinite while  loop. Equation 1 is applied as formula. tlong and voltage variables are used.  

In simulation on Proteus we can always increase and decrease temperature by simply putting minus and plus symbol on the device. Changes will be displayed on 7-segment displays immediately. 

Conversion from Celcius to Fahrenheit is being done by formula [3] 
 
𝐹𝑎ℎ𝑟𝑒𝑛ℎ𝑒𝑖𝑡 = 9/5 × (𝐶𝑒𝑙𝑐𝑖𝑢𝑠) + 32  (Equation 2). 
This is done by convertCtoF function defined in the code. We, however, did not add  32 but 320 as we didn’t divide value by 10 mV already.

To change unit displayed on 7-segment displays, we apply the logic of that with two buttons one has four statements, i.e. 00, 01, 11,10. The first two statements are used to change unit of temperature value, from Celcius to Fahrenheit defaultly. That means, 00 is default and assigns unit_flag variable to 0. 

## THRESHOLD 
Setting a threshold interval for an analog value is important for alerts and can provide safety for cases such as excess humidity, pressure, motion and -in this application- temperature rate.  Threshold values are determined via potentiometers and can be displayed on 7-segment displays if button 1 is pressed. Potentiometers are adjustable resistors that can change the potential difference across of them, providing a change in input. To set that values, we set two potentiometers circuits with maximum 4k resistance value: one for low_value and one for high_value. Voltage values are continuosly (i.e. inside infitine loop in the main) read from  RA3 / AN3 and RA5/AN4 pins of PIC16. They are multiplied by 10 to convert centigrad values and then stored as TH1 and TH2 variables. By their order, they are assigned to low and high values. To convert from analog to digital, same procedure that is discussed previous section is applied.  


Whether temperature value read is in between low and high thresholds is checked in thresholding() function. In case of alert, i.e the heat being either excessive or scant, led will be glowed.  This function is operated as an interrupt to provide continous checking. 

## DISPLAY 

As it was stated before, we are using 4-digit 7-segment display, 7SEG-MPX4-CC, to display temperature values, threshold values and unit. After calculating temperature and threshold values, there is a function to divide each digit of the values to store them as a seperate digit to display them in the first three digits of the 7SEG-MPX4-CC. This function thousands digit as a3, hundreds digit as a2 and tens digit as a3.  
 
It is beneficial to recall our example. We have 𝑉𝑖𝑛 = 217.7 𝑚𝑉. Then we have digits as:                     
𝑎1 = (217.7/1000)%10 = 0, 
𝑎2 = (217.7/100)%10 = 2, 
𝑎3 = (217.7/10)%10 = 7. 

As result, 027C will be displayed (default unit is Celcius).  
 
After that, we use these variables in the display function which defines  the digits of the first three digits of the 4-digit 7-segment display as temperature or threshold value and fourth digit of the 4-digit 7-segment display as unit. Note that; unit flag for the fourth is determined in the interrupt part.
 
We used global interrupt to execute functions that mainly about display and to be able to display different values on 7-segment display, we used two buttons to provide four possibilities. If we think buttons’ positions as logically 0 (not pressed) and 1 (pressed), there can be 22  = 4 possibilities: 00, 01, 10, 11. Furthermore, we have also four possible screens, and we mapped screens with the button positions; temperature with celcius (00), temperature with fahrenheit (01), first threshold value (10) and second threshold value (11). Working principle is the buttons are connected to the analog pins and we are reading the analog values of the buttons on main function’s infinite while loop.
 
Then, in the interrupt we seperated all conditions into four different if condition. In 00 condition (first and default), temperature is displayed and the unit flag is zero, which means it is not fahrenheit. In 01 condition (second), temperature is display, but in fahrenheit because the unit flag is set 1 now in that code block.  In 10 condition (third), first threshold value and in 11 condition (fourth) second threshold value is displayed in Celcius degress via digit seperation function and display function. 
 
 

REFERENCES 

[1] https://www.ti.com/document-viewer/LM35/datasheet/revisionhistory#SNIS1593436  
[2] https://www.researchgate.net/post/How_do_you_convert_an_ADC_digitized_ numeric_value_0255_for_8_bit_to_a_voltage 
[3] https://en.wikipedia.org/wiki/Fahrenheit
All the other figures are taken as screenshots or done by hand. The code is our own inspired by lecture notes.

![alt text](https://github.com/yusuftengriverdi/thermometer-with-PIC16/blob/main/Circuit.png?raw=true)
