int bH = 6;
int bL = 24;
int wH = 35;
int wL = 15;
int gH = 1;
int gL = 9;
int water = 0;
int ice = 0;
int i = 0;
int t = 0;
int on = 0;
int prev = 0; 
int count = 0;
typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 3;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, OFF, BH, BL, WH, WL, GH, GL };
int SM1_Tick(int state1) {
  switch (state1) { // State transitions
    case SM1_INIT:
      state1 = OFF;
      break;
    case OFF:
      if((analogRead(A1) < 10) && (analogRead(A0) < 10) && water != 1 && ice != 1 && count == 0){
        count = 1;
        state1 = BH;
        on = 1;
      }
      else if(on == 1 && water != 1 && ice != 1){
        state1 = prev;        
      }
      break;
    case BH:
      if(water == 1 || ice == 1){
        state1 = OFF;
        prev = BH;
        break;  
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        prev = BH;
        break;        
      }
      else if( t >= 300){
        state1 = WH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < bH){
        count = 0;
        state1 = BH;        
      }
      else if( i > bH){
        state1 = BL;
        i = 0;
      }
      break;
    case BL:
      if(water == 1 || ice == 1){
        state1 = OFF;
        prev = BL;        
        break;
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        break;        
      }
      else if( t >= 300){
        state1 = WH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < bL){
        state1 = BL;
      }
      else if (i >= bL){
        state1 = BH; 
        i = 0;      
      }
      break;
    case WH:
      if(water == 1 || ice == 1){
        state1 = OFF;
        prev = WH;
        break;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        break;        
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if( t >= 500){
        state1 = GH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < wH){
        state1 = WH;
      }
      else if (i > wH){
        state1 = WL;  
        i = 0;     
      }
      break;
    case WL:
    if(water == 1 || ice == 1){
        state1 = OFF;
        prev = WL;
        break;
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        break;        
      }
      else if( t >= 500){
        state1 = GH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < wL){
        state1 = WL;
      }
      else if (i > wL){
        state1 = WH;  
        i = 0;     
      }
      break;
    case GH:
      if(water == 1 || ice == 1){
        state1 = OFF;
        prev = GH;
        break;
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        break;        
      }
      else if( t >= 200){
        state1 = BH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < gH){
        state1 = GH;
      }
      else if (i > gH){
        state1 = GL;  
        i = 0;     
      }
      break;
    case GL:
      if(water == 1 || ice == 1){
        state1 = OFF;
        prev = GL;
        break;
      }
      else if(on == 0){
        state1 = OFF;
        break;
        t = 0;
        i = 0;
      }
      else if((analogRead(A1) < 10) && (analogRead(A0) < 10)){
        state1 = OFF;
        on = 0;
        break;        
      }
      else if( t >= 200){
        state1 = BH;
        i = 0;
        t = 0;
        break;
      }
      else if(i < gL){
        state1 = GL;
      }
      else if (i > gL){
        state1 = GH;  
        i = 0;     
      }
      break;
  }
  switch (state1) { // State Action
    case SM1_INIT:
      break;
    case OFF:
      digitalWrite(3,LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);      
      break;
    case BH:
      digitalWrite(3, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      i++;
      t++;     
      break;
    case BL:
      digitalWrite(3, LOW);
      i++;
      t++;
      break;
    case WH:
      digitalWrite(5,HIGH);
      digitalWrite(3,LOW);
      //digitalWrite(5, LOW);
      digitalWrite(6, LOW); 
      i++;
      t++;
      break;
    case WL:
      digitalWrite(5, LOW);
      digitalWrite(3,LOW);
      //digitalWrite(5, LOW);
      digitalWrite(6, LOW); 
      i++;
      t++;
      break;
    case GH:
      digitalWrite(6, HIGH);
      digitalWrite(3,LOW);
      digitalWrite(5, LOW);
      //digitalWrite(6, LOW); 
      i++;
      t++;
      break;
    case GL:
      digitalWrite(6,LOW);
      digitalWrite(3,LOW);
      digitalWrite(5, LOW);
      //digitalWrite(6, LOW); 
      i++;
      t++;
      break;      
  }
  return state1;
}

enum SM2_States { SM2_INIT, cOFF, waterTest};
int SM2_Tick(int state2) {
  switch (state2) { // State transitions
    case SM2_INIT:
      state2 = cOFF;
      break;
    case cOFF:
      if(on == 1){
        state2 = waterTest;  
      }
      else{
          if(analogRead(A1) > 10 || analogRead(A0) > 10){
          count = 0;
        }
      }
      break;
    case waterTest:
      state2 = waterTest;
      if(on == 0){
        state2 = cOFF;
      }
      break;

  }
  switch (state2) { // State Action
    case cOFF:
      ice = 0;
      water = 0;
      break;
    case waterTest:
      if(analogRead(A0) < 10){
        digitalWrite(4, HIGH);
        water = 1;
        if(analogRead(A1) < 10 && count == 0){
          on = 0;        
          count = 1;
          digitalWrite(4, LOW);            
        }
        break;
      }
      else{
        digitalWrite(4, LOW);
        water = 0;        
      }
      break;
  }

  return state2;
}

enum SM3_States { SM3_INIT, iOFF, iceTest};

int SM3_Tick(int state3){
  switch (state3){
    case SM3_INIT:
      state3 = iOFF;
      break;
    case iOFF:
      if(on == 1){
        state3 = iceTest;
      }
      break;
    case iceTest:
      state3 = iceTest;
      if(on == 0){
        state3 = iOFF;
      }
      break;
  }
  switch (state3){
    case iOFF:
      ice = 0;
      water = 0;
      break;      
    case iceTest:
      if(analogRead(A1) < 10){
        digitalWrite(2, HIGH);
        ice = 1;
        if(analogRead(A0) < 10 && count == 0){
          on = 0;
          count = 1;
          digitalWrite(2, LOW);          
        }
        break;
      }
      else{
        digitalWrite(2, LOW);
        ice = 0;        
      }
      break;      
  }  
  return state3;      
}  

void setup() {
  // put your setup code here, to run once:
  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 10;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 200;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  delay_gcd = 1000; // GCD
  Serial.begin(9600);
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}
