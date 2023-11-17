# BMP280

Sensor configuration is relatively straightforward using [thewknd](https://github.com/thewknd/VEML6040) library. You already have all the functions you need. I've added a few extra features to streamline the final code.

> [!NOTE]
> RGBW Light sensor address is 0x10

## Arduino Output
```
20:16:13.527 ->   VEML6040 - WakeUp
20:16:13.823 ->   R(679) G(637) B(242) W(1021)
20:16:13.868 ->   Ambient light : 20.04
20:16:13.868 ->   Correlated Color Temperature in 260K : 3459
20:16:13.868 ->   VEML6040 - Sleep
20:16:14.865 -> .
20:16:14.865 ->   VEML6040 - WakeUp
20:16:15.177 ->   R(449) G(403) B(153) W(677)
20:16:15.177 ->   Ambient light : 12.68
20:16:15.177 ->   Correlated Color Temperature in 260K : 3291
20:16:15.222 ->   VEML6040 - Sleep
20:16:16.215 -> .
20:16:16.215 ->   VEML6040 - WakeUp
20:16:16.542 ->   R(313) G(253) B(101) W(466)
20:16:16.542 ->   Ambient light : 7.96
20:16:16.542 ->   Correlated Color Temperature in 260K : 2977
20:16:16.542 ->   VEML6040 - Sleep
```

## Board
![KiCad 3D View Front](/0_GitBook/Images/Kicad_3DViewFront_BnW_VEML6040.png)
