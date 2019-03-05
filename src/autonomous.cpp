#include "main.h"
#include "robot-config.hpp"

void autonomous() {
  robot.reset();
  tracker->reset();
  tracker->setPos(0, 0, TORAD(90));
  pros::delay(500);
  pros::Task posTracker(odom::trackTask, tracker);

  // robot.turnToFace(90);

  robot.moveFor(20);

  while(true) {
    pros::delay(20);
  }
}
