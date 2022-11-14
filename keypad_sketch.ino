#include <LiquidCrystal.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {A0, A1, 12, 10};
byte colPins[COLS] = {9, 8, 7, 6}; 
char keys[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

LiquidCrystal lcd(13, 11, 5, 4, 3, 2); // lcd
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // keypad

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Starting keypad...");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = kpd.getKey();
  if(key) {
    switch (key) {
      case '*':
        break;
      case '#':        
        break;
      default:
        Serial.println(key);
    }

    lcd.setCursor(0, 0);
    lcd.print("Button: ");
    lcd.print(key);
    delay(2000);
    lcd.clear();
  }
}