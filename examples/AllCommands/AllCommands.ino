#include <SensirionCoreArduinoLibrary.h>
#include <stdint.h>

uint8_t txBuffer[256];
uint8_t rxBuffer[256];

SensirionShdlcTxFrame txFrame(txBuffer, 256);
SensirionShdlcRxFrame rxFrame(rxBuffer, 256);
SensirionShdlcCommunication hardwareCom;

void setup() {
  Serial.begin(115200);
  hardwareCom.begin(&Serial);
}

void loop() {
  uint8_t mockCommand = 42;
  uint8_t mockAddress = 42;
  uint8_t mockDataLength = 42;
  uint16_t error = txFrame.begin(mockCommand, mockAddress, mockDataLength);

  uint32_t mockUInt32 = 42;
  error |= txFrame.addUInt32(mockUInt32);

  int32_t mockInt32 = 42;
  error |= txFrame.addInt32(mockInt32);

  uint16_t mockUInt16 = 42;
  error |= txFrame.addUInt16(mockUInt16);

  int16_t mockInt16 = 42;
  error |= txFrame.addInt16(mockInt16);

  uint8_t mockUInt8 = 42;
  error |= txFrame.addUInt8(mockUInt8);

  int8_t mockInt8 = 42;
  error |= txFrame.addInt8(mockInt8);

  float mockFloat = 42.0;
  error |= txFrame.addFloat(mockFloat);

  bool mockBool = true;
  error |= txFrame.addBool(mockBool);

  uint8_t mockBytes[] = {42, 42, 42, 42};
  error |= txFrame.addBytes(&mockBytes[0], 4);

  error |= txFrame.finish();

  error |= hardwareCom.sendFrame(txFrame);

  error |= txFrame.reset();

  error |= hardwareCom.receiveFrame(rxFrame);

  error |= rxFrame.processHeader();

  error |= rxFrame.getUInt32(&mockUInt32);
  error |= rxFrame.getInt32(&mockInt32);
  error |= rxFrame.getUInt16(&mockUInt16);
  error |= rxFrame.getInt16(&mockInt16);
  error |= rxFrame.getUInt8(&mockUInt8);
  error |= rxFrame.getInt8(&mockInt8);
  error |= rxFrame.getFloat(&mockFloat);
  error |= rxFrame.getBytes(&mockBytes[0], 4);

  error |= rxFrame.processTail();

  rxFrame.reset();
}
