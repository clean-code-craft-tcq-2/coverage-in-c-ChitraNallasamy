#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"
#include <string.h>

TEST_CASE("Testcase for breaching LowerLimit") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("Testcase for breaching HigherLimit") {
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH);
}

TEST_CASE("Testcase1 for valid limit") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Testcase2 for valid limit") {
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
}

TEST_CASE("Testcase3 for valid limit") {
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
}

TEST_CASE("Testcase for retreiving the limits - TOO HIGH") {
  BatteryCharacter myBatteryChar = {PASSIVE_COOLING, "EXIDE"};
  double temperatureInC = 50;
  int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                    {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                    {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
  
  REQUIRE(classifyTemperatureBreach(RangeBasedOnCoolingType, myBatteryChar.coolingType, temperatureInC) == TOO_HIGH);
}

TEST_CASE("Testcase for retreiving the limits - NORMAL") {
  BatteryCharacter myBatteryChar = {HI_ACTIVE_COOLING, "EXIDE"};
  double temperatureInC = 30;
  int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                    {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                    {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
  
  REQUIRE(classifyTemperatureBreach(RangeBasedOnCoolingType, myBatteryChar.coolingType, temperatureInC) == NORMAL);
}

TEST_CASE("Testcase for retreiving the limits - TOO LOW") {
  BatteryCharacter myBatteryChar = {MED_ACTIVE_COOLING, "EXIDE"};
  double temperatureInC = 8;
  int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                    {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                    {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
  
  REQUIRE(classifyTemperatureBreach(RangeBasedOnCoolingType, myBatteryChar.coolingType, temperatureInC) == TOO_LOW);
}

TEST_CASE("Testcase for Alert Text Formatters in Controller Target - NORMAL") {
  char AlertMessage[] = "feed : 0";
  prepareAlertTextForController(NORMAL);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for Alert Text Formatters in Controller Target - TOO_LOW") {
  char AlertMessage[] = "feed : 1";
  prepareAlertTextForController(TOO_LOW);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for Alert Text Formatters in Controller Target - TOO_HIGH") {
  char AlertMessage[] = "feed : 2";
  prepareAlertTextForController(TOO_HIGH);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for Alert Text Formatters in Email Target - TOO_LOW") {
  char AlertMessage[] = "c.d@c.com : Hi, the temperature is too low";
  prepareAlertTextForEmail(TOO_LOW);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for Alert Text Formatters in Email Target_NORMAL") {
  char AlertMessage[] = "c.d@c.com : Hi, the temperature is Normal";
  prepareAlertTextForEmail(NORMAL);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for Alert Text Formatters in Email Target_TOO-HIGH") {
  char AlertMessage[] = "c.d@c.com : Hi, the temperature is too high";
  prepareAlertTextForEmail(TOO_HIGH);
  REQUIRE(!strcmp(MessageToBeDisplayedOnConsole,AlertMessage));
}

TEST_CASE("Testcase for validating function PerformBatteryCheck") {
  BatteryCharacter myBatteryChar = {PASSIVE_COOLING, "EXIDE"};
  int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                    {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                    {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
  
  REQUIRE(PerformBatteryCheck(myBatteryChar, -10, RangeBasedOnCoolingType) == 1);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 30, RangeBasedOnCoolingType) == 0);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 40, RangeBasedOnCoolingType) == 2);
  
  myBatteryChar.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(PerformBatteryCheck(myBatteryChar, -10, RangeBasedOnCoolingType) == 1);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 30, RangeBasedOnCoolingType) == 0);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 50, RangeBasedOnCoolingType) == 2);
  
  myBatteryChar.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(PerformBatteryCheck(myBatteryChar, -10, RangeBasedOnCoolingType) == 1);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 30, RangeBasedOnCoolingType) == 0);
  REQUIRE(PerformBatteryCheck(myBatteryChar, 41, RangeBasedOnCoolingType) == 2);
}
