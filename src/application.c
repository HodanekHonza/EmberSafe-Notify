#include <application.h>

twr_tmp112_t temp;

void tmp112_event_handler(twr_tmp112_t *self, twr_tmp112_event_t event, void *event_param)
{
    (void) self;
    (void) event_param;

    if (event == TWR_TMP112_EVENT_UPDATE)
    {
        float temperature = 0.0;
        int16_t rawTemperature = 0;
        twr_tmp112_get_temperature_celsius(&temp, &temperature);
        twr_tmp112_get_temperature_raw(&temp, &rawTemperature);
        twr_log_debug("%.4f °C\r\n%d", temperature, rawTemperature);
    }
}

void application_init(void)
{
    // initialize logging
    twr_log_init(TWR_LOG_LEVEL_DEBUG, TWR_LOG_TIMESTAMP_ABS);

    // initialize TMP112 sensor
    twr_tmp112_init(&temp, TWR_I2C_I2C0, 0x49);

    // set measurement handler (call "tmp112_event_handler()" after measurement)
    twr_tmp112_set_event_handler(&temp, tmp112_event_handler, NULL);

    // automatically measure the temperature every 5 seconds
    twr_tmp112_set_update_interval(&temp, 5000);
}