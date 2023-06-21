// the setup function runs once when you press reset or power the board
#include <EEPROM.h>

#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9

#define LEDL 10
#define LEDM 11
#define LEDR 12

//#define LEDTIMER1 14
//#define LEDTIMER2 15
//#define LEDTIMER3 16
//#define LEDTIMER4 17
//#define LEDTIMER5 18

#define maxCount 500
#define minCount 50
#define stepCount 10

const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int BUTTON3 = 4;
const int BUTTON4 = 5;

int button1State = 0;
int button2State = 0;
int button3State = 0;
int button4State = 0;

int counter;
int currentCount;
bool initial = true;
bool lost_time = false;
int answer = 0;
int last = 0;
int score = 0;
int maxScore = 0;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  pinMode(LEDL, OUTPUT);
  pinMode(LEDM, OUTPUT);
  pinMode(LEDR, OUTPUT);

  //pinMode(LEDTIMER1, OUTPUT);
  //pinMode(LEDTIMER2, OUTPUT);
  //pinMode(LEDTIMER3, OUTPUT);
  //pinMode(LEDTIMER4, OUTPUT);
  //pinMode(LEDTIMER5, OUTPUT);


  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LEDL, LOW);
  digitalWrite(LEDM, LOW);
  digitalWrite(LEDR, LOW);
  //digitalWrite(LEDTIMER1, LOW);
  //digitalWrite(LEDTIMER2, LOW);
  //digitalWrite(LEDTIMER3, LOW);
  //digitalWrite(LEDTIMER4, LOW);
  //digitalWrite(LEDTIMER5, LOW);

  currentCount = maxCount;
  counter = currentCount;
  initial = true;
  lost_time = false;
  score = 0;

  Serial.begin(9600);
  loadMaxScore();
  randomSeed(analogRead(0));
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
}

void loadMaxScore() {
  maxScore = EEPROM.read(0);
  Serial.print("Max score is: ");
  Serial.println(maxScore);
}

int right() {
  if (last == 1) {
    return 2;
  } else if (last == 2) {
    return 3;
  } else if (last == 3) {
    return 4;
  } else {
    return 1;
  }
}

int left() {
  if (last == 1) {
    return 4;
  } else if (last == 2) {
    return 1;
  } else if (last == 3) {
    return 2;
  } else {
    return 3;
  }
}

void lost() {

  //digitalWrite(LEDTIMER1, LOW);
  //digitalWrite(LEDTIMER2, LOW);
  //digitalWrite(LEDTIMER3, LOW);
  //digitalWrite(LEDTIMER4, LOW);
  //digitalWrite(LEDTIMER5, LOW);

  if (score > 0 || !lost_time) {
    Serial.print("Score is: ");
    Serial.println(score);
    if(score > maxScore) {
      maxScore = score;
      EEPROM.write(0, maxScore);
      Serial.print("New max score!");
    }
  }

  currentCount = maxCount;
  counter = currentCount;
  initial = true;
  lost_time = false;
  score = 0;

  int i = 0;

  for (i = 0; i < 3; i++) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LEDL, HIGH);
    digitalWrite(LEDM, HIGH);
    digitalWrite(LEDR, HIGH);
    //digitalWrite(LEDTIMER1, HIGH);
    //digitalWrite(LEDTIMER5, HIGH);
    if (i > 0) {
      //digitalWrite(LEDTIMER2, HIGH);
      //digitalWrite(LEDTIMER4, HIGH);
    }

    if (i > 1) {
      //digitalWrite(LEDTIMER3, HIGH);
    }

    delay (500);
    
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LEDL, LOW);
    digitalWrite(LEDM, LOW);
    digitalWrite(LEDR, LOW);
    //digitalWrite(LEDTIMER1, LOW);
    //digitalWrite(LEDTIMER2, LOW);
    //digitalWrite(LEDTIMER3, LOW);
    //digitalWrite(LEDTIMER4, LOW);
    //digitalWrite(LEDTIMER5, LOW);

    delay(500);
  }

  
}

