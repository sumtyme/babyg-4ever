// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

/// @file	AP_MotorsHexa.h
/// @brief	Motor control class for Hexacopters

#ifndef __AP_MOTORS_HEXA_H__
#define __AP_MOTORS_HEXA_H__

#include <AP_Common.h>
#include <AP_Math.h>        // ArduPilot Mega Vector/Matrix math Library
#include <RC_Channel.h>     // RC Channel Library
#include "AP_MotorsMatrix.h"    // Parent Motors Matrix library

/// @class      AP_MotorsHexa
class AP_MotorsHexa : public AP_MotorsMatrix {
public:

    /// Constructor
    AP_MotorsHexa( uint8_t APM_version, RC_Channel* rc_roll, RC_Channel* rc_pitch, RC_Channel* rc_throttle, RC_Channel* rc_yaw, uint16_t speed_hz = AP_MOTORS_SPEED_DEFAULT) : AP_MotorsMatrix(APM_version, rc_roll, rc_pitch, rc_throttle, rc_yaw, speed_hz) {
    };

    // setup_motors - configures the motors for a quad
    virtual void        setup_motors();

protected:

};

#endif  // AP_MOTORSHEXA
