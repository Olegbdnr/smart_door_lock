#include <Keypad.h>

 // include the library code for LCD
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
 
 // include the library code for Keypad 
 
int Lock = A0;    // relay
int greenLED=A1;  //Green LED
int redLED=A2;    //Red LED

const byte numRows= 4;  //number of rows on the keypad
const byte numCols= 4;    //number of columns on the keypad
 
char keymap[numRows][numCols]= 
{
{'7', '8', '9', '/'}, 
{'4', '5', '6', 'X'}, 
{'1', '2', '3', '-'},
{'C', '0', '=', '+'}
};
 
char keypressed;                 //Where the keys are stored it changes very often
char code[]= {'1','2','3','3'};  //The default code, you can change it or make it a 'n' digits one
 
char check1[sizeof(code)];  //Where the new key is stored
char check2[sizeof(code)];  //Where the new key is stored again so it's compared to the previous one
 
short a=0,i=0,s=0,j=0;   //Variables
 
byte rowPins[numRows] = {0,1,2,3}; //connect to the row pinouts of the keypad
byte colPins[numCols] = {4,5,6,7}; //connect to the column pinouts of the keypad
 
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
 
void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0, 0);
  lcd.print("  THE BRIGHT LIGHT");
  lcd.setCursor(0, 1);
  lcd.print(" Password Door Lock");
  lcd.setCursor(0,2);
  lcd.print(" Press: ");
  lcd.setCursor(0,3);
  lcd.print(" C: Unlock  X:Lock");
  pinMode(Lock, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}
 
void loop()
{
  keypressed = myKeypad.getKey();  //Constantly waiting for a key to be pressed
  if(keypressed == 'C')  // C to open the lock
  {
    Serial.println("Hello");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter Code");   //Message to show
    ReadCode();               //Call the code function
    if(a==sizeof(code))   //The ReadCode function assign a value to a (it's correct when it has the size of the code array)
    {
      OpenDoor();   //Open lock function
    }
    else
    {
      lcd.clear();
      lcd.print("Wrong Password.!!"); //Message to print when the code is wrong
      lcd.setCursor(0,1);
      lcd.print("Press C and Try");
      lcd.setCursor(0,2);
      lcd.print("Again");
      digitalWrite(redLED,HIGH);
      delay(2000);
      digitalWrite(redLED,LOW);
    }
  }

  if(keypressed == 'X')
  {
    lcd.clear();
    digitalWrite(Lock, LOW);
    lcd.print("Locked: Press C To");
    lcd.setCursor(0,1);
    lcd.print("Unlock the Door!!"); 
  }
}

//Function to Get code
void ReadCode()
{
  lcd.setCursor(0,2);
  lcd.print("and Press '='");
  
  //All variables set to 0
  i=0;
  a=0;
  j=0;
  
  while(keypressed != '=')  //The user press = to confirm the code otherwise he can keep typing
  {
    keypressed = myKeypad.getKey();                         
    if(keypressed != NO_KEY && keypressed != '=' ) //If the char typed isn't = and neither "nothing"
    {
      lcd.setCursor(j,1);  //This to write "*" on the lcd whenever a key is pressed it's position is controlled by j
      lcd.print("*");
      j++;
      
      if(keypressed == code[i]&& i<sizeof(code)) //if the char typed is correct a and i increments to verify the next caracter
      {
        a++;
        i++;
      }
      else
      a--;  //if the character typed is wrong a decrements and cannot equal the size of code []
    }
  }
  
  keypressed = NO_KEY;
}

 //Door Opening function
void OpenDoor()
{
  lcd.clear();
  lcd.print("Sucessfull...");
  lcd.setCursor(0,1);
  lcd.print("Unlocked");
  digitalWrite(Lock,HIGH);
  digitalWrite(greenLED,HIGH);
  delay(2000);
  digitalWrite(greenLED,LOW);
  lcd.clear();
  lcd.print("Door is Unlocked.");
  lcd.setCursor(0,2);
  lcd.print("Press X To Lock ");
  lcd.setCursor(0,3);
  lcd.print("The Door"); 
 }

 
