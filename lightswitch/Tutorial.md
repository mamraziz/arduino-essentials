# Project description

This is a very simple introductory project making a simple light bulb. Pressing the button turns the LED on and off like any light bulb does. 

You only need: 

1x arduino uno 

1x breadbord 

1x laptop to compile the code 

1x LED 

1x button 

4x jumper cables 

1x 330/220 resistor 

## How to wire it

To make things simple, while you can connect both the button and LED using the many GND headers that are on the uno I recommend connecting them to the -ve blue rail as seen in the photos to make things simpler. But both ways work. 
The LED

The core idea here is to connect the LED to the arduino. To do so we must connect the long leg of the LED to any numbered pin on the arduino (I picked 13 for this example). Then we need to connect the short pin of the LED to the GND. Theoritically this works, but without a resistor the LED will fry and burn. So add a 330 or a 220 resistor on either the long leg or the short leg. In this example the resistor goes in between the GND and the short leg. 
The button

Place the button on the middle of the breadboard so the 'bridge' is under the body. Now take two opposite legs (for example the bottom left leg and top right leg OR the bottom right leg and top left leg), and connect one to GND and one to a numbered pin (for this example it's connected to 12). This is really important, since we are not using a resistor for the button we need to use the arduino's built in 'input_pullup' which is found in the code. 

## Code explanation

You can skip this part, since this is just explaining the code 

The logic behind the code here is that we create a digital 'switch' (our 'on' boolean), which stores the value of whether its supposed to be on or off. 

We have the first if statement checking if the button was pressed, if so it changes it's state (like a physical switch when you click it, it either turns on or off depending on whether it was already on or off). 

 

In the setup() function we first initialize our LED stating that its an output, and use the built in function INPUT_PULLUP for the button. To help with troubleshooting we use Serial.being(9600) so that the serial monitor is available. 

 

You might have realized in the code 'digitalRead()' is checking if it is LOW not HIGH. This is because the built in input_pullup inverts the output, meaning LOW is the new 'HIGH' (basically meaning LOW means a click happened). 

We added a delay since when dealing with hardware components it frequently reads a single click as multiple clicks, so this delay filters out the electrical 'noise' 

We then use two if statements that react to whether our digital switch is on or off. 

## Troubleshooting

First thing you have to make sure of is that you place the jumper cable in the right spot. It is very common to think you connected it to pin 12 to have connected it to pin 11 instead 

The code comes with troubleshooting for the button, open up the serial monitor (Tools > serial monitor) and click on the button to make sure if it even reads the button 

Ensure the LED is wired correctly with the long leg connecting to the numbered pin and the short leg connecting to GND 

If all else fails try a different LED/button. 
