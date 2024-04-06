// GREENWOOD LABORATORY SCHOOL
// MATTHEW WHITWORTH / Joaquin Parada
// ROBOT TOUR
// C05 EAGLES


// RULE CLARIFICATION ALLOWING USB CABLES
// https://www.soinc.org/once-programming-changes-are-made-impounded-program-can-modified-program-be-downloaded-over-wifi-or 


// TARGET TIME
int timesecondstoachieve = 50;

// E; L, R, F1, S, Q, P, O
String combinationstring = "ERSRSRSLSSLSSF1";
// ERPRSSLRSRLSSOF1

// STEPS PER 1000
int numberofsteps = 10000;

// LONGER STRAIGHT - P - FIRST
int numberofstepsfront = 11000;

// SHORTER STRAIGHT - O - SECOND
int numberofstepsend = 9000;

// REVERSE DISTANCE
int numberofstepsenter = 2700;

// DEGREES PER 100
int numberofturns23 = 2300;

// MINIMUM VALUES
float min50straight = 5;
float min50turn = 2;
int minmotorvalue = 700;
int delaybetweenmicrosteps = 700;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// TIME VARIABLES!
int execspersecond = 100;
int currenttimeinexecs = 0;
int currenttimeinseconds = 0;
int linestoplot = 0;
float delayinmicroseconds = 800;
int maxminstepperdelay[2] = { 800, 14000 };
int execsperloop[6] = { 11000, 11000, 11000, 11000, 11000, 11000 };
int speeddelay[6] = { 1000, 1000, 1000, 1000, 1000, 100 };
bool startedchecks = false;
int stepnumberinprogram = 0;


// MAX, MIN (SECONDS)
float leftturnspeed[2] = { 10, 2 };
float straightturnspeed[2] = { 10, 2 };
float rightturnspeed[2] = { 10, 2 };
float finalturntheoretical[2] = { 10, 2 };


// SERIAL VARIABLES
int nS;
boolean newData = false;
const byte numChars = 128;  // EXTENDED TO 128
char receivedChars[numChars];
String i2csend1 = "none";
String i2csend2 = "none";
String i2csend3 = "none";
String i2csend4 = "none";
String receivedSerial3000 = "none";



//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////

// DEFINING PIN OUTPUTS
#define STATUSLED 2    // GREEN LED IN CENTER
#define LEFTLED 3      // LEFT BLUE LED
#define STRAIGHTLED 4  // WHITE LED IN CENTER
#define RIGHTLED 5     // RIGHT RED LED
#define PVLED1 6       // UNDERNEATH LED
#define REVERSELED 7
#define TURNPLUS 10
#define TURNMINUS 11
#define ledpin 13     // ledpin ON MB
#define USBDMINUS 16  // USB - PLUG
#define USBDPLUS 17   // USB + PLUG
#define USBIDPLUS 18  // USB - ID SHIELD
#define USBSHIELD 19  // USB SHIELD
#define M1IN1 22
#define M1IN2 23
#define M1IN3 24
#define M1IN4 25
#define M2IN1 26
#define M2IN2 27
#define M2IN3 28
#define M2IN4 29
#define M3IN1 30
#define M3IN2 31
#define M3IN3 32
#define M3IN4 33
#define M4IN1 34
#define M4IN2 35
#define M4IN3 36
#define M4IN4 37
#define LEFTBUTTON 38
#define RIGHTBUTTON 39
#define STRAIGHTBUTTON 40
#define REVERSEBUTTON 41
#define FINAL1BUTTON 42
#define FINAL2BUTTON 43
#define TENSECONDPLUS 44
#define TENSECONDMINUS 45
#define ONESECONDPLUS 46
#define ONESECONDMINUS 47
#define RESETBUTTON 48
#define MODIFIERPLUS 49
#define MODIFIERMINUS 50
#define PVLEDHIT1 51      // DEBUG LED ON TOP FOR PV1
#define PVLEDHIT2 52      // DEBUG LED ON TOP FOR PV2
#define PVLEDHIT3 8      // DEBUG LED ON TOP FOR PV3
#define PVLEDHIT4 9      // DEBUG LED ON TOP FOR PV4
#define STARTANALOG A4    // ANALOG LED ON TOP
#define PVSENSOR1 57      // ANALOG PVSENSOR1
#define PVSENSOR2 58      // ANALOG PVSENSOR2
#define PVSENSOR3 59      // ANALOG PVSENSOR3
#define PVSENSOR4 60      // ANALOG PVSENSOR4
#define STARTBUTTONON 61  // START BUTTON ON


