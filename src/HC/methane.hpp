#ifndef METHANE_HPP
#define METHANE_HPP

#include "main.h"
#include "benzene.hpp"
#include "pentane.hpp"
#include "propene.hpp"
#include "../robot-config.hpp"

// robot specification macros
#define ZERO_SPEED 30
#define A_ERR 4
#define P_ERR 1

bool withinRange(float target, float current, float error);

namespace hc {
  namespace methane {
    class Robot { // this class handles all of the auton functions
    private:
      ::hc::benzene::Tracker *tracker;

    public:
      Robot(::hc::benzene::Tracker *tracker,
            ::hc::propene::PID *pid) :
            tracker(tracker) {};
      void seek(float x, float y, ::hc::propene::PID *transPID, ::hc::propene::PID *rotPID);
      void reset();

      void feedBall(float exit = 10000);
      bool hasBall();

      void flyUp(int rpm, std::function <void(float)> action);

      void moveTo(::hc::benzene::Point target, float err = P_ERR, float exit = 10000); // moves to a point
      void moveTo(::hc::benzene::Point target, float err, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float exit = 10000);
      void moveTo(::hc::benzene::Point target, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float exit = 10000);

      void moveAlong(::hc::benzene::Point wayPoints[], int len, float lookAhead, ::hc::propene::PIDConfig tPID, ::hc::propene::PIDConfig rPID, float err = P_ERR, float exit = 6000);
      // moves the bot along a set of way points

      void moveToSimple(::hc::benzene::Point target);
      void moveFor(float dist, float exit = 5000);

      void combineSet(bool rev);
        // moveTo({3, 4}, 45) - move to point (3, 4) and face 45deg
      // void moveFor(float length); // moves for a distance
        // moveFor(4) - move 4 in forwards
      void turnToFace(float deg, float max = 100);
      void turnToFace(::hc::benzene::Point point, float max = 100);
        // moveAlong({{1, 4}, {2, 5}}, 0); // move through the points (1, 4) then (2, 5) and end facing 0deg
      // void raiseLiftTo(int height); // rasie lift to a certain amount
      // void shootBall(int spd); // shoots a ball
      // void flipCap(); // flips the currently held cap
    };
  }
}

extern hc::methane::Robot robot;

#endif
