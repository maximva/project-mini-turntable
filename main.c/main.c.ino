const int ENABLE = 11;
const int DIRA = 8;
const int DIRB = 9;
const int rotaryEncoderClk = 3;
const int rotaryEncoderData = 2;
const int buttonPin = 4;

int motorSpeed = 200;
boolean buttonPressed = false;
volatile int interruptCount = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("[TurnTable] Initializing firmware ...");

  // SET PIN DIRECTION
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(rotaryEncoderClk, INPUT);
  pinMode(rotaryEncoderData, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), clkISR, FALLING);

  Serial.println("[TurnTable] Firmware initialized.");
}

void clkISR() {
  if (interruptCount == 0) {
    interruptCount++;
    if (digitalRead(rotaryEncoderClk) != digitalRead(rotaryEncoderData)) {
      // CLK (A) WAS FIRST (CW ROTATION)
      speedUpMotor(&motorSpeed);
    } else {
      // DTA (B) WAS FIRST (CCW ROTATION)
      slowDownMotor(&motorSpeed);
    }
  } else {
    interruptCount--;
  }
  
  // THIS WORKS BEST TO DEBOUNCE THE ROTARY ENCODER
  delay(50);
  while(digitalRead(rotaryEncoderClk) == 0);
  delay(50);
}

void loop() {
  listenForButtonPress(&buttonPressed);

  if (buttonPressed) {
    startMotor(&motorSpeed);
  } else {
    stopMotor();
  }
}

void listenForButtonPress(boolean * buttonPressed) {
  if (!digitalRead(buttonPin)) {
    Serial.println("[TurnTable] Button pressed.");
    (*buttonPressed) = !(*buttonPressed);
    while(!digitalRead(buttonPin)); // wait for button to be released to continue
  }
}

void startMotor(int *motorSpeed) {
  analogWrite(ENABLE,(*motorSpeed));
  digitalWrite(DIRA,HIGH);
  digitalWrite(DIRB,LOW);
  delay(10); 
}

void stopMotor() {
  analogWrite(ENABLE, 0);
}

void slowDownMotor(int *currentSpeed) {
  (*currentSpeed) -= 10;
  (*currentSpeed) = ((*currentSpeed) < 10 ? 10 : (*currentSpeed));
  Serial.print("[TurnTable] Slowing down: current speed is ");
  Serial.println((*currentSpeed));
}

void speedUpMotor(int *currentSpeed) {
  (*currentSpeed) += 10;
  (*currentSpeed) = ((*currentSpeed) > 250 ? 250 : (*currentSpeed));
  Serial.print("[TurnTable] Speeding up: current speed is ");
  Serial.println((*currentSpeed));
}
