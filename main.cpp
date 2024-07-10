#include "mbed.h"

/*

            Sample code for testing MSB Motor Driver Board

    Controls the speed of a motor attached to the MSB Motor Driver Board.
    The speed can be varied by changing the position of the potentiometer connected 
    to "POT AN INPUT" on the left side of the Module Support Board  

    Title:          MSB Motor Driver Test
    Author:         Andrew Norris
    Institution:    Plymouth University
    Date:           10/07/24
    Version:        1.0

*/


PwmOut driver(PC_6);    // The motor driver connects to PC6
AnalogIn pot(PA_0);     // The potentiometer connects to PA0

float prev_duty=0.0f;


int main()
{
    driver.period_ms(10);               // Set the PWM rate to 100Hz

    while (true) {
        float duty = pot.read();        // Sample the value of the potentiometer
        if (duty != prev_duty){         // Check to see if it has changed
            if(duty<0.05){              // Remove noise from low value readings
                duty = 0.0;
            }
            driver.write(duty);         // Update the PWM duty cycle
            prev_duty = duty;           // Save the new duty value to compare to next sample
        }                               

        ThisThread::sleep_for(200ms);    // Crudely control the refresh rate (5Hz)
    }
}

