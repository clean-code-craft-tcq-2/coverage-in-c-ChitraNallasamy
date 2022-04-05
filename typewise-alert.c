#include "typewise-alert.h"
#include <stdio.h>
#include <string.h>

char MessageToBeDisplayedOnConsole[44] = "";
void (*pointerToAlertingOptions[]) (BreachType) = {prepareAlertTextForController,prepareAlertTextForEmail};
int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                  {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                  {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(int MapForCoolingTypeVsRange[][TEMPERATURE_LIMITS], CoolingType coolingType, double temperatureInC) {
  int lowerLimit = MapForCoolingTypeVsRange[coolingType][LOWER_LIMIT_IN_MAP];
  int upperLimit = MapForCoolingTypeVsRange[coolingType][UPPER_LIMIT_IN_MAP];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void prepareAlertTextForController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  snprintf(MessageToBeDisplayedOnConsole,10,"%x : %x", header, breachType);
}

void prepareAlertTextForEmail(BreachType breachType) {
   char recepient[] = "c.d@c.com";
   char AlertMessagesForEmail[][32] = {"Hi, the temperature is Normal",
                                       "Hi, the temperature is too low", 
                                       "Hi, the temperature is too high"};

   snprintf(MessageToBeDisplayedOnConsole,44,"%s : %s",recepient,&(AlertMessagesForEmail[breachType][0]));
}

void printOnConsole(char *stringToBePrinted) {
    printf("%s",stringToBePrinted);
}

BreachType PerformBatteryCheck(BatteryCharacter batteryChar, double temperatureInC, int RangeBasedOnCoolingType[][TEMPERATURE_LIMITS]) {
    return classifyTemperatureBreach(RangeBasedOnCoolingType, batteryChar.coolingType, temperatureInC);
}

void alertAndPrint(AlertTarget currentAlertTarget, BreachType breachType) {
  /* Provide Alert on the requested Target*/
  pointerToAlertingOptions[currentAlertTarget](breachType); // Function Pointers of different targets
  (void) printOnConsole(MessageToBeDisplayedOnConsole);
}

void Start_BatteryCheckSystem (AlertTarget currentAlertTarget, BatteryCharacter batteryChar, double temperatureInC) {     
    (void) alertAndPrint(currentAlertTarget,PerformBatteryCheck(batteryChar, temperatureInC, RangeBasedOnCoolingType));
}
