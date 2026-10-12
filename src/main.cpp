#include <Arduino.h>

float Kp = 1.5, Ki = 0.05, Kd = 0.5;
float target_pos = 0;
float current_pos = 0;
float last_time = 0;

float integral = 0;
float previous_error = 0;
float timeDelay = 10;

float integral_max = 50.0;
float integral_min = -50.0;

  float output_max = 20.0;
float output_min = -20.0;

bool first_run = true;

float computePID(float target, float current);

void setup() {
  last_time = millis();
  Serial.begin(9600);
  Serial.println("Starting PID Controller...");
  delay(100);
}

void loop() {
  target_pos = 100; 

  float output_vel = computePID(target_pos, current_pos);

  float dt_seconds = timeDelay / 1000.0;
  current_pos += output_vel * dt_seconds;

  Serial.print("velocity: ");
  Serial.print(output_vel);
  Serial.print(", position: ");
  Serial.print(current_pos);
  Serial.print(", error: ");
  Serial.println(target_pos - current_pos);

  delay(timeDelay);
}

float computePID(float target, float current) {
  float current_time = millis();
  float dt = (current_time - last_time);

  float dt_seconds = dt / 1000.0;

  if (dt_seconds <= 0.001) {
    dt_seconds = 0.001;
  }

  float error = target - current;

  float P = Kp * error;

  integral += error * dt_seconds;

  if (integral > integral_max)
    integral = integral_max;
  if (integral < integral_min)
    integral = integral_min;
  float I = Ki * integral;

  float D = 0;
  if (!first_run) {
    float derivative = (error - previous_error) / dt_seconds;
    D = Kd * derivative;
  } else {
    first_run = false;
  }

  previous_error = error;
  last_time = current_time;

  float output = P + I + D;

  if (output > output_max)
    output = output_max;
  if (output < output_min)
    output = output_min;

  return output;
}
