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

TEST_CASE("Testcase for valid limit") {
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Testcase for retreiving the limits") {
  BatteryCharacter myBatteryChar = {PASSIVE_COOLING, "EXIDE"};
  double temperatureInC = 50;
  int RangeBasedOnCoolingType[COOLING_TYPES][TEMPERATURE_LIMITS] = {{PASSIVE_COOLING_LOWER_LIMIT, PASSIVE_COOLING_UPPER_LIMIT}, 
                                                                    {HI_ACTIVE_COOLING_LOWER_LIMIT, HI_ACTIVE_COOLING_UPPER_LIMIT}, 
                                                                    {MED_ACTIVE_COOLING_LOWER_LIMIT, MED_ACTIVE_COOLING_UPPER_LIMIT}};
  
  REQUIRE(classifyTemperatureBreach(RangeBasedOnCoolingType, myBatteryChar.coolingType, temperatureInC) == TOO_HIGH);
}

TEST_CASE("Testcase for AlertTextFormatters in Email Target") {
  char TestAlertMessage[44] = "";
  char ExpectedAlertMessage[] = "a.b@c.com : Hi, the temperature is too low";
  prepareAlertTextForEmail(TOO_LOW, TestAlertMessage);
  REQUIRE(!strcmp(TestAlertMessage,ExpectedAlertMessage));
}
