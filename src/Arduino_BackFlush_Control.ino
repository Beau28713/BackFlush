#include "Adafruit_LiquidCrystal.h"
#include <Arduino.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);

int valve_control_relay = 8;
int pump_control_relay = 12;
int flow_sensor = 5;

int tilt_switch_position = 0;
int man_backflush_switch_position = 0;
int manual_auto_switch_position = 0;

int man_backflush_switch = 2;
int manual_auto_control_switch = 13;
int tilt_switch = 4;

unsigned long previous_time = 0;
unsigned long prev_time = 0;
unsigned long flow_prev_time = 0;
unsigned long weekly_timer;
unsigned long count_timer;

unsigned long time_interval = 1000;
unsigned long check_flow_interval = 10000;
unsigned long weekly_interval = 604800000;

int back_flushes_completed = 0;

unsigned long lastflowpinstate;
unsigned long lastpulsesstate = 0;
unsigned long pulses = 0;
unsigned long flow;
float flowrate;
unsigned long lastflowratetimer = 0;

SIGNAL(TIMER0_COMPA_vect)
{
  flow = digitalRead(flow_sensor);
  
  if (flow == lastflowpinstate) 
  {
    lastflowratetimer++;
    return;
  }

  if(flow == HIGH)
  {
    pulses++;
  }
  lastflowpinstate = flow;
  flowrate = 1000.0;
  flowrate /= lastflowratetimer;
  lastflowratetimer = 0;
  
  
}

void useInterrupt(boolean v)
{
  if (v)
  {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  }
  else
  {
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

void setup()
{
  pinMode(tilt_switch, INPUT_PULLUP);
  pinMode(man_backflush_switch, INPUT_PULLUP);
  pinMode(manual_auto_control_switch, INPUT_PULLUP);
  pinMode(valve_control_relay, OUTPUT);
  pinMode(pump_control_relay, OUTPUT);
  pinMode(flow_sensor, INPUT);
  digitalWrite(flow_sensor, HIGH);
  useInterrupt(true);

  Serial.begin(9600);

  digitalWrite(valve_control_relay, HIGH);
  digitalWrite(pump_control_relay, HIGH);

  if (!lcd.begin(20, 4))
  {
    Serial.println("Could not init backpack. Check wiring.");
    while (1)
      ;
  }

  lcd.clear();
}

void loop()
{
  weekly_timer = millis();

  tilt_switch_position = digitalRead(tilt_switch);
  manual_auto_switch_position = digitalRead(manual_auto_control_switch);
  
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

  if (weekly_timer - flow_prev_time >= check_flow_interval)
  {
    flow_prev_time = weekly_timer;
    if(pulses - lastpulsesstate > 0)
    {
      lcd.setCursor(0, 3);
      lcd.print("Flow detected");
      lastpulsesstate = pulses;
    }
    else
    {
      lcd.setCursor(0, 3);
      lcd.print("No flow detected");
      flushing_sequence();
      back_flushes_completed += 1;
    }
  }
  
  lcd.setCursor(0, 2);
  lcd.print("BF completed: ");
  lcd.print(back_flushes_completed);
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

void pump_control()
{
  lcd.setCursor(0, 1);
  lcd.print("Pump on         ");
  digitalWrite(pump_control_relay, LOW);
  count_down_timer(10);

  lcd.setCursor(0, 1);
  lcd.print("Pump off        ");
  digitalWrite(pump_control_relay, HIGH);
  count_down_timer(5);
}

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