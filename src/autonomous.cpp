#include "main.h"
#include "robot-config.hpp"

void autonomous() {
  robot.reset();
  tracker->reset();
  tracker->setPos(0, 0, TORAD(90));
  pros::Task posTracker(odom::trackTask, tracker);

  robot.moveToTest({ 2, 10 }, TORAD(30));
  while(true) {
    pros::delay(20);
  }
}
