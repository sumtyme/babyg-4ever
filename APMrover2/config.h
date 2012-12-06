// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//  DO NOT EDIT this file to adjust your configuration.  Create your own
//  APM_Config.h and use APM_Config.h.example as a reference.
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
///
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// Default and automatic configuration details.
//
// Notes for maintainers:
//
// - Try to keep this file organised in the same order as APM_Config.h.example
//

#include "defines.h"

///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///
#include "APM_Config.h"  // <== THIS INCLUDE, DO NOT EDIT IT. EVER.
///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///

// Just so that it's completely clear...
#define ENABLED			1
#define DISABLED		0

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HARDWARE CONFIGURATION AND CONNECTIONS
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// APM HARDWARE
//

#ifndef CONFIG_APM_HARDWARE
# define CONFIG_APM_HARDWARE APM_HARDWARE_APM1
#endif

//////////////////////////////////////////////////////////////////////////////
// APM2 HARDWARE DEFAULTS
//

#if CONFIG_APM_HARDWARE == APM_HARDWARE_APM2
# define CONFIG_INS_TYPE   CONFIG_INS_MPU6000
# define CONFIG_PUSHBUTTON DISABLED
# define CONFIG_RELAY      DISABLED
# define MAG_ORIENTATION   AP_COMPASS_APM2_SHIELD
# define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
# define MAGNETOMETER ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// LED and IO Pins
//
#if CONFIG_APM_HARDWARE == APM_HARDWARE_APM1
# define A_LED_PIN        37
# define B_LED_PIN        36
# define C_LED_PIN        35
# define LED_ON           HIGH
# define LED_OFF          LOW
# define SLIDE_SWITCH_PIN 40
# define PUSHBUTTON_PIN   41
# define USB_MUX_PIN      -1
# define CONFIG_RELAY     ENABLED
# define BATTERY_PIN_1	  0
# define CURRENT_PIN_1	  1
#elif CONFIG_APM_HARDWARE == APM_HARDWARE_APM2
# define A_LED_PIN        27
# define B_LED_PIN        26
# define C_LED_PIN        25
# define LED_ON           LOW
# define LED_OFF          HIGH
# define SLIDE_SWITCH_PIN (-1)
# define PUSHBUTTON_PIN   (-1)
# define CLI_SLIDER_ENABLED DISABLED
# define USB_MUX_PIN 23
# define BATTERY_PIN_1	  1
# define CURRENT_PIN_1	  2
#endif

#ifdef DESKTOP_BUILD
#define CONFIG_SONAR DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// IMU Selection
//
#ifndef CONFIG_INS_TYPE
# define CONFIG_INS_TYPE CONFIG_INS_OILPAN
#endif

//////////////////////////////////////////////////////////////////////////////
// ADC Enable - used to eliminate for systems which don't have ADC.
//
#ifndef CONFIG_ADC
# if CONFIG_INS_TYPE == CONFIG_INS_OILPAN
#   define CONFIG_ADC ENABLED
# else
#   define CONFIG_ADC DISABLED
# endif
#endif

#ifndef SONAR_TYPE
# define SONAR_TYPE             MAX_SONAR_LV	// MAX_SONAR_XL,
#endif

//////////////////////////////////////////////////////////////////////////////
// Sonar
//

#ifndef CONFIG_SONAR_SOURCE
# define CONFIG_SONAR_SOURCE SONAR_SOURCE_ADC
#endif

#if CONFIG_SONAR_SOURCE == SONAR_SOURCE_ADC && CONFIG_ADC == DISABLED
# warning Cannot use ADC for CONFIG_SONAR_SOURCE, becaude CONFIG_ADC is DISABLED
# warning Defaulting CONFIG_SONAR_SOURCE to ANALOG_PIN
# undef CONFIG_SONAR_SOURCE
# define CONFIG_SONAR_SOURCE SONAR_SOURCE_ANALOG_PIN
#endif

