// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

static void init_barometer(void)
{
    barometer.calibrate(mavlink_delay);
    ahrs.set_barometer(&barometer);
    gcs_send_text_P(SEVERITY_LOW, PSTR("barometer calibration complete"));
}

// filter altitude from the barometer with a 0.3 low pass
// filter
static LowPassFilterInt32 altitude_filter(0.3);

// read the barometer and return the updated altitude in centimeters
// above the calibration altitude
static int32_t read_barometer(void)
{
    barometer.read();
    return altitude_filter.apply(barometer.get_altitude() * 100.0);
}

// in M/S * 100
static void read_airspeed(void)
{
    airspeed.read();
    calc_airspeed_errors();
}

static void zero_airspeed(void)
{
    airspeed.calibrate(mavlink_delay);
    gcs_send_text_P(SEVERITY_LOW,PSTR("zero airspeed calibrated"));
}

static void read_battery(void)
{
    if(g.battery_monitoring == 0) {
        battery_voltage1 = 0;
        return;
    }

    if(g.battery_monitoring == 3 || g.battery_monitoring == 4) {
        static AP_AnalogSource_Arduino bat_pin(BATTERY_PIN_1);
        battery_voltage1 = BATTERY_VOLTAGE(bat_pin.read_average());
    }
    if(g.battery_monitoring == 4) {
        static AP_AnalogSource_Arduino current_pin(CURRENT_PIN_1);
        current_amps1    = CURRENT_AMPS(current_pin.read_average());
        current_total1   += current_amps1 * (float)delta_ms_medium_loop * 0.0002778;                                    // .0002778 is 1/3600 (conversion to hours)
    }

#if BATTERY_EVENT == ENABLED
    if(battery_voltage1 < LOW_VOLTAGE) low_battery_event();
    if(g.battery_monitoring == 4 && current_total1 > g.pack_capacity) low_battery_event();
#endif
}


// read the receiver RSSI as an 8 bit number for MAVLink
// RC_CHANNELS_SCALED message
void read_receiver_rssi(void)
{
#if RECEIVER_RSSI_PIN != -1
    float ret = RSSI_pin.read();
    receiver_rssi = constrain(ret, 0, 255);
#endif
}


/*
  return current_loc.alt adjusted for ALT_OFFSET
  This is useful during long flights to account for barometer changes
  from the GCS, or to adjust the flying height of a long mission
 */
static int32_t adjusted_altitude_cm(void)
{
    return current_loc.alt - (g.alt_offset*100);
}
