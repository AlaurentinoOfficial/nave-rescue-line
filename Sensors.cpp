#include "Sensors.h"

// Mesuare the RGB color in the sensor
void ColorRaw(RGB * color, uint8_t port)
{
	// Get red value
	digitalWrite(S2, LOW);
	digitalWrite(S3, LOW);
	color->red = pulseIn(port, LOW);

	// Get green value
	digitalWrite(S2, HIGH);
	digitalWrite(S3, HIGH);
	color->green = pulseIn(port, LOW);

	// Get blue value
	digitalWrite(S2, LOW);
	digitalWrite(S3, HIGH);
	color->blue = pulseIn(port, LOW);

	return color;
}
