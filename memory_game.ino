
#include <LiquidCrystal_I2C.h> 

#define BUZZER_PIN 12

LiquidCrystal_I2C lcd(0x27, 20, 4);// an lcd displayer object 


int leds[4]={2,3,4,5};// defining an array to store pins of the leds 
int buttuns[4]={7,6,8,9};// defining an array to store pins of the buttons


int patern[10]={0,0,0, 0,0,0, 0,0,0,0}; // array to store the patern where the values will be the index of the led to turn on in the array leds
int score=2; // starting at 2 so that the patern shown has 3 leds at least but we will substract the 2 to show the real score 
int typing=0;// 0 to show the patern then switched to 1 to avoid showing it again and give the user the chance to type his answer

int step=0;// how many right clicks the user does 

int level=1; // used to change the speed of the game 


int button1_state=HIGH; // variable for the state of each speed button
int button2_state=HIGH;
int button3_state=HIGH;
int button4_state=HIGH;



void setup() {

  lcd.init(); // initialisation of the displayer
  lcd.clear();
  lcd.backlight(); 

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  randomSeed(analogRead(A0)); // to initialise the random function to generate diffrent number each time 
  patern[0] = random(4); /// the first two steps are random and by defaut shown 
  patern[1] = random(4);
  lcd.print("   WELCOME !!   ");
  delay(1500);


}

void loop() {
  if (typing==0)
  {
    show_patern(score);
  }
  else  {
    button1_state=digitalRead(7); // reading the state of the button 
    button2_state=digitalRead(6);
    button3_state=digitalRead(8);
    button4_state=digitalRead(9);

     
        if (button1_state==LOW) // if the buttun number one is pressed 
        {
              if(patern[step]==0) // if the number in the patern array for the cuurent step is equal to the index of the pressed button 
              {
                correct(); // the answer is correct 
              }
              else {
                wrong();// the answer is wrong 
              }

        }
        else if (button2_state==LOW)
        {
              if(patern[step]==1)
            {
              correct();
            }
            else {
              wrong();
            }
        }
        else if (button3_state==LOW)
        {
              if(patern[step]==2)
              {
                correct();
              }
              else {
                wrong();
              }
        }
        else if (button4_state==LOW)
        {
              if(patern[step]==3)
              {
                correct();
              }
              else {
                wrong();
              }
        }

    
    if (step==(score+1)) // if the number of steps achieved become equal to the current score +1 means that the patern shown and typed match
    {
      if (score<9) // if the score is less than 9 means that we will add another led an stay in the current level 
      {
        congrates();// and show a congratulations message 
      }
      
      typing=0; // now we stop typing we show the the patern with the extra led added to it (if we still i the same level of course )
      step=0; // reset the step number
      score++; // increase the score 
      if (score ==10) // if the score is 10 then the level has ended 
      {
        
        if (level!=3) // if level  is not 3 we pass to the next level
        {
          nailed_it(); // show a nailed it message 
        }
        if (level==3) // if the level is 3 the game ends 
        {
           
          end();// show the end message 
        }

        level++;
      }
    }






  }
  
  delay(100); // Pause avant de recommencer
}


void show_patern(int score) // a function to show the petern 
{
    patern[score]=random(4); // add a led to the patern 
    lcd.clear();
    lcd.print("get ready...");
    delay(1500);
    start_buzz();
    lcd.clear();
    lcd.print("patern ...  ");

    for (int i=0;i<(score+1);i++) // showing the patern by iterating through the patern array 
    {
      int speed=1000-level*250; // defining the speed the game 
      digitalWrite(leds[patern[i]], HIGH); // light up the led that is index in the leds table is: the number that its index is i 
      delay(speed);
      digitalWrite(leds[patern[i]], LOW);
      delay(speed);
    }

    // the end of the patern showing now the user should go ahead and type his answer 
    lcd.clear();
    lcd.print("go ahead !");
    lcd.setCursor(0,1);
    lcd.print("score:");
    lcd.print(score-2);
    lcd.print("   lvl:");
    lcd.print(level);
    go_ahead_buzz();
    typing=1;
}




