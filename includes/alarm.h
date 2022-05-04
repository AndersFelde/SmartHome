/*
 * alarm.h
 *
 * Created: 26.04.2022 14:31:59
 *  Author: Anders K Felde
 */

#ifndef ALARM_H_
#define ALARM_H_
int Alarm;
int CountDown;
int coolDown;
void initAlarm();
void startTimer();
void triggerWarning();
void triggerAlarm();
void stopAlarm();
void startCooldown();
void stopCooldown();

#endif /* ALARM_H_ */
