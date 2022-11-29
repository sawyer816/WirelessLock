#include <LiquidCrystal.h>
#include <Keypad.h>
#include <EMailSender.h>

/**************************************
 *            LCD DISPLAY             *
 **************************************/
LiquidCrystal lcd(13, 11, 5, 4, 3, 2);
int lcdRows = 2;
int lcdCols = 16;
int curRow = 0;
int curCol = 0;

/**************************************
 *              KEYPAD                *
 **************************************/
const byte keypadRows = 4;
const byte keypadCols = 4;
const byte rowPins[keypadRows] = {A0, A1, 12, 10};
const byte colPins[keypadCols] = {9, 8, 7, 6};
const char keys[keypadRows][keypadCols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, keypadRows, keypadCols);

/**************************************
 *          GLOBAL VARIABLES          *
 **************************************/
String pin;
String guess;
int buzzerPin = A5;
bool disabled = false;
int attempts = 0;

/**************************************
 *             RUNS ONCE              *
 **************************************/
void setup()
{
  lcd.begin(lcdCols, lcdRows);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  // set lock's code
  pin = "578112";
  guess = "";

  // send test email
  EMailSender emailSend("cs530projectsender@gmail.com", "Raspberry!530");
  EMailSender::EMailMessage message;
  message.subject = "Soggetto";
  message.message = "Ciao come stai";
  EMailSender::Response resp = emailSend.send("sawyer816@gmail.com", message);

  Serial.println(resp.status);
  Serial.println(resp.code);
  Serial.println(resp.desc);
  delay(1000);

  // startup noise
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 440);
  delay(50);
  tone(buzzerPin, 494);
  delay(50);
  tone(buzzerPin, 523);
  delay(50);
  tone(buzzerPin, 587);
  delay(50);
  tone(buzzerPin, 659);
  delay(50);
  tone(buzzerPin, 698);
  delay(50);
  tone(buzzerPin, 784);
  delay(50);
  noTone(buzzerPin);
  delay(50);

  delay(500);
  lcd.clear();
}

/**************************************
 *          RUNS INDEFINITELY         *
 **************************************/
void loop()
{

  // key received from hardware
  char input = kpd.getKey();
  
  if (input) 
  {

    // lock is disabled
    if (disabled) {
      tone(buzzerPin, 440);
      delay(100);

      noTone(buzzerPin);
    } 
    
    // lock not disabled
    else
    {

      // handle input
      switch (input) 
      {

        // clear input
        case '*':
          curCol = 0;
          guess = "";
          lcd.clear();
          break;

        // test input against lock
        case '#':
          if (guess.equals(pin))
          {
            lcd.setCursor(0, 1);
            lcd.print("UNLOCKED SUCCESSFULLY.");
            attempts = 0;
                        
            noTone(buzzerPin);
            break;

          } else {
            lcd.setCursor(0, 1);
            lcd.print("INCORRECT INPUT.");
            attempts += 1;
            if (attempts >= 3) {
              disabled = true;

              // play disabled tone
              tone(buzzerPin, 147);
              delay(750);
              tone(buzzerPin, 139);
              delay(750);
              tone(buzzerPin, 131);
              delay(750);
              tone(buzzerPin, 124);
              delay(500);

              noTone(buzzerPin);
            } else{
              
              // play incorrect tone
              tone(buzzerPin, 62);
              delay(200);
              tone(buzzerPin, 55);
              delay(150);

              noTone(buzzerPin);
            }
          }

          curCol = 0;
          guess = "";
          delay(300);
          lcd.clear();
          break;

        // display next input
        default:
          int guessLength = guess.length();

          if (guessLength < 6)
          {
            guess.concat(input);

            lcd.setCursor(curCol++, 0);
            lcd.print(input);
            lcd.setCursor(0, 1);
            lcd.print("Pressed: ");
            lcd.print(input);
          }
      }
    }
  }
}