#if CONFIG_SONAR_SOURCE == SONAR_SOURCE_ADC
# ifndef CONFIG_SONAR_SOURCE_ADC_CHANNEL
#  define CONFIG_SONAR_SOURCE_ADC_CHANNEL 7
# endif
#elif CONFIG_SONAR_SOURCE == SONAR_SOURCE_ANALOG_PIN
# ifndef CONFIG_SONAR_SOURCE_ANALOG_PIN
#  define CONFIG_SONAR_SOURCE_ANALOG_PIN A0
# endif
#else
# warning Invalid value for CONFIG_SONAR_SOURCE, disabling sonar
# undef SONAR_ENABLED
# define SONAR_ENABLED DISABLED
#endif

#ifndef CONFIG_SONAR
# define CONFIG_SONAR ENABLED
#endif

#ifndef SONAR_TRIGGER
# define SONAR_TRIGGER       60        // trigger distance in cm
#endif

//////////////////////////////////////////////////////////////////////////////
// HIL_MODE                                 OPTIONAL

#ifndef HIL_MODE
#define HIL_MODE	HIL_MODE_DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// GPS_PROTOCOL
//
// Note that this test must follow the HIL_PROTOCOL block as the HIL
// setup may override the GPS configuration.
//
#ifndef GPS_PROTOCOL
# define GPS_PROTOCOL GPS_PROTOCOL_AUTO
#endif

#ifndef MAV_SYSTEM_ID
# define MAV_SYSTEM_ID		1
#endif

//////////////////////////////////////////////////////////////////////////////
// Serial port speeds.
//
#ifndef SERIAL0_BAUD
# define SERIAL0_BAUD			115200
#endif
#ifndef SERIAL3_BAUD
# define SERIAL3_BAUD			 57600
#endif

#ifndef CH7_OPTION
# define CH7_OPTION		          CH7_DO_NOTHING
#endif

#ifndef TUNING_OPTION
# define TUNING_OPTION		          TUN_NONE
#endif

//////////////////////////////////////////////////////////////////////////////
// Battery monitoring
//
#ifndef BATTERY_EVENT
# define BATTERY_EVENT			DISABLED
#endif
#ifndef LOW_VOLTAGE
# define LOW_VOLTAGE			9.6
#endif
#ifndef VOLT_DIV_RATIO
# define VOLT_DIV_RATIO			3.56	// This is the proper value for an on-board APM1 voltage divider with a 3.9kOhm resistor
#endif

#ifndef CURR_AMP_PER_VOLT
# define CURR_AMP_PER_VOLT		27.32	// This is the proper value for the AttoPilot 50V/90A sensor
#endif

#ifndef CURR_AMPS_OFFSET
# define CURR_AMPS_OFFSET		0.0
#endif
#ifndef HIGH_DISCHARGE
# define HIGH_DISCHARGE		1760
#endif

//////////////////////////////////////////////////////////////////////////////
// INPUT_VOLTAGE
//
#ifndef INPUT_VOLTAGE
# define INPUT_VOLTAGE			4.68	//  4.68 is the average value for a sample set.  This is the value at the processor with 5.02 applied at the servo rail
#endif

//////////////////////////////////////////////////////////////////////////////
//  MAGNETOMETER
#ifndef MAGNETOMETER
# define MAGNETOMETER			DISABLED
#endif
#ifndef MAG_ORIENTATION
# define MAG_ORIENTATION		AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// RADIO CONFIGURATION
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Radio channel limits
//
// Note that these are not called out in APM_Config.h.reference.
//
#ifndef CH5_MIN
# define CH5_MIN	1000
#endif
#ifndef CH5_MAX
# define CH5_MAX	2000
#endif
#ifndef CH6_MIN
# define CH6_MIN	1000
#endif
#ifndef CH6_MAX
# define CH6_MAX	2000
#endif
#ifndef CH7_MIN
# define CH7_MIN	1000
#endif
#ifndef CH7_MAX
# define CH7_MAX	2000
#endif
#ifndef CH8_MIN
# define CH8_MIN	1000
#endif
#ifndef CH8_MAX
# define CH8_MAX	2000
#endif


//////////////////////////////////////////////////////////////////////////////
// FLIGHT_MODE
// FLIGHT_MODE_CHANNEL
//
#ifndef FLIGHT_MODE_CHANNEL
# define FLIGHT_MODE_CHANNEL	8
#endif
#if (FLIGHT_MODE_CHANNEL != 5) && (FLIGHT_MODE_CHANNEL != 6) && (FLIGHT_MODE_CHANNEL != 7) && (FLIGHT_MODE_CHANNEL != 8)
# error XXX
# error XXX You must set FLIGHT_MODE_CHANNEL to 5, 6, 7 or 8
# error XXX
#endif

