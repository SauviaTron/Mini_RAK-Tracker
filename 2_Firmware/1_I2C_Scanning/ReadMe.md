# I2C Scanning

The card is equipped with two low-power LEDs.

The blue LED functions as a user LED and serves solely as an indicator; for example, it can be illuminated when the card is performing calculations.

The white LED is connected to a branch of the GNSS module, specifically the TIMEPULSE pin. This pin is in a high state when the GNSS module receives satellite signals, thus turning on the LED. However, it can also be controlled by the microcontroller.

Therefore, with this pair of LEDs, it is possible to provide the user with different indications based on the illuminated state of the LEDs.

## Hardware Integration

| I2C Address | Description    |
| ----------- | -------------- |
| 0x10        | RGBW Light     |
| 0x19        | Accelerometer  |
| 0x1E        | Magnetometer   |
| 0x76        | Pressure       |

## Board
![KiCad 3D View Front](/0_GitBook/Images/Kicad_3DViewFront_BnW_Sensors.png)
![KiCad 3D View Back](/0_GitBook/Images/Kicad_3DViewBack_BnW_Sensors.png)
