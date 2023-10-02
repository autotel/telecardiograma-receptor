#define PIN_MOTOR A1

float beatLerp(float lerp) {
  if (lerp > 0.9) {
    return 0;
  } else if (lerp > 0.7) {
    return 0.5;
  } else if (lerp > 0.5) {
    return 0;
  } else if (lerp > 0.3) {
    return 1;
  } else {
    return 0;
  }
}

float bps = 1.1;
float beatPhase = 0;
unsigned long prev = 0;

void setup() {
  pinMode(PIN_MOTOR, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long now = millis();
  float delta = now - prev;
  beatPhase = fmod(beatPhase + bps * delta / 1000., 1.);

  float out = beatLerp(beatPhase);
  int mapped = floor(out * 255.);
  Serial.print("1,0,");
  Serial.print(beatPhase);
  Serial.print(",");
  Serial.print(out);
  Serial.println();
  analogWrite(PIN_MOTOR, mapped);
  prev = now;
}