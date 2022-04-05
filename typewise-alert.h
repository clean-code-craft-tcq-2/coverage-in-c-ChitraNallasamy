#pragma once

#define COOLING_TYPES 3
#define TEMPERATURE_LIMITS 2
#define LOWER_LIMIT_IN_MAP 0
#define UPPER_LIMIT_IN_MAP 1
#define PASSIVE_COOLING_LOWER_LIMIT 0
#define PASSIVE_COOLING_UPPER_LIMIT 35
#define HI_ACTIVE_COOLING_LOWER_LIMIT 0
#define HI_ACTIVE_COOLING_UPPER_LIMIT 45
#define MED_ACTIVE_COOLING_LOWER_LIMIT 0
#define MED_ACTIVE_COOLING_UPPER_LIMIT 40

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(int MapForCoolingTypeVsRange[][TEMPERATURE_LIMITS], CoolingType coolingType, double temperatureInC);
void prepareAlertTextForController(BreachType breachType);
void prepareAlertTextForEmail(BreachType breachType);
void printOnConsole(char *stringToBePrinted);
BreachType PerformBatteryCheck(BatteryCharacter batteryChar, double temperatureInC, int RangeBasedOnCoolingType[][TEMPERATURE_LIMITS]);
void Initialize_and_Start_BatteryCheckSystem (AlertTarget currentAlertTarget, BatteryCharacter batteryChar, double temperatureInC);
