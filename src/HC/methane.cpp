#include "methane.hpp"


// util functions
bool withinRange(float target, float current, float error) {
  return abs(target - current) < error;
}

bool withinErr(float cX, float cY, float tX, float tY, float eP = P_ERR) {
  return (
    withinRange(tX, cX, eP) &&
    withinRange(tY, cY, eP)
  );
}

float dist(float x1, float y1, float x2, float y2) {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

float dot(float x1, float y1, float x2, float y2) {
  return (x1 * x2) + (y1 * y2);
}

float remap (float value, float from1, float to1, float from2, float to2) {
  return (value - from1) / (to1 - from1) * (to2 - from2) + from2;
}


float angleDiff(float angle1, float angle2) {
  float diff = fmod(angle2 - angle1 + PI, TAU) - (PI / 2);
  return diff < -PI ? diff + TAU : diff;
}
// end util functions


namespace hc {
  void methane::Robot::seek(float x, float y, propene::PID *transPID, propene::PID *rotPID) {
    float dotter = SGN(dot(x, y, posTracker.x, posTracker.y));
    float trans = transPID->calculate(-dist(x, y, posTracker.x, posTracker.y), 0) * (dotter != 0 ? dotter : 1);
    float rot = rotPID->calculate(TODEG(posTracker.a - atan2(x - posTracker.x, y - posTracker.y)), 0);

    float idealVR = (trans + rot);
    float idealVL = (trans - rot);

    float maxMag = fmax(abs(idealVL), abs(idealVR));
    float minMag = fmin(abs(idealVL), abs(idealVR));

    if (maxMag > 1)  {
      idealVR /= maxMag;
      idealVL /= maxMag;
    }

    RIGHT_DRIVE_SET(idealVR * 127);
    LEFT_DRIVE_SET(idealVL * 127);
  }

  void methane::Robot::moveTo(::hc::benzene::Point target, float targetA) {
    ::hc::propene::PID *transPID = new ::hc::propene::PID(0.048, 0, 0.0, 0.0001, 0.00001, 1, -1);
    ::hc::propene::PID *rotPID = new ::hc::propene::PID(0.013, 0, 0.002, 0.0001, 0.00001, 1, -1);

    while(!withinErr(posTracker.x, posTracker.y, target.x, target.y)) {
      // std::cout << "posTracker.x: " << posTracker.x << std::endl;
      // std::cout << "posTracker.y: " << posTracker.y << std::endl;

      seek(target.x, target.y, transPID, rotPID);
    }


    if(!withinRange(TODEG(posTracker.a), targetA, A_ERR))
      turnToFace(targetA);

    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::moveAlong(::hc::benzene::Point wayPoints[], int size, float endA) {

  }

  void methane::Robot::moveFor(float dist) {
    float initialEL = lTrackerWheel.get_value();
    float initialER = rTrackerWheel.get_value();

    pid->doPID(dist, 50 , [=]() -> float {
      return (initialEL - lTrackerWheel.get_value() + initialER - rTrackerWheel.get_value()) / 2;
    }, [](float output) -> void {
      RIGHT_DRIVE_SET(output);
      LEFT_DRIVE_SET(output);
    });
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(float deg) {
    if(withinRange(posTracker.a, deg, A_ERR)) return;
    
    pid->doPID(deg, 3, []() -> float {
      return TODEG(posTracker.a);
    }, [](float output) -> void {
      RIGHT_DRIVE_SET(output);
      LEFT_DRIVE_SET(-output);
    });
    RIGHT_DRIVE_SET(0);
    LEFT_DRIVE_SET(0);
  }

  void methane::Robot::turnToFace(::hc::benzene::Point point) {
    turnToFace(TODEG(atan2(point.x - posTracker.x, point.y - posTracker.y) - posTracker.a));
  }

  void methane::Robot::feedBall() {
    INTAKE_SET(127);
  }

  void methane::Robot::reset() {
    tracker->reset();
  }
}

hc::methane::Robot robot = hc::methane::Robot(&posTracker, &mainPID);
