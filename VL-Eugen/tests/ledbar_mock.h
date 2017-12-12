/* Diese Header File wird fuer diverse Tests benoetigt.
 * NICHT VERAENDERN!
 */
#ifndef CMOCK_TEST_FOO_MOCK_H_
#define CMOCK_TEST_FOO_MOCK_H_

#include "cmock/cmock.h"
#include "ledbar.h" // use original function declaration

DECLARE_FUNCTION_MOCK2(SetLedMock, set_led, int(leds, brightness));

#endif /* CMOCK_TEST_FOO_MOCK_H_ */