void correct() // a function to show a message saying correct and the preogress of the typing and in the level 
{
  lcd.clear();
  lcd.print("correct !");
  lcd.setCursor(0,1);
  lcd.print("  [");
  for (int i=0;i<step+1;i++) // show as much "|" as the steps achieved 
  {
    lcd.print("|");
  }
  for (int i=0;i<9-step;i++)
  {
    lcd.print(" ");
  }
  lcd.print("]");

  step++;

  correct_buzz();
}
void wrong() // a function to show a message saying wrong , you lost and the score and the level then restarting the game 
{ 
  lcd.clear();
  lcd.print("wrong !!");

  wrong_buzz();

  delay(100);
  lcd.clear();
  lcd.print("you lost ,sorry!");
  lcd.setCursor(0,1);
  lcd.print("score:");
  lcd.print(score-2);
  lcd.print("   lvl:");
  lcd.print(level);
  delay(3000);
  // reseting the game parametres 
  typing=0;
  score=2;
  level=1;
  patern[0] = random(4);
  patern[1] = random(4);
  lcd.clear();
  lcd.print("try again .");
  delay(2000);


}

void congrates() // a function to show a massage saying congrates and continuing 
{
  lcd.clear();
  lcd.print("congradulations!");
  congrates_buzz();
  delay(1000);
  lcd.clear();
  lcd.print("continuing...");
  delay(1000);
}


void nailed_it() // A function that displays a message saying "You nailed it!" and announces the next level. 
{
  lcd.clear();
  lcd.print("you nailed it!");
  nailed_it_buzz();
  delay(1000);
  lcd.clear();
  lcd.print("NEXT lvl :");
  lcd.print(level+1);
  delay(2000);

  typing=0;
  score=2;
  patern[0] = random(4);
  patern[1] = random(4);
  

}



void end() // a function to announce the end of the game and starting a new game 
{
  lcd.clear();
  lcd.print("wow !!");
  end_buzz();
  delay(1000);
  lcd.clear();
  lcd.print("impressive !!");
  delay(1000);

  lcd.clear();
  lcd.print("   THE END !   ");
  lcd.setCursor(0,1);
  lcd.print("score:");
  lcd.print(score-2);
  lcd.print("   lvl:");
  lcd.print(level);
  delay(2500);
  // starting a new game 
  lcd.clear();
  lcd.print("    New Game    ");
  delay(1000);
// resetting the game parametres 
  typing=0;
  level=1;
  score=2;
  patern[0] = random(4);
  patern[1] = random(4);


}





// functions for the diffirent type of buzzes 
void correct_buzz() {
  // Gradually increasing frequency to indicate a correct answer
  for (int f = 800; f <= 1000; f += 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  // Second frequency rise for confirmation
  for (int f = 1000; f <= 1500; f += 25) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  noTone(BUZZER_PIN);
}

void wrong_buzz() {
  // Decreasing frequency to indicate a wrong answer
  for (int f = 600; f >= 400; f -= 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(400);
  
  noTone(BUZZER_PIN);
}

void start_buzz() {
  // Rising frequency to indicate the start of the game
  for (int f = 1800; f <= 2100; f += 30) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(150);
  
  noTone(BUZZER_PIN);
}

void go_ahead_buzz() {
  // High-pitched ascending tone to indicate progress
  for (int f = 2500; f <= 2800; f += 30) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(150);
  
  noTone(BUZZER_PIN);
}

void congrates_buzz() {
  // First rising tone to initiate the congratulation sound
  for (int f = 400; f <= 500; f += 10) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  // Second rising tone for an uplifting effect
  for (int f = 800; f <= 1200; f += 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  noTone(BUZZER_PIN);
}

void nailed_it_buzz() {
  // Fast frequency rise for a success effect
  for (int f = 700; f <= 1500; f += 50) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  // Small confirmation with a higher note
  tone(BUZZER_PIN, 1800, 200);
  delay(250);
  
  noTone(BUZZER_PIN);
}

void end_buzz() {
  // Low descending tone to mark the end of the game
  for (int f = 1000; f >= 400; f -= 40) {
    tone(BUZZER_PIN, f);
    delay(15);
  }
  delay(200);
  
  // A final echo effect
  tone(BUZZER_PIN, 500, 300);
  delay(350);
  
  noTone(BUZZER_PIN);
}