#if !defined(FLIGHT_MODE_1)
# define FLIGHT_MODE_1			LEARNING
#endif
#if !defined(FLIGHT_MODE_2)
# define FLIGHT_MODE_2			LEARNING
#endif
#if !defined(FLIGHT_MODE_3)
# define FLIGHT_MODE_3			LEARNING
#endif
#if !defined(FLIGHT_MODE_4)
# define FLIGHT_MODE_4			LEARNING
#endif
#if !defined(FLIGHT_MODE_5)
# define FLIGHT_MODE_5			LEARNING
#endif
#if !defined(FLIGHT_MODE_6)
# define FLIGHT_MODE_6			MANUAL
#endif


//////////////////////////////////////////////////////////////////////////////
// THROTTLE_FAILSAFE
// THROTTLE_FS_VALUE
// SHORT_FAILSAFE_ACTION
// LONG_FAILSAFE_ACTION
// GCS_HEARTBEAT_FAILSAFE
//
#ifndef THROTTLE_FAILSAFE
# define THROTTLE_FAILSAFE		ENABLED
#endif
#ifndef THROTTLE_FS_VALUE
# define THROTTLE_FS_VALUE		950
#endif
#ifndef SHORT_FAILSAFE_ACTION
# define SHORT_FAILSAFE_ACTION		0
#endif
#ifndef LONG_FAILSAFE_ACTION
# define LONG_FAILSAFE_ACTION		0
#endif
#ifndef GCS_HEARTBEAT_FAILSAFE
# define GCS_HEARTBEAT_FAILSAFE		DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// AUTO_TRIM
//
#ifndef AUTO_TRIM
# define AUTO_TRIM				DISABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// MANUAL_LEVEL
//
#ifndef MANUAL_LEVEL
# define MANUAL_LEVEL			DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// ENABLE_STICK_MIXING
//
#ifndef ENABLE_STICK_MIXING
# define ENABLE_STICK_MIXING	ENABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// THROTTLE_OUT
//
#ifndef THROTTE_OUT
# define THROTTLE_OUT			ENABLED
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// STARTUP BEHAVIOUR
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// GROUND_START_DELAY
//
#ifndef GROUND_START_DELAY
# define GROUND_START_DELAY		0
#endif

//////////////////////////////////////////////////////////////////////////////
// MOUNT (ANTENNA OR CAMERA)
//
#ifndef MOUNT
# define MOUNT		DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// AIRSPEED_CRUISE
//
#ifndef AIRSPEED_CRUISE
# define AIRSPEED_CRUISE		3 // 12 m/s
#endif
#define AIRSPEED_CRUISE_CM AIRSPEED_CRUISE*100

#ifndef GSBOOST
# define GSBOOST		0
#endif
#ifndef GSBOOST
# define GSBOOST		0
#endif
#ifndef NUDGE_OFFSET
# define NUDGE_OFFSET		0
#endif

#ifndef E_GLIDER
# define E_GLIDER		ENABLED
#endif

#ifndef TURN_GAIN
# define TURN_GAIN		5
#endif

//////////////////////////////////////////////////////////////////////////////
// MIN_GNDSPEED
//
#ifndef MIN_GNDSPEED
# define MIN_GNDSPEED			0 // m/s (0 disables)
#endif
#define MIN_GNDSPEED_CM MIN_GNDSPEED*100

//////////////////////////////////////////////////////////////////////////////
// Servo Mapping
//
#ifndef THROTTLE_MIN
# define THROTTLE_MIN			0 // percent
#endif
#ifndef THROTTLE_CRUISE
# define THROTTLE_CRUISE		45
#endif
#ifndef THROTTLE_MAX
# define THROTTLE_MAX			75
#endif

//////////////////////////////////////////////////////////////////////////////
// Autopilot control limits
//
#ifndef HEAD_MAX
# define HEAD_MAX				45
#endif
#ifndef PITCH_MAX
# define PITCH_MAX				15
#endif
#ifndef PITCH_MIN
# define PITCH_MIN				-25
#endif
#define HEAD_MAX_CENTIDEGREE HEAD_MAX * 100
#define PITCH_MAX_CENTIDEGREE PITCH_MAX * 100
#define PITCH_MIN_CENTIDEGREE PITCH_MIN * 100

