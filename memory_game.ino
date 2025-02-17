
#include <LiquidCrystal_I2C.h> 

#define BUZZER_PIN 12

LiquidCrystal_I2C lcd(0x27, 20, 4);// an lcd displayer object 


int leds[4]={2,3,4,5};
int buttuns[4]={7,6,8,9};


int patern[10]={0,0,0, 0,0,0, 0,0,0,0};
int score=2;
int typing=0;

int step=0;

int level=1;


int button1_state=HIGH; // variable for the state of each speed button
int button2_state=HIGH;
int button3_state=HIGH;
int button4_state=HIGH;



void setup() {

  lcd.init(); // initialisation of the displayer
  lcd.clear();
  lcd.backlight(); // active le rétro-éclairage

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(7, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  randomSeed(analogRead(A0)); // Initialisation de la graine aléatoire
  patern[0] = random(4);
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

     
        if (button1_state==LOW) 
        {
              if(patern[step]==0)
              {
                correct();
              }
              else {
                wrong();
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

    
    if (step==(score+1))
    {
      if (score<9)
      {
        congrates();
      }
      
      typing=0;
      step=0;
      score++;
      if (score ==10)
      {
        
        if (score!=3)
        {
          nailed_it();
        }
        if (level==3)
        {
          
          end();
        }

        level++;
      }
    }






  }
  
  delay(100); // Pause avant de recommencer
}


void show_patern(int score)
{
    patern[score]=random(4);
    lcd.clear();
    lcd.print("get ready...");
    delay(1500);
    start_buzz();
    lcd.clear();
    lcd.print("patern ...  ");

    for (int i=0;i<(score+1);i++)
    {
      int speed=1000-level*250;
      digitalWrite(leds[patern[i]], HIGH);
      delay(speed);
      digitalWrite(leds[patern[i]], LOW);
      delay(speed);
    }
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




void correct()
{
  lcd.clear();
  lcd.print("correct !");
  lcd.setCursor(0,1);
  lcd.print("  [");
  for (int i=0;i<step+1;i++)
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
void wrong()
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
  typing=0;
  score=2;
  level=1;
  patern[0] = random(4);
  patern[1] = random(4);
  lcd.clear();
  lcd.print("try again .");
  delay(2000);


}

void congrates()
{
  lcd.clear();
  lcd.print("congradulation!");
  congrates_buzz();
  delay(1000);
  lcd.clear();
  lcd.print("continuing...");
  delay(1000);
}


void nailed_it()
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



void end()
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

  lcd.clear();
  lcd.print("    New Game    ");
  delay(1000);

  typing=0;
  level=1;
  score=2;
  patern[0] = random(4);
  patern[1] = random(4);


}







void correct_buzz() {
  for (int f = 800; f <= 1000; f += 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  for (int f = 1000; f <= 1500; f += 25) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  noTone(BUZZER_PIN);
}

void wrong_buzz() {
  for (int f = 600; f >= 400; f -= 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(400);
  noTone(BUZZER_PIN);
}

void start_buzz() {
  for (int f = 1800; f <= 2100; f += 30) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(150);
  noTone(BUZZER_PIN);
}

void go_ahead_buzz() {
  for (int f = 2500; f <= 2800; f += 30) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(150);
  noTone(BUZZER_PIN);
}

void congrates_buzz() {
  for (int f = 400; f <= 500; f += 10) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  for (int f = 800; f <= 1200; f += 20) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  noTone(BUZZER_PIN);
}




void nailed_it_buzz() {
  // Montée rapide en fréquence pour un effet de succès
  for (int f = 700; f <= 1500; f += 50) {
    tone(BUZZER_PIN, f);
    delay(10);
  }
  delay(100);
  
  // Petite confirmation avec une note plus aiguë
  tone(BUZZER_PIN, 1800, 200);
  delay(250);
  
  noTone(BUZZER_PIN);
}

void end_buzz() {
  // Son grave descendant pour marquer la fin du jeu
  for (int f = 1000; f >= 400; f -= 40) {
    tone(BUZZER_PIN, f);
    delay(15);
  }
  delay(200);
  
  // Un petit écho final
  tone(BUZZER_PIN, 500, 300);
  delay(350);
  
  noTone(BUZZER_PIN);
}

