#ifndef _NET_MOSQ_H_
#define _NET_MOSQ_H_

#include <stdint.h>

/* Macros for accessing the MSB and LSB of a uint16_t */
#define MOSQ_MSB(A) (uint8_t)((A & 0xFF00) >> 8)
#define MOSQ_LSB(A) (uint8_t)(A & 0x00FF)

struct _mosquitto_packet{
	uint8_t command;
	uint8_t command_saved;
	uint8_t have_remaining;
	uint8_t remaining_count;
	uint32_t remaining_mult;
	uint32_t remaining_length;
	uint32_t to_process;
	uint32_t pos;
	uint8_t *payload;
	struct _mosquitto_packet *next;
};

int _mosquitto_socket_connect(const char *host, uint16_t port);

int _mosquitto_read_byte(struct _mosquitto_packet *packet, uint8_t *byte);
int _mosquitto_read_bytes(struct _mosquitto_packet *packet, uint8_t *bytes, uint32_t count);
int _mosquitto_read_string(struct _mosquitto_packet *packet, char **str);
int _mosquitto_read_uint16(struct _mosquitto_packet *packet, uint16_t *word);

int _mosquitto_write_byte(struct _mosquitto_packet *packet, uint8_t byte);
int _mosquitto_write_bytes(struct _mosquitto_packet *packet, const uint8_t *bytes, uint32_t count);
int _mosquitto_write_string(struct _mosquitto_packet *packet, const char *str, uint16_t length);
int _mosquitto_write_uint16(struct _mosquitto_packet *packet, uint16_t word);

#endif
