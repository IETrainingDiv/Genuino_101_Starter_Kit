#define LED_MODULE 9
#define IR_SENSOR A0

int lowBrightness = 1023, highBrightness = 0;

void fadeLED(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    for (int j = 0; j < 255; j += 5) {
      analogWrite(LED_MODULE, j);
      delay(delayTime);
    }
    for (int j = 255; j > 0; j -= 5) {
      analogWrite(LED_MODULE, j);
      delay(delayTime);
    }
  }
}

void calibrate(int times) {
  for (int i = 0; i < times; i++) {
    int brightness = analogRead(A0);
    if (brightness <= lowBrightness) {
      lowBrightness = brightness;
    }
    if (brightness >= highBrightness) {
      highBrightness = brightness;
    }
    delay(10);
  }
}


void setup() {
  pinMode(LED_MODULE, OUTPUT);
  //calibration will take about 300*10 ms once
  //cover IR SENSOR with the desired object to determine the highest brightness
  //uncover IR SENSOR to determine the lowest brightness
  calibrate(300);
}

void loop() {
  int distance;
  distance = map(analogRead(A0), lowBrightness, highBrightness, 30, 1);
  if (distance > 30) {
    distance = 30;
  }
  if (distance < 1) {
    distance = 1;
  }
  fadeLED(1, distance);
}