//////////////////////////////////////////////////////////////////////////////
// Attitude control gains
//
#ifndef SERVO_ROLL_P
# define SERVO_ROLL_P         0.4
#endif
#ifndef SERVO_ROLL_I
# define SERVO_ROLL_I         0.0
#endif
#ifndef SERVO_ROLL_D
# define SERVO_ROLL_D         0.0
#endif
#ifndef SERVO_ROLL_INT_MAX
# define SERVO_ROLL_INT_MAX   5
#endif
#define SERVO_ROLL_INT_MAX_CENTIDEGREE SERVO_ROLL_INT_MAX*100
#ifndef ROLL_SLEW_LIMIT
# define ROLL_SLEW_LIMIT      0
#endif
#ifndef SERVO_PITCH_P
# define SERVO_PITCH_P        0.6
#endif
#ifndef SERVO_PITCH_I
# define SERVO_PITCH_I        0.0
#endif
#ifndef SERVO_PITCH_D
# define SERVO_PITCH_D        0.0
#endif
#ifndef SERVO_PITCH_INT_MAX
# define SERVO_PITCH_INT_MAX  5
#endif
#define SERVO_PITCH_INT_MAX_CENTIDEGREE SERVO_PITCH_INT_MAX*100
#ifndef PITCH_COMP
# define PITCH_COMP           0.2
#endif
#ifndef SERVO_YAW_P
# define SERVO_YAW_P          0.0
#endif
#ifndef SERVO_YAW_I
# define SERVO_YAW_I          0.0
#endif
#ifndef SERVO_YAW_D
# define SERVO_YAW_D          0.0
#endif
#ifndef SERVO_YAW_INT_MAX
# define SERVO_YAW_INT_MAX    0
#endif
#ifndef RUDDER_MIX
# define RUDDER_MIX           0.5
#endif


//////////////////////////////////////////////////////////////////////////////
// Navigation control gains
//
#ifndef NAV_ROLL_P
# define NAV_ROLL_P           0.7
#endif
#ifndef NAV_ROLL_I
# define NAV_ROLL_I           0.0
#endif
#ifndef NAV_ROLL_D
# define NAV_ROLL_D           0.02
#endif
#ifndef NAV_ROLL_INT_MAX
# define NAV_ROLL_INT_MAX     5
#endif
#define NAV_ROLL_INT_MAX_CENTIDEGREE NAV_ROLL_INT_MAX*100
#ifndef NAV_PITCH_ASP_P
# define NAV_PITCH_ASP_P      0.65
#endif
#ifndef NAV_PITCH_ASP_I
# define NAV_PITCH_ASP_I      0.0
#endif
#ifndef NAV_PITCH_ASP_D
# define NAV_PITCH_ASP_D      0.0
#endif
#ifndef NAV_PITCH_ASP_INT_MAX
# define NAV_PITCH_ASP_INT_MAX 5
#endif
#define NAV_PITCH_ASP_INT_MAX_CMSEC NAV_PITCH_ASP_INT_MAX*100
#ifndef NAV_PITCH_ALT_P
# define NAV_PITCH_ALT_P      0.65
#endif
#ifndef NAV_PITCH_ALT_I
# define NAV_PITCH_ALT_I      0.0
#endif
#ifndef NAV_PITCH_ALT_D
# define NAV_PITCH_ALT_D      0.0
#endif
#ifndef NAV_PITCH_ALT_INT_MAX
# define NAV_PITCH_ALT_INT_MAX 5
#endif
#define NAV_PITCH_ALT_INT_MAX_CM NAV_PITCH_ALT_INT_MAX*100


