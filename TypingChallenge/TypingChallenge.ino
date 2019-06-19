/* Typing Challenge: The game have 4 levels, in each level random words will be appear on screen 
 * players have to press the displayed words in specified time.
 * @Credits
 * ==========================================================================
 * This project is developed by "Ritu Raj", "Avinash" and "Shaopeng"
 * To contact us : "ritu.raj@tu-ilmenau.de" || "avinash.boina@tu-ilmenau.de"
 * ==========================================================================
 */

/* Keyborad mapping
 * Typing Challenge
 */ 
#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <MI0283QT2.h>
#include <PS2Keyboard.h>
#include <GraphicsLib.h>
#include <LiquidCrystal.h>

PS2Keyboard keyboard;
MI0283QT2 lcd;

const int DataPin = 2;
const int IRQpin =  3;

/* Section - user defined parameters
 */
int status = 0;
char keyin, keyout;
String keyout1;
int time_limit;
int points = 0, out = 0;
int fresh = 0;
/***************************************************
****************************************************/


/* Section - arduino setup
*/
void setup() {
  delay(1000);
  /* For German Keyboard use this :
   * keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
   * For English Keyboard use this :
   * keyboard.begin(DataPin, IRQpin);
   */
   
  keyboard.begin(DataPin, IRQpin, PS2Keymap_German);
  lcd.begin();
  Serial.begin(9600);
  randomSeed(analogRead(0));
  gameGreet();
  }
/***************************************************
****************************************************/


/* Section - random character generator
*/
void generateChar() {
      int num = random(0,26);
      num = (num + 97);
      keyout = num;
}
/***************************************************
****************************************************/


/* Section - Game Greetings
 *  
 */
void gameGreet(){
  out = 0;
  lcd.fillScreen(RGB(255,255,255));
  lcd.drawText(10, 10, "Welcome to the Typing Challenge !!!", RGB(255,0,0), RGB(255,255,255), 1); 
  lcd.drawText(0, 60, " Level ", RGB(255,0,0), RGB(255,255,255), 2);
  lcd.drawText(140, 60, "Time Limit", RGB(255,0,0), RGB(255,255,255),2);
  lcd.drawText(0, 90, " (press) 1 :", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(160, 90, " 30 sec", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(0, 105, " (press) 2 :", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(160, 105, " 20 sec", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(0, 120, " (press) 3 :", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(160, 120, " 10 sec", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(0, 135, " (press) 4 :", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(160, 135, " 3 sec", RGB(255,0,255), RGB(255,255,255), 1);
  
  lcd.drawText(10, 180, "Developed By : ", RGB(255,0,0), RGB(255,255,255), 1);
  lcd.drawText(10, 190, " -Ritu Raj", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(10, 200, " -Avinash", RGB(255,0,255), RGB(255,255,255), 1);
  lcd.drawText(10, 210, " -Shopeng", RGB(255,0,255), RGB(255,255,255), 1);
  
  delay(1000);
}
/***************************************************
****************************************************/

/* Section - GamePlay 
*/
void gamePlay(){
  lcd.fillScreen(RGB(255,255,0));
  generateChar(); 
  while (out != 1){
    for( int setTime = time_limit; setTime != 0; setTime--){
      keyout1 = keyout;
      lcd.drawText(10, 20, "Enter the displayed character: ", RGB (255,0,0), RGB (255,255,0), 1);
      lcd.drawText(120, 90, keyout1, RGB (255,0,0), RGB (255,255,0), 3);
      lcd.drawText(10, 190, "***** Remaining Time left *****", RGB (255,0,0), RGB (255,255,0), 1);
      if(setTime < 10){
        lcd.drawText(10, 200, "  ", RGB (255,0,0), RGB (255,255,0), 1);
      }
      lcd.drawInteger(10, 200, setTime, DEC, RGB (255,0,0), RGB (255,255,0), 1);
      if(keyboard.available()){
          keyin = keyboard.read();
          fresh = 1;
      }
      if (fresh == 1 ){
          if (keyin == keyout) {
            points ++;
            generateChar();
            fresh = 0;
            break;
          }
          else {
            out = 1;
            fresh = 0;
            lcd.fillScreen(RGB (255,255,0));
            lcd.drawText(30, 30, "ohhh!, wrong input", RGB (255,0,0), RGB (255,255,0), 1);
            lcd.drawText(30, 50, "You tried very hard, good effort", RGB (255,0,0), RGB (255,255,0), 1);
            lcd.drawText(25, 90, "!Congratulations!", RGB(255,0,255), RGB (255,255,0), 2);
            lcd.drawText(30, 130, "You have scored", RGB (255,0,0), RGB (255,255,0), 2);
            lcd.drawInteger(130, 160, points, DEC, RGB (255,0,0), RGB (255,255,0), 3);
            delay(2000);
            break;
          }
      }
       if (setTime <= 1) {
          out = 1;
          fresh = 0;
          lcd.fillScreen(RGB (255,255,0));
          lcd.drawText(30, 30, "Time's up !, better luck next time", RGB (255,0,0), RGB (255,255,0), 1);
          lcd.drawText(25, 90, "!Congratulations!", RGB(255,0,255), RGB (255,255,0), 2);
          lcd.drawText(30, 130, "You have scored", RGB (255,0,0), RGB (255,255,0), 2);
          lcd.drawInteger(130, 160, points, DEC, RGB (255,0,0), RGB (255,255,0), 3);         
          delay(3000);
      }
    delay(1000);
   }
  }
}
/***************************************************
****************************************************/

void play() {
  lcd.fillScreen(RGB(0,0,0));
  if(keyin == '1'){
    time_limit = 30;
    lcd.drawText(20, 50, "Welcome TO: ", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(20, 70, "Kids mode", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(10, 120, "Time Limit - 30 sec", RGB(255,0,0), RGB(0,0,0), 2);
  } else if(keyin == '2'){
    time_limit = 20;
    lcd.drawText(20, 50, "Welcome TO: ", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(20, 70, "Basic mode", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(10, 120, "Time Limit - 20 sec", RGB(255,0,0), RGB(0,0,0), 2);
  } else if(keyin == '3'){
    time_limit = 10;
    lcd.drawText(20, 50, "Welcome TO: ", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(20, 70, "Advance mode", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(10, 120, "Time Limit - 10 sec", RGB(255,0,0), RGB(0,0,0), 2);
  } else {
    time_limit = 3;
    lcd.drawText(20, 50, "Welcome TO: ", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(20, 70, "Expert/Ninja mode", RGB(255,255,0), RGB(0,0,0), 2);
    lcd.drawText(10, 120, "Time Limit - 3 sec", RGB(255,0,0), RGB(0,0,0), 2);
  }
  delay(3000);
  gamePlay();
  delay(2000);
  gameGreet();
}
/***************************************************
****************************************************/


/* Section - loop logic 
*/
void loop() 
{
    if (keyboard.available() == 1) {
        keyin = keyboard.read();
        fresh = 1;
        if (keyin == '1' or keyin == '2' or keyin == '3' or keyin == '4') {
          fresh = 0;
          //lcd.fillScreen(RGB (255,255,0));
          delay(1000);
          play();
        }
    }
}
