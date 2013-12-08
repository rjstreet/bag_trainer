const int xPin = 2;
const int yPin = 3;
const int rlPin = 13;
const int rmPin = 12;
const int rtPin = 11;
const int mlPin = 10;
const int mmPin = 9;
const int mtPin = 8;
const int llPin = 7;
const int lmPin = 6;
const int ltPin = 5;

int xOffset = 0;
int yOffset = 0;
boolean beenHit = true;
int currentPin;
int startTime, endTime;

void setup() {
  Serial.begin( 9600 );
  pinMode( xPin, INPUT );
  pinMode( yPin, INPUT ); 
  pinMode( rlPin, OUTPUT );
  pinMode( rmPin, OUTPUT );
  pinMode( rtPin, OUTPUT );
  randomSeed(analogRead(0));
  calibrate();
}

void calibrate() {
  xOffset = getXAcceleration();
  yOffset = getYAcceleration();
}

int getXAcceleration() {
  return ((( pulseIn( xPin, HIGH ) / 10 ) - 500 ) * 8) - xOffset;
}

int getYAcceleration() {
  return ((( pulseIn( yPin, HIGH ) / 10 ) - 500 ) * 8) - yOffset;
}

void loop() {
  int accelerationX, accelerationY;
  
  if( beenHit ) {
    Serial.print( currentPin );
    Serial.print( "\t" );
    Serial.print( endTime-startTime );
    Serial.println();
    currentPin = random( 3 ) + 11;
    digitalWrite( currentPin, HIGH );
    startTime = millis();
    beenHit = false;
  }  
  accelerationX = getXAcceleration();
  accelerationY = getYAcceleration();
  
  if( accelerationX > 100 || accelerationX < -100 ) {
    digitalWrite( currentPin, LOW );
    endTime = millis();
    delay( 1000 );
    beenHit = true;
  }
}

