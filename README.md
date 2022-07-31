# PhysiMix

This project is a sound controller for every applications on your windows computer (I didn't try on linux or MacOS)

For this project you will need an Arduino, a potentiometer, a button, a pull-down resistor (I used a 10kΩ but a 1kΩ is enough) and a I2C screen (I used this one: [I2C screen](https://www.amazon.fr/gp/product/B09BFK48GJ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&th=1)).

Create your circuit like this one [Circuit](https://github.com/ThierryBissel/PhysiMix/blob/main/images/Circuit.png)

Upload the ino code on the Arduino and keep  your Arduino connected to the computer. Lauch the program and you can now change  your different apps volume on your PC by using the potentiometer. To change the app press the button the current app is shown on the screen.


NOTE: This project is still in developpement and still have some issues and optimisations to do. In addition this project is only tested on Windows, a Linux version may be available (MacOS version is unlikely to append due to the lack of material ^^')