// ANALYZING BUTTON PRESSES TO CREATE STRINGS AND THE OTHER STUFF
bool lbinitial;
bool rigbinitial;
bool sbinitial;
bool revbinitial;
bool f1initial;
bool f2initial;
bool tspinitial;
bool tsminitial;
bool ospinitial;
bool osminitial;
bool resinitial;
bool mpinitial;
bool mminitial;
bool tpinitial;
bool tminitial;


int steplength = 50;
bool overrideonce = false;

bool lbpressed = true;
bool rigbpressed = true;
bool sbpressed = true;
bool revbpressed = true;
bool f1pressed = true;
bool f2pressed = true;
bool tsppressed = true;
bool tsmpressed = true;
bool osppressed = true;
bool osmpressed = true;
bool respressed = true;
bool mppressed = true;
bool mmpressed = true;
bool tppressed = true;
bool tmpressed = true;



//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////
//////////////////////////____________________________________________________________________________________/////////////////////////////


// WATCHDOG VARIABLES AND TROUBLESHOOTING VARIABLES
bool watchdogactivated = false;

// TOTAL NUMBER OF STEPS
int totalstepnumber;

// CURRENT STEP
int currentstepnumber;

// NEED TO STOP?
bool needstostop = false;

// ERROR NUMBERS
int error;

// PHOTOVOLTAIC SENSOR ANALOG STATUS
int PVStatus1;
int PVStatus2;
int PVStatus3;
int PVStatus4;

// PV SENSOR ON/OFF
bool PVstate1 = false;
bool PVstate2 = false;
bool PVstate3 = false;
bool PVstate4 = false;

// MOTOR STATES
bool moto1in1state;
bool moto1in2state;
bool moto1in3state;
bool moto1in4state;
bool moto2in1state;
bool moto2in2state;
bool moto2in3state;
bool moto2in4state;
bool moto3in1state;
bool moto3in2state;
bool moto3in3state;
bool moto3in4state;
bool moto4in1state;
bool moto4in2state;
bool moto4in3state;
bool moto4in4state;

// FINAL STEP
bool finalstep = false;

// STEP STRING ARRAY
String pathroute[100];

// TOTAL LEFTS AND RIGHTS
int numberoftimes[6] = { 0, 0, 0, 0, 0, 0 };

// STEPPERMOTORDECISIONENGINE VARIABLES
String currentdecision;
bool leftturn;
bool straightturn;
bool rightturn;
bool reverseturn;
bool finalturn;
bool finalstepdone;

// STEPPERMOTORACTIVATIONENGINE VARIABLES
int loopnumberexectime = 0;

// DEBUG VARIABLES
bool batteryprotectionoverrive = true;





////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS///////////////////////////////////////////////////////////////////

