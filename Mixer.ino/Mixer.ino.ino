#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String Processus[40];
int ProcessusLenght = 0;
int CurrentProcessus = 0;
bool firstRota = true;
String currentList = "";
String dataShow = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(4, INPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  int volume = value * (100 / 1023.0);
  int button = digitalRead(4);

  String val;



  while (Serial.available() > 0) {
    val = Serial.readStringUntil(';');

    int first = 4;

    if (currentList != val) {
      currentList = val;
      if (val.substring(3)) {
        int index = val.indexOf(",", first);
        while (index <= val.length() - 1) {
          String processus = val.substring(first, index);
          first = val.indexOf(",", first) + 1;
          index = val.indexOf(",", first);
          if (firstRota) {
            firstRota = false;
          } else {
            ProcessusLenght += 1;
          }
          Processus[ProcessusLenght] = processus;
        }
      }
    }
  }

  unique();

  if (button == 1) {
    incrementImage();
  }

  showCurrentProcessus();

  Serial.print(Processus[CurrentProcessus]);
  Serial.print(";");

  Serial.println(volume);
  delay(500);
}

void incrementImage() {
  if (CurrentProcessus == ProcessusLenght) {
    CurrentProcessus = 0;
  } else {
    CurrentProcessus++;
  }
}

void showCurrentProcessus() {
  String text = Processus[CurrentProcessus];
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Processus:");
  display.setCursor(0, 15);
  display.print(text);
  display.print("   ");
  display.print(CurrentProcessus);
  display.print("/");
  display.print(ProcessusLenght);
  display.display();
}

void unique() {
  for ( int i = 0; i < ProcessusLenght; i ++)
  {
    for ( int j = i + 1; j < ProcessusLenght; j++)
    {
      // use if statement to check duplicate element
      if ( Processus[i] == Processus[j])
      {
        // delete the current position of the duplicate element
        for ( int k = j; k < ProcessusLenght - 1; k++)
        {
          Processus[k] = Processus [k + 1];
        }
        // decrease the size of array after removing duplicate element
        ProcessusLenght--;

        // if the position of the elements is changes, don't increase the index j
        j--;
      }
      int lenght = Processus[i].length();
      if ( lenght <= 3)
      {
        // delete the current position of the duplicate element
        for ( int k = j; k < ProcessusLenght - 1; k++)
        {
          Processus[k] = Processus [k + 1];
        }
        // decrease the size of array after removing duplicate element
        ProcessusLenght--;

        // if the position of the elements is changes, don't increase the index j
        j--;
      }
    }
  }
}
