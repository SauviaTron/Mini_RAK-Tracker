# I2C Scanning

This program is designed to detect the sensors on the board, each of which is assigned a unique address, as illustrated in the table below. In the case of the LSM303AGR, which incorporates both an accelerometer and a magnetometer, there are four addresses allocated for the three sensors. Notably, there is a distinct address assigned for each of these two components.

<div align="center">
| I2C Address | Description    |
| ----------- | -------------- |
| 0x10        | RGBW Light     |
| 0x19        | Accelerometer  |
| 0x1E        | Magnetometer   |
| 0x76        | Pressure       |
</div>

<div align="center">

COLUMN1 | COLUMN 2 
--- | ---
left | center 
</div>


## Board
![KiCad 3D View Front](/0_GitBook/Images/Kicad_3DViewFront_BnW_Sensors.png)
