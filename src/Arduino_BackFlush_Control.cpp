#include "Adafruit_LiquidCrystal.h"
#include <Arduino.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

int valve_control_relay = 8;
int pump_control_relay = 12;
int low_level_light_relay = 7;

int man_backflush_switch_position = 0;
int manual_auto_switch_position = 0;

int man_backflush_switch = 2;
int manual_auto_control_switch = 13;
int water_level_sensor = A0;

unsigned long previous_time = 0;
unsigned long prev_time = 0;
// unsigned long flow_prev_time = 0;
unsigned long weekly_timer;
unsigned long count_timer;

unsigned long time_interval = 1000;
// unsigned long check_flow_interval = 1800000;
unsigned long weekly_interval = 604800000;

int back_flushes_completed = 0;
float water_level_sensor_output = 0;
float sensor_voltage = 0;

void count_down_timer(int timer)
{
  int time_count = 0;
  while (time_count < timer)
  {
    count_timer = millis();

    if (count_timer - previous_time >= time_interval)
    {
      previous_time = count_timer;
      time_count += 1;
    }
  }
}
void pump_control()
{
  lcd.setCursor(0, 1);
  lcd.print("Pump on         ");
  digitalWrite(pump_control_relay, LOW);
  count_down_timer(60);

  lcd.setCursor(0, 1);
  lcd.print("Pump off        ");
  digitalWrite(pump_control_relay, HIGH);
  count_down_timer(10);
}

void flushing_sequence()
{
  lcd.setCursor(0, 1);
  lcd.print("BF valve opening  ");
  digitalWrite(valve_control_relay, LOW);
  count_down_timer(15);

  pump_control();

  lcd.setCursor(0, 1);
  lcd.print("BF valve closing  ");
  digitalWrite(valve_control_relay, HIGH);
  count_down_timer(15);
  lcd.clear();
}

void setup()
{
  pinMode(man_backflush_switch, INPUT_PULLUP);
  pinMode(manual_auto_control_switch, INPUT_PULLUP);
  pinMode(valve_control_relay, OUTPUT);
  pinMode(pump_control_relay, OUTPUT);
  pinMode(low_level_light_relay, OUTPUT);

  Serial.begin(9600);

  digitalWrite(valve_control_relay, HIGH);
  digitalWrite(pump_control_relay, HIGH);

  if (!lcd.begin(20, 4))
  {
    Serial.println("Could not init backpack. Check wiring.");
    while (1)
      ;
  }
  Serial.println("Backflush control system is ready");
  lcd.clear();
}

void loop()
{
  weekly_timer = millis();

  water_level_sensor_output = analogRead(water_level_sensor);
  float sensor_voltage = water_level_sensor_output * (5.0 / 1023.0);
  manual_auto_switch_position = digitalRead(manual_auto_control_switch);

  if (sensor_voltage < 1.5)
  {
    digitalWrite(low_level_light_relay, LOW);
  }
  else
  {
    digitalWrite(low_level_light_relay, HIGH);
  }

  if (manual_auto_switch_position == LOW)
  {
    man_backflush_switch_position = digitalRead(man_backflush_switch);
    lcd.setCursor(0, 0);
    lcd.print("Manual Mode");

    if (man_backflush_switch_position == LOW)
    {
      flushing_sequence();
      back_flushes_completed += 1;
    }
  }

  else if (manual_auto_switch_position == HIGH)
  {
    lcd.setCursor(0, 0);
    lcd.print("Auto Mode  ");
    if (weekly_timer - prev_time >= weekly_interval)
    {
      prev_time = weekly_timer;
      flushing_sequence();
      back_flushes_completed += 1;
    }
  }

  lcd.setCursor(0, 2);
  lcd.print("BF completed: ");
  lcd.print(back_flushes_completed);
}