//////////////////////////////////////////////////////////////////////////////
// Energy/Altitude control gains
//
#ifndef THROTTLE_TE_P
# define THROTTLE_TE_P        0.50
#endif
#ifndef THROTTLE_TE_I
# define THROTTLE_TE_I        0.0
#endif
#ifndef THROTTLE_TE_D
# define THROTTLE_TE_D        0.0
#endif
#ifndef THROTTLE_TE_INT_MAX
# define THROTTLE_TE_INT_MAX  20
#endif
#ifndef THROTTLE_SLEW_LIMIT
# define THROTTLE_SLEW_LIMIT  0
#endif
#ifndef P_TO_T
# define P_TO_T               0
#endif
#ifndef T_TO_P
# define T_TO_P               0
#endif
#ifndef PITCH_TARGET
# define PITCH_TARGET         0
#endif

//////////////////////////////////////////////////////////////////////////////
// Crosstrack compensation
//
#ifndef XTRACK_GAIN
# define XTRACK_GAIN          1 // deg/m
#endif
#ifndef XTRACK_ENTRY_ANGLE
# define XTRACK_ENTRY_ANGLE   20 // deg
#endif
# define XTRACK_GAIN_SCALED XTRACK_GAIN*100
# define XTRACK_ENTRY_ANGLE_CENTIDEGREE XTRACK_ENTRY_ANGLE*100

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// DEBUGGING
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Dataflash logging control
//

#ifndef LOGGING_ENABLED
# define LOGGING_ENABLED		ENABLED
#endif


#ifndef LOG_ATTITUDE_FAST
# define LOG_ATTITUDE_FAST		DISABLED
#endif
#ifndef LOG_ATTITUDE_MED
# define LOG_ATTITUDE_MED 		ENABLED
#endif
#ifndef LOG_GPS
# define LOG_GPS 				ENABLED
#endif
#ifndef LOG_PM
# define LOG_PM 				DISABLED
#endif
#ifndef LOG_CTUN
# define LOG_CTUN				ENABLED
#endif
#ifndef LOG_NTUN
# define LOG_NTUN				DISABLED
#endif
#ifndef LOG_MODE
# define LOG_MODE				ENABLED
#endif
#ifndef LOG_RAW
# define LOG_RAW				DISABLED
#endif
#ifndef LOG_CMD
# define LOG_CMD				ENABLED
#endif
#ifndef LOG_CUR
# define LOG_CUR			DISABLED
#endif

// calculate the default log_bitmask
#define LOGBIT(_s)	(LOG_##_s ? MASK_LOG_##_s : 0)

#define DEFAULT_LOG_BITMASK \
		LOGBIT(ATTITUDE_FAST)	| \
		LOGBIT(ATTITUDE_MED)	| \
		LOGBIT(GPS)				| \
		LOGBIT(PM)				| \
		LOGBIT(CTUN)			| \
		LOGBIT(NTUN)			| \
		LOGBIT(MODE)			| \
		LOGBIT(RAW)				| \
		LOGBIT(CMD)				| \
		LOGBIT(CUR)


//////////////////////////////////////////////////////////////////////////////
// Navigation defaults
//
#ifndef WP_RADIUS_DEFAULT
# define WP_RADIUS_DEFAULT		2
#endif

//////////////////////////////////////////////////////////////////////////////
// Developer Items
//

#ifndef STANDARD_SPEED
# define STANDARD_SPEED		3.0
#define STANDARD_SPEED_SQUARED (STANDARD_SPEED * STANDARD_SPEED)
#endif
#define STANDARD_THROTTLE_SQUARED (THROTTLE_CRUISE * THROTTLE_CRUISE)

// use this to enable servos in HIL mode
#ifndef HIL_SERVOS
# define HIL_SERVOS DISABLED
#endif

#ifndef TRACE
# define TRACE DISABLED
#endif

// use this to completely disable the CLI
#ifndef CLI_ENABLED
# define CLI_ENABLED ENABLED
#endif

// use this to disable the CLI slider switch
#ifndef CLI_SLIDER_ENABLED
# define CLI_SLIDER_ENABLED ENABLED
#endif

// if RESET_SWITCH_CH is not zero, then this is the PWM value on
// that channel where we reset the control mode to the current switch
// position (to for example return to switched mode after failsafe or
// fence breach)
#ifndef RESET_SWITCH_CHAN_PWM
# define RESET_SWITCH_CHAN_PWM 1750
#endif

#ifndef BOOSTER
# define BOOSTER              2    // booster factor x1 = 1 or x2 = 2
#endif

#ifndef SONAR_ENABLED
# define SONAR_ENABLED       DISABLED
#endif