void chooseLed() {
  int led;

  delay(100);


  if (initial) {
    led = random(1, 5);
    initial = false;
    
  } else {
    led = random(1, 8);
  }

  if (led == 1) {
    digitalWrite(LED1, HIGH);
    answer = 1;
    
  } else if (led == 2) {
    digitalWrite(LED2, HIGH);
    answer = 2;
    
  } else if (led == 3) {
    digitalWrite(LED3, HIGH);
    answer = 3;
    
  } else if (led == 4) {
    digitalWrite(LED4, HIGH);
    answer = 4;
    
  } else if (led == 5) {
    digitalWrite(LEDL, HIGH);
    answer = left();
    
  } else if (led == 6) {
    digitalWrite(LEDM, HIGH);
    answer = last;
    
  } else if (led == 7) {
    digitalWrite(LEDR, HIGH);
    answer = right();
    
  }

  //digitalWrite(LEDTIMER1, LOW);
  //digitalWrite(LEDTIMER2, LOW);
  //digitalWrite(LEDTIMER3, LOW);
  //digitalWrite(LEDTIMER4, LOW);
  //digitalWrite(LEDTIMER5, LOW);

  delay(300);

}

// void ledTimer () {

//   float division = ((currentCount - counter)/(float)currentCount)*6;

//   if (division > 1.0) {
//     //digitalWrite(LEDTIMER1, HIGH);
//   }

//   if (division > 2.0) {
//     //digitalWrite(LEDTIMER2, HIGH);
//   }

//   if (division > 3.0) {
//     //digitalWrite(LEDTIMER3, HIGH);
//   }

//   if (division > 4.0) {
//     //digitalWrite(LEDTIMER4, HIGH);
//   }

//   if (division > 5.0) {
//     //digitalWrite(LEDTIMER5, HIGH);
//   }
  
// }

// the loop function runs over and over again forever
void loop() {
  delay(10);

  counter = counter - 1;

  //ledTimer();

  if (initial) chooseLed();

  button1State = digitalRead(BUTTON1);
  button2State = digitalRead(BUTTON2);
  button3State = digitalRead(BUTTON3);
  button4State = digitalRead(BUTTON4);

  if (button1State == HIGH) {
    if (answer == 1) {
      counter = currentCount;
      if (currentCount > minCount){
        currentCount = currentCount - stepCount;
      }
      last = 1;
      digitalWrite(LED1, LOW);
      digitalWrite(LEDL, LOW);
      digitalWrite(LEDM, LOW);
      digitalWrite(LEDR, LOW);
      score++;
      
      chooseLed();
      
    } else {
      lost();
    }
    
  } else if (button2State == HIGH) {
    if (answer == 2) {
      counter = currentCount;
      if (currentCount > minCount){
        currentCount = currentCount - stepCount;
      }
      last = 2;
      digitalWrite(LED2, LOW);
      digitalWrite(LEDL, LOW);
      digitalWrite(LEDM, LOW);
      digitalWrite(LEDR, LOW);
      score++;

      chooseLed();
      
    } else {
      lost();
    }
    
  } else if (button3State == HIGH) {
    if (answer == 3) {
      counter = currentCount;
      if (currentCount > minCount){
        currentCount = currentCount - stepCount;
      }
      last = 3;
      digitalWrite(LED3, LOW);
      digitalWrite(LEDL, LOW);
      digitalWrite(LEDM, LOW);
      digitalWrite(LEDR, LOW);
      score++;

      chooseLed();
      
    } else {
      lost();
    }
    
  } else if (button4State == HIGH) {
    if (answer == 4) {
      counter = currentCount;
      if (currentCount > minCount){
        currentCount = currentCount - stepCount;
      }
      last = 4;
      digitalWrite(LED4, LOW);
      digitalWrite(LEDL, LOW);
      digitalWrite(LEDM, LOW);
      digitalWrite(LEDR, LOW);
      score++;

      chooseLed();
      
    } else {
      lost();
    }
    
  }

  if (counter == 0) {
    lost_time = true;
    lost();
  }
  
}