// SETUP LOOP
void setup() {
  // START THE DEBUG SERIAL PROTOCOL
  Serial.begin(115200);

  // DEBUG SERIAL
  Serial.println(F("STARTING"));

  // PINMODES
  pinMode(STATUSLED, OUTPUT);
  pinMode(LEFTLED, OUTPUT);
  pinMode(STRAIGHTLED, OUTPUT);
  pinMode(RIGHTLED, OUTPUT);
  pinMode(PVLED1, OUTPUT);
  pinMode(REVERSELED, OUTPUT);
  pinMode(PVSENSOR1, INPUT);
  pinMode(PVSENSOR2, INPUT);
  pinMode(PVSENSOR3, INPUT);
  pinMode(PVSENSOR4, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(STARTBUTTONON, INPUT_PULLUP);
  pinMode(M1IN1, OUTPUT);
  pinMode(M1IN2, OUTPUT);
  pinMode(M1IN3, OUTPUT);
  pinMode(M1IN4, OUTPUT);
  pinMode(M2IN1, OUTPUT);
  pinMode(M2IN2, OUTPUT);
  pinMode(M2IN3, OUTPUT);
  pinMode(M2IN4, OUTPUT);
  pinMode(M3IN1, OUTPUT);
  pinMode(M3IN2, OUTPUT);
  pinMode(M3IN3, OUTPUT);
  pinMode(M3IN4, OUTPUT);
  pinMode(M4IN1, OUTPUT);
  pinMode(M4IN2, OUTPUT);
  pinMode(M4IN3, OUTPUT);
  pinMode(M4IN4, OUTPUT);
  pinMode(LEFTBUTTON, INPUT_PULLUP);
  pinMode(RIGHTBUTTON, INPUT_PULLUP);
  pinMode(STRAIGHTBUTTON, INPUT_PULLUP);
  pinMode(REVERSEBUTTON, INPUT_PULLUP);
  pinMode(FINAL1BUTTON, INPUT_PULLUP);
  pinMode(FINAL2BUTTON, INPUT_PULLUP);
  pinMode(TENSECONDPLUS, INPUT_PULLUP);
  pinMode(TENSECONDMINUS, INPUT_PULLUP);
  pinMode(ONESECONDPLUS, INPUT_PULLUP);
  pinMode(ONESECONDMINUS, INPUT_PULLUP);
  pinMode(RESETBUTTON, INPUT_PULLUP);
  pinMode(MODIFIERPLUS, INPUT_PULLUP);
  pinMode(MODIFIERMINUS, INPUT_PULLUP);
  pinMode(PVLEDHIT1, OUTPUT);
  pinMode(PVLEDHIT2, OUTPUT);
  pinMode(PVLEDHIT3, OUTPUT);
  pinMode(PVLEDHIT4, OUTPUT);
  pinMode(STARTANALOG, INPUT);
  pinMode(TURNPLUS, INPUT);
  pinMode(TURNMINUS, INPUT);

  // SET ALL PINS TO LOW!!!
  digitalWrite(STATUSLED, LOW);
  digitalWrite(LEFTLED, LOW);
  digitalWrite(STRAIGHTLED, LOW);
  digitalWrite(RIGHTLED, LOW);
  digitalWrite(PVLED1, LOW);
  digitalWrite(REVERSELED, LOW);
  digitalWrite(ledpin, LOW);
  digitalWrite(M1IN1, LOW);
  digitalWrite(M1IN2, LOW);
  digitalWrite(M1IN3, LOW);
  digitalWrite(M1IN4, LOW);
  digitalWrite(M2IN1, LOW);
  digitalWrite(M2IN2, LOW);
  digitalWrite(M2IN3, LOW);
  digitalWrite(M2IN4, LOW);
  digitalWrite(M3IN1, LOW);
  digitalWrite(M3IN2, LOW);
  digitalWrite(M3IN3, LOW);
  digitalWrite(M3IN4, LOW);
  digitalWrite(M4IN1, LOW);
  digitalWrite(M4IN2, LOW);
  digitalWrite(M4IN3, LOW);
  digitalWrite(M4IN4, LOW);
  digitalWrite(PVLEDHIT1, LOW);
  digitalWrite(PVLEDHIT2, LOW);
  digitalWrite(PVLEDHIT3, LOW);
  digitalWrite(PVLEDHIT4, LOW);

  // DELAY IN MILLISECONDS
  delay(120);

  // MOTOR STATES OFF
  moto1in1state = false;
  moto1in2state = false;
  moto1in3state = false;
  moto1in4state = false;
  moto2in1state = false;
  moto2in2state = false;
  moto2in3state = false;
  moto2in4state = false;
  moto3in1state = false;
  moto3in2state = false;
  moto3in3state = false;
  moto3in4state = false;
  moto4in1state = false;
  moto4in2state = false;
  moto4in3state = false;
  moto4in4state = false;

  // DEBUG SERIAL
  Serial.println(F("FINISHED PINMODE STARTUP"));

  // DELAY IN MILLISECONDS
  delay(120);

  // DEBUG SERIAL
  Serial.println(F("FINISHED STARTUP CHECKS"));

  // PLEASE WORK!!!
  if (setupstringloop == "") {
    setupstringloop();
  } else {
    targettimeanalysis();
  }
  

  delay(100);
  watchdogactivated = false;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MAIN RHETORICAL LOOP
void loop() {
  int LEDRESET = 0;
  int startinganalog = analogRead(STARTANALOG);

  delay(100);
  Serial.print(startinganalog);
  Serial.println(F(" + WAITING"));
  delay(100);

  // OPERATING CONDITIONS
  if (startinganalog <= 400) {
    bool completion113 = false;
    String nextcharacter = "";
    int nextstepletter = 0;
    bool sbutton = true;

    analogRead(STARTANALOG);
    delay(250);
    if (startinganalog >= 450) {
      return;
      return;
    }
    while (completion113 == false && sbutton != false) {
      sbutton = digitalRead(STRAIGHTBUTTON);
      nextcharacter = combinationstring.substring(nextstepletter, nextstepletter + 1);
      if (nextcharacter == "E") {
        eENTERING();
        Serial.println(F("entering code"));
        delay(10);
      }
      if (nextcharacter == "R") {
        eRIGHT();
        Serial.println(F("RIGHT CODE"));
        delay(10);
      }
      if (nextcharacter == "L") {
        eLEFT();
        Serial.println(F("LEFT CODE"));
        delay(10);
      }
      if (nextcharacter == "S") {
        eSTRAIGHT();
        Serial.println(F("STRAIGHT CODE"));
        delay(10);
      }
      if (nextcharacter == "Q") {
        eREVERSE();
        Serial.println(F("REVERSE CODE"));
        delay(10);
      }
      if (nextcharacter == "F") {
        eFINALONE();
        completion113 = true;
        Serial.println(F("COMPLETED!"));
        delay(2000);
        nextcharacter = " ";
        sbutton = true;
      }
      if (nextcharacter == "P") {
        eFIRSTRAIGHT();
        Serial.println(F("ENTER FIRST STRAIGHT"));
        delay(10);
      }
      if (nextcharacter == "O") {
        eFINALSTRAIGHT();
        Serial.println(F("FINAL STRAIGHT"));
        delay(10);
      }
      nextstepletter = nextstepletter + 1;
    }
    delay(3000);
  }


  delay(100);
  startinganalog = 1000;

  // RESET BACK INTO SETUP BUTTONS
  int finalreset = digitalRead(FINAL1BUTTON);
  if (finalreset == 0) {
    digitalWrite(PVLEDHIT1, HIGH);
    digitalWrite(PVLEDHIT2, HIGH);
    digitalWrite(PVLEDHIT3, HIGH);
    digitalWrite(PVLEDHIT4, HIGH);

    // RESET VARIABLES
    f1pressed = true;
    combinationstring = "";
    int timesecondstoachieve = 50;
    int steplength = 50;
    bool overrideonce = false;

    delay(100);
    setupstringloop();
  }
}

void pvhit() {
  PVStatus1 = analogRead(PVSENSOR1);
  PVStatus2 = analogRead(PVSENSOR2);
  PVStatus3 = analogRead(PVSENSOR3);
  PVStatus4 = analogRead(PVSENSOR4);

  delay(1);

  //  PVLED1 HIT STATUS
  if (PVStatus1 > 600) {
    PVstate1 = true;
    digitalWrite(PVLEDHIT1, HIGH);
  } else {
    PVstate1 = false;
    digitalWrite(PVLEDHIT1, LOW);
  }

  // PVLED2 HIT STATUS
  if (PVStatus2 > 600) {
    PVstate2 = true;
    digitalWrite(PVLEDHIT2, HIGH);
  }

  // PVLED3 HIT STATUS
  if (PVStatus3 > 600) {
    PVstate3 = true;
    digitalWrite(PVLEDHIT3, HIGH);
  }

  // PVLED4 HIT STATUS
  if (PVStatus4 > 600) {
    PVstate4 = true;
    digitalWrite(PVLEDHIT4, HIGH);
  }

  delay(1);
}

void LEDEngine() {
  digitalWrite(STATUSLED, LOW);
  digitalWrite(LEFTLED, LOW);
  digitalWrite(STRAIGHTLED, LOW);
  digitalWrite(RIGHTLED, LOW);
  digitalWrite(PVLED1, LOW);
  digitalWrite(REVERSELED, LOW);
  digitalWrite(ledpin, LOW);
  digitalWrite(PVLEDHIT1, LOW);
  digitalWrite(PVLEDHIT2, LOW);
  digitalWrite(PVLEDHIT3, LOW);
  digitalWrite(PVLEDHIT4, LOW);
}

void targettimeanalysis() {
  // NEW TARGET TIME ANALYSIS
  digitalWrite(ledpin, LOW);
  bool FINISHED = false;
  int analyzedization = 0;
  int straightmoves = 0;
  int turnmoves = 0;
  int timerdelay6000 = 0;
  while (FINISHED != true && timerdelay6000 != 1000) {
    String toanalyze = combinationstring.substring(timerdelay6000, timerdelay6000 + 1);

    delay(100);

    // ANALYZE 
    if (toanalyze == "S" || toanalyze == "R" || toanalyze == "P" || toanalyze == "O") {
      straightmoves = straightmoves + 1;
    }
    if (toanalyze == "L" || toanalyze == "R") {
      turnmoves = turnmoves + 1;
    }
    if (toanalyze == "F") {
      FINISHED = true;
      Serial.println(F("THIS IS TRUE"));
    }
    if (toanalyze == "1") {
      FINISHED = true;
      Serial.println(F("THIS IS TRUE"));
    }
    if (toanalyze == "E") {
      
    }
    timerdelay6000 = timerdelay6000 + 1;
  }

  int mod = steplength;
  numberofsteps = 10000 / 50 * steplength;

  // TIME FOR DIFFERENT THINGS
  float mintimestraight = min50straight * steplength / 50;
  float mintimeturn = min50turn;

  // COMBINED TIME FOR EACH
  float timestraight = mintimestraight * straightmoves;
  float timeturns = mintimeturn * turnmoves;

  int totaltimerequired = timestraight + timeturns;

  delay(1000);

  float multiplierrequired = timesecondstoachieve / totaltimerequired;

  if (totaltimerequired >= timesecondstoachieve || totaltimerequired == 0 || timestraight == 0) {
    Serial.println(F(""));
    delaybetweenmicrosteps = minmotorvalue;
  } else {
    Serial.println(totaltimerequired);
    delaybetweenmicrosteps = 800 * multiplierrequired;
  }
  Serial.println(F("TIME REQUIRED"));
  Serial.println(delaybetweenmicrosteps);
  Serial.println(F("MULTIPLIER"));
  Serial.println(multiplierrequired);
  digitalWrite(ledpin, HIGH);
}

void eSTRAIGHT() {
  Serial.println(F("QWERTY - STRAIGHT"));
  bool completion229 = false;
  int stepnumber229 = 0;
  
  // DEBUG
  digitalWrite(ledpin, LOW);

  delay(10);

  int Steps = -1;
  Serial.println(F("HELLO"));
  while (completion229 == false) {

    // DEBUG
    digitalWrite(ledpin, HIGH);
    stepnumber229 = stepnumber229 + 1;
    if (Steps == 7) {
      Steps = 0;
    } else {
      Steps = Steps + 1;
    }
    if (stepnumber229 >= numberofsteps) {
      completion229 = true;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW); 
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}

void eREVERSE() {
  Serial.println(F("QWERTY - REVERSE"));
  bool completion456 = false;
  int stepnumber456 = 0;
  int Steps = 7;

  

  while (completion456 == false) {
    stepnumber456 = stepnumber456 + 1;
    if (stepnumber456 >= numberofsteps) {
      completion456 = true;
    }
    if (Steps == 0) {
      Steps = 7;
    } else {
      Steps = Steps - 1;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}

void eLEFT() {
  Serial.println(F("QWERTY - LEFT"));
  bool completion334 = false;
  int stepnumber334 = 0;
  int excelsheets = execsperloop[3];
  int Steps = 0;
  while (completion334 == false) {
    stepnumber334 = stepnumber334 + 1;
    if (stepnumber334 >= numberofturns23 * 1.01) {
      completion334 = true;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    if (Steps == 7) {
      Steps = 0;
    } else {
      Steps = Steps + 1;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}

void eRIGHT() {
  Serial.println(F("QWERTY - RIGHT"));
  bool completion334 = false;
  int stepnumber334 = 0;
  int excelsheets = execsperloop[3];
  int Steps = 0;
  while (completion334 == false) {
    stepnumber334 = stepnumber334 + 1;
    if (stepnumber334 >= numberofturns23) {
      completion334 = true;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    if (Steps == 7) {
      Steps = 0;
    } else {
      Steps = Steps + 1;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}

void eFINALONE() {
  Serial.println(F("QWERTY - REVERSE"));
  bool completion456 = false;
  int stepnumber456 = 0;
  int Steps = 7;

  

  while (completion456 == false) {
    stepnumber456 = stepnumber456 + 1;
    if (stepnumber456 >= (numberofsteps / 20)) {
      completion456 = true;
    }
    if (Steps == 0) {
      Steps = 7;
    } else {
      Steps = Steps - 1;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(800);
  }
}

void eFINALTWO() {
  digitalWrite(PVLED1, HIGH);
  Serial.println(F("QWERTY - FINAL VERSION TWO"));
  bool completion819 = false;
  int stepmnumber819 = 0;
  int underground = execsperloop[6];
  int Steps = 0;
  while (completion819 == false) {
    pvhit();

  }
}

void eENTERING() {
  Serial.println(F("QWERTY - REVERSE"));
  bool completion456 = false;
  int stepnumber456 = 0;
  int Steps = 7;

  

  while (completion456 == false) {
    stepnumber456 = stepnumber456 + 1;
    if (stepnumber456 >= numberofstepsenter) {
      completion456 = true;
    }
    if (Steps == 0) {
      Steps = 7;
    } else {
      Steps = Steps - 1;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(800);
  }
}

void setupstringloop() {
  // TAKE READINGS OF INITIAL VARIABLES
  lbinitial = digitalRead(LEFTBUTTON);
  rigbinitial = digitalRead(RIGHTBUTTON);
  sbinitial = digitalRead(STRAIGHTBUTTON);
  revbinitial = digitalRead(REVERSEBUTTON);
  f1initial = digitalRead(FINAL1BUTTON);
  f2initial = digitalRead(FINAL2BUTTON);
  tspinitial = digitalRead(TENSECONDPLUS);
  tsminitial = digitalRead(TENSECONDMINUS);
  ospinitial = digitalRead(ONESECONDPLUS);
  osminitial = digitalRead(ONESECONDMINUS);
  resinitial = digitalRead(RESETBUTTON);
  mpinitial = digitalRead(MODIFIERPLUS);
  mminitial = digitalRead(MODIFIERMINUS);
  tpinitial = digitalRead(TURNPLUS);
  tminitial = digitalRead(TURNMINUS);
  digitalWrite(ledpin,LOW);


  bool FINISHED = false;


  bool lbfinal;
  bool rigbfinal;
  bool sbfinal;
  bool revbfinal;
  bool f1final;
  bool f2final;
  bool tspfinal;
  bool tsmfinal;
  bool ospfinal;
  bool osmfinal;
  bool resfinal;
  bool mpfinal;
  bool mmfinal;
  bool tpfinal;
  bool tmfinal;


  int timer9000 = 0;
  int startanalogsignal = 0;


  delay(2000);


  digitalWrite(PVLEDHIT1, LOW);
  digitalWrite(PVLEDHIT2, LOW);
  digitalWrite(PVLEDHIT3, LOW);
  digitalWrite(PVLEDHIT4, LOW);
  combinationstring = "E";

  // WHILE LOOP UNTIL FINAL IS RECEIVED OR ANALOG IS RECEIVED;
  while (FINISHED == false) {
    lbfinal = digitalRead(LEFTBUTTON);
    rigbfinal = digitalRead(RIGHTBUTTON);
    sbfinal = digitalRead(STRAIGHTBUTTON);
    revbfinal = digitalRead(REVERSEBUTTON);
    f1final = digitalRead(FINAL1BUTTON);
    f2final = digitalRead(FINAL2BUTTON);
    tspfinal = digitalRead(TENSECONDPLUS);
    tsmfinal = digitalRead(TENSECONDMINUS);
    ospfinal = digitalRead(ONESECONDPLUS);
    osmfinal = digitalRead(ONESECONDMINUS);
    resfinal = digitalRead(RESETBUTTON);
    mpfinal = digitalRead(MODIFIERPLUS);
    mmfinal = digitalRead(MODIFIERMINUS);
    tpfinal = digitalRead(MODIFIERPLUS);
    tmfinal = digitalRead(MODIFIERMINUS);

    startanalogsignal = analogRead(STARTANALOG);
    delay(1);
    startanalogsignal = startanalogsignal + analogRead(STARTANALOG);
    delay(1);
    startanalogsignal = startanalogsignal + analogRead(STARTANALOG);
    delay(1);
    startanalogsignal = startanalogsignal + analogRead(STARTANALOG);
    delay(1);
    startanalogsignal = startanalogsignal + analogRead(STARTANALOG);
    delay(1);

    startanalogsignal = startanalogsignal / 5;


    // LEFT BUTTON
    if (lbfinal != lbinitial && lbpressed != true) {
      Serial.println(F("LEFT BUTTON PRESSED"));
      lbpressed = true;
      combinationstring = combinationstring + "L";
      digitalWrite(LEFTLED, HIGH);
    } else {
      if (lbfinal == lbinitial && lbpressed == true) {
        Serial.println(F("RESET"));
        lbpressed = false;
        delay(10);
        digitalWrite(LEFTLED, LOW);
      }
    }

    // RIGHT BUTTON
    if (rigbfinal != rigbinitial && rigbpressed != true) {
      Serial.println(F("RIGHT BUTTON PRESSED"));
      rigbpressed = true;
      combinationstring = combinationstring + "R";
      digitalWrite(RIGHTLED, HIGH);
    } else {
      if (rigbfinal == rigbinitial && rigbpressed == true) {
        rigbpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(RIGHTLED, LOW);
      }
    }

    // STRAIGHT BUTTON
    if (sbfinal != sbinitial && sbpressed != true) {
      Serial.println(F("STRAIGHT BUTTON PRESSED"));
      sbpressed = true;
      combinationstring = combinationstring + "S";
      digitalWrite(STRAIGHTLED, HIGH);
    } else {
      if (sbfinal == sbinitial && sbpressed == true) {
        sbpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(STRAIGHTLED, LOW);
      }
    }

    // REVERSE BUTTON
    if (revbfinal != revbinitial && revbpressed != true) {
      Serial.println(F("REVERSE BUTTON PRESSED"));
      revbpressed = true;
      combinationstring = combinationstring + "Q";
      digitalWrite(REVERSELED, HIGH);
    } else {
      if (revbfinal == revbinitial && revbpressed == true) {
        revbpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(REVERSELED, LOW);
      }
    }

    // FINAL 1 BUTTON PRESSED
    if (f1final != f1initial && f1pressed != true) {
      Serial.println(F("FINAL ONE BUTTON PRESSED"));
      f1pressed = true;
      combinationstring = combinationstring + "F1";
      digitalWrite(PVLEDHIT1, HIGH);
      digitalWrite(PVLEDHIT2, HIGH);
      digitalWrite(PVLEDHIT3, HIGH);
      digitalWrite(PVLEDHIT4, HIGH);
    } else {
      if (f1final == f1initial && f1pressed == true) {
        f1pressed = false;
        Serial.println(F("RESET"));
        digitalWrite(PVLEDHIT1, HIGH);
        digitalWrite(PVLEDHIT2, HIGH);
        digitalWrite(PVLEDHIT3, HIGH);
        digitalWrite(PVLEDHIT4, HIGH);
        FINISHED = true;
        delay(10);
      }
    }

    // FINAL 2 BUTTON PRESSED
    if (f2final != f2initial && f2pressed != true) {
      Serial.println(F("FINAL TWO BUTTON PRESSED"));
      f2pressed = true;
      combinationstring = combinationstring + "F2";
    } else {
      if (f2final == f2initial && f2pressed == true) {
        f2pressed = false;
        Serial.println(F("RESET"));
        delay(10);
      }
    }

    // TEN SECOND PLUS BUTTON PRESSED
    if (tspfinal != tspinitial && tsppressed != true) {
      Serial.println(F("TEN SECOND PLUS BUTTON PRESSED"));
      tsppressed = true;
      timesecondstoachieve = timesecondstoachieve + 10;
      digitalWrite(PVLEDHIT1, HIGH);
    } else {
      if (tspfinal == tspinitial && tsppressed == true) {
        tsppressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(PVLEDHIT1, LOW);
      }
    }

    // TEN SECOND MINUS BUTON PRESSED
    if (tsmfinal != tsminitial && tsmpressed != true) {
      Serial.println(F("TEN SECOND MINUS BUTTON PRESSED"));
      tsmpressed = true;
      timesecondstoachieve = timesecondstoachieve - 10;
      digitalWrite(PVLEDHIT3, HIGH);
    } else {
      if (tsmfinal == tsminitial && tsmpressed == true) {
        tsmpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(PVLEDHIT3, LOW);
      }
    }

    // ONE SECOND PLUS BUTTON PRESSED
    if (ospfinal != ospinitial && osppressed != true) {
      Serial.println(F("ONE SECOND PLUS BUTTON PRESSED"));
      osppressed = true;
      timesecondstoachieve = timesecondstoachieve + 1;
      digitalWrite(PVLEDHIT4, HIGH);
    } else {
      if (ospfinal == ospinitial && osppressed == true) {
        osppressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(PVLEDHIT4, LOW);
      }
    }

    // ONE SECOND MINUS BUTTON PRESSED
    if (osmfinal != osminitial && osmpressed != true) {
      Serial.println(F("ONE SECOND MINUS BUTTON PRESSED"));
      osmpressed = true;
      timesecondstoachieve = timesecondstoachieve - 1;
      digitalWrite(PVLEDHIT2, HIGH);
    } else {
      if (osmfinal == osminitial && osmpressed == true) {
        osmpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(PVLEDHIT2, LOW);
      }
    }

    // RESET BUTTON PRESSED
    if (resfinal != resinitial && respressed != true) {
      Serial.println(F("RESET BUTTON PRESSED"));
      respressed = true;
    } else {
      if (resfinal == resinitial && respressed == true) {
        respressed = false;
        Serial.println(F("RESET"));
        delay(10);
      }
    }

    // MODIFIER MINUS BUTTON PRESSED
    if (mmfinal != mminitial && mmpressed != true) {
      Serial.println(F("MODIFIER MINUS BUTTON PRESSED"));
      mmpressed = true;
      steplength = steplength - 1;
      digitalWrite(STRAIGHTLED, HIGH);
    } else {
      if (mmfinal == mminitial && mmpressed == true) {
        mmpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(STRAIGHTLED, LOW);
      }
    }

    // MODIFIER PLUS BUTTON PRESSED
    if (mpfinal != mpinitial && mppressed != true) {
      Serial.println(F("MODIFIER PLUS BUTTON PRESSED"));
      mppressed = true;
      steplength = steplength + 1;
      digitalWrite(REVERSELED, HIGH);
    } else {
      if (mpfinal == mpinitial && mppressed == true) {
        mppressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(REVERSELED, LOW);
      }
    }

    // TURNPLUS BUTTON PRESSED
    if (tpfinal != tpinitial && tppressed != true) {
      Serial.println(F("TURN PLUS BUTTON PRESSED!"));
      tppressed = true;
      numberofturns23 = numberofturns23 + 100;
      digitalWrite(STRAIGHTLED, HIGH);
    } else {
     if (tpfinal == tpinitial && tppressed == true) {
        tppressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(STRAIGHTLED, LOW);
      }
    }

    // TURNMINUS BUTTON PRESSED
    if (tmfinal != tminitial && tmpressed != true) {
      Serial.println(F("TURN MINUS BUTTON PRESSED!"));
      tmpressed = true;
      numberofturns23 = numberofturns23 - 100;
      digitalWrite(REVERSELED, HIGH);
    } else {
      if (tmfinal == tminitial && tmpressed == true) {
        tmpressed = false;
        Serial.println(F("RESET"));
        delay(10);
        digitalWrite(REVERSELED, LOW);
      }
    }

    // TIMER VARIABLES TO REPORT CURRENT STRING
    timer9000 = timer9000 + 1;
    if (timer9000 >= 150) {
      Serial.print(F("STRING: "));
      Serial.print(combinationstring);
      Serial.print(F(" TIMER9000: "));
      Serial.print(timer9000);
      Serial.print(F(" STEP_LENGTH: "));
      Serial.print(steplength);
      Serial.print(F(" ANALOG START "));
      Serial.print(startanalogsignal);
      Serial.print(F(" TIME TO ACHIEVE: "));
      Serial.println(timesecondstoachieve);
      timer9000 = 0;
    }
  }
  Serial.println(F("FINISHED!"));
  if (overrideonce == false) {
    overrideonce = true;
    setupstringloop();
  } else {
    FINISHED = false;
    overrideonce = false;
    delay(200);
    digitalWrite(PVLEDHIT1, LOW);
    digitalWrite(PVLEDHIT2, LOW);
    digitalWrite(PVLEDHIT3, LOW);
    digitalWrite(PVLEDHIT4, LOW);
    delay(200);
    targettimeanalysis();
    delay(100);
  }
}

void eFIRSTRAIGHT() {
  Serial.println(F("QWERTY - STRAIGHT"));
  bool completion229 = false;
  int stepnumber229 = 0;
  
  // DEBUG
  digitalWrite(ledpin, LOW);

  int Steps = -1;
  Serial.println(F("HELLO"));
  while (completion229 == false) {

    // DEBUG
    digitalWrite(ledpin, HIGH);
    stepnumber229 = stepnumber229 + 1;
    if (Steps == 7) {
      Steps = 0;
    } else {
      Steps = Steps + 1;
    }
    if (stepnumber229 >= numberofstepsfront) {
      completion229 = true;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW); 
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}

void eFINALSTRAIGHT() {
  Serial.println(F("QWERTY - STRAIGHT"));
  bool completion229 = false;
  int stepnumber229 = 0;
  
  // DEBUG
  digitalWrite(ledpin, LOW);

  int Steps = -1;
  Serial.println(F("HELLO"));
  while (completion229 == false) {

    // DEBUG
    digitalWrite(ledpin, HIGH);
    stepnumber229 = stepnumber229 + 1;
    if (Steps == 7) {
      Steps = 0;
    } else {
      Steps = Steps + 1;
    }
    if (stepnumber229 >= numberofstepsend) {
      completion229 = true;
    }
    switch (Steps) {
      case 0:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 1:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 2:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
      case 3:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, HIGH);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, HIGH);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, HIGH);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, HIGH);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 4:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, LOW);
        break;
      case 5:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, HIGH);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, HIGH);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, HIGH);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, HIGH);
        digitalWrite(M4IN4, HIGH);
        break;
      case 6:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      case 7:
        digitalWrite(M1IN1, HIGH);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, HIGH);
        digitalWrite(M2IN1, HIGH);
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, HIGH);
        digitalWrite(M3IN1, HIGH);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, HIGH);
        digitalWrite(M4IN1, HIGH);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, HIGH);
        break;
      default:
        digitalWrite(M1IN1, LOW);
        digitalWrite(M1IN2, LOW);
        digitalWrite(M1IN3, LOW);
        digitalWrite(M1IN4, LOW);
        digitalWrite(M2IN1, LOW); 
        digitalWrite(M2IN2, LOW);
        digitalWrite(M2IN3, LOW);
        digitalWrite(M2IN4, LOW);
        digitalWrite(M3IN1, LOW);
        digitalWrite(M3IN2, LOW);
        digitalWrite(M3IN3, LOW);
        digitalWrite(M3IN4, LOW);
        digitalWrite(M4IN1, LOW);
        digitalWrite(M4IN2, LOW);
        digitalWrite(M4IN3, LOW);
        digitalWrite(M4IN4, LOW);
        break;
    }
    delayMicroseconds(delaybetweenmicrosteps);
  }
}