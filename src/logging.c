#include <stdarg.h>
#include <stdio.h>
#include <syslog.h>

#include <mqtt3.h>

/* Options for logging should be:
 *
 * A combination of:
 * Via syslog
 * To a file
 * To stdout/stderr
 * To topics
 */

/* Give option of logging timestamp.
 * Logging pid.
 */
static int log_types = 0;
static int max_level = 0;

int mqtt3_log_init(int level, int types)
{
	int rc = 0;

	max_level = level;
	log_types = types;

	if(log_types & LOG_SYSLOG){
		openlog("mosquitto", LOG_PID, LOG_DAEMON);
	}
	/* FIXME - do something for all types! */

	return rc;
}

int mqtt3_log_close(void)
{
	if(log_types & LOG_SYSLOG){
		closelog();
	}
	/* FIXME - do something for all types! */

	return 0;
}

int mqtt3_log_printf(int level, int type, const char *fmt, ...)
{
	va_list va;
	char s[500];

	if(level <= max_level && (log_types & type)==type){
		va_start(va, fmt);
		vsnprintf(s, 500, fmt, va);
		va_end(va);

		/* FIXME - do something! */
	}

	return 0;
}
