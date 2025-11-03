#ifndef _CONFIG_H
#define _CONFIG_H

#include <RadioLib.h>

// First, set your radio model and pin configuration.
// This is provided as a default example.
// Example: SX1278 radio = new Module(10, 2, 9, 3);

// Use supported RadioBoards pin configurations
// (https://github.com/radiolib-org/RadioBoards).

#define RADIO_BOARD_AUTO
#include <RadioBoards.h>

Radio radio = new RadioModule();

// How often to send an uplink. Consider legal constraints for your region.
const uint32_t uplinkIntervalSeconds = 1UL * 30UL; // minutes x seconds

#define LORAWAN_VERSION  (0) // Use version 1.LORAWAN_VERSION when joining. Helium prefers 1.0.x
#define LORAWAN_OTAA     (1) // Use OTAA (1) or ABP (0)

//---

#if (LORAWAN_OTAA == 1)
#if (LORAWAN_OTAA == 1)
// joinEUI (previously called AppEUI in older LoRaWAN versions).
// For development purposes, you can use all zeros—see the project wiki for details.
#define RADIOLIB_LORAWAN_JOIN_EUI  0x751BC6DD53B32FE1
#endif
// The device EUI and keys can be generated on the LNS (Network Server).
#ifndef RADIOLIB_LORAWAN_DEV_EUI   // Replace with your Device EUI
#define RADIOLIB_LORAWAN_DEV_EUI   0x5225BB996093794D
#endif
#ifndef RADIOLIB_LORAWAN_APP_KEY   // Replace with your App Key
#define RADIOLIB_LORAWAN_APP_KEY   0x8D, 0xEC, 0xCD, 0x33, 0x41, 0xA0, 0xCE, 0x84, 0xD3, 0xBA, 0xC9, 0x3D, 0x6B, 0x7B, 0x1C, 0x34
#endif

//---

// Copy the EUIs and keys into typed variables so incorrect formatting will fail to compile.
uint64_t joinEUI = RADIOLIB_LORAWAN_JOIN_EUI;
uint64_t devEUI  = RADIOLIB_LORAWAN_DEV_EUI;
uint8_t appKey[] = { RADIOLIB_LORAWAN_APP_KEY };

#if (LORAWAN_VERSION == 1)
#ifndef RADIOLIB_LORAWAN_NWK_KEY   // Put your Nwk Key here
#define RADIOLIB_LORAWAN_NWK_KEY   0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- 
#endif
uint8_t nwkKey[] = { RADIOLIB_LORAWAN_NWK_KEY };  // LW v1.1 only
#endif

#else // ABP

#ifndef RADIOLIB_LORAWAN_DEV_ADDR   // Replace with your DevAddr
#define RADIOLIB_LORAWAN_DEV_ADDR   0x------
#endif

#ifndef RADIOLIB_LORAWAN_NWKSENC_KEY   // Replace with your NwkSEnc Key 
#define RADIOLIB_LORAWAN_NWKSENC_KEY   0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- 
#endif
#ifndef RADIOLIB_LORAWAN_APPS_KEY   // Replace with your AppS Key 
#define RADIOLIB_LORAWAN_APPS_KEY   0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- 
#endif

// Copy the keys into typed variables so incorrect formatting will fail to compile.
uint32_t devAddr = RADIOLIB_LORAWAN_DEV_ADDR;
uint8_t sNwkSEncKey[] = { RADIOLIB_LORAWAN_NWKSENC_KEY };
uint8_t appSKey[] = { RADIOLIB_LORAWAN_APPS_KEY };

#if (LORAWAN_VERSION == 1)
#ifndef RADIOLIB_LORAWAN_FNWKSINT_KEY   // Replace with your FNwkSInt Key 
#define RADIOLIB_LORAWAN_FNWKSINT_KEY   0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- 
#endif
#ifndef RADIOLIB_LORAWAN_SNWKSINT_KEY   // Replace with your SNwkSInt Key 
#define RADIOLIB_LORAWAN_SNWKSINT_KEY   0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- 
#endif
uint8_t fNwkSIntKey[] = { RADIOLIB_LORAWAN_FNWKSINT_KEY };  // LW v1.1 only
uint8_t sNwkSIntKey[] = { RADIOLIB_LORAWAN_SNWKSINT_KEY };  // LW v1.1 only
#endif

#endif // OTAA/ABP

// For the curious: the #ifndef blocks allow automated testing, or you can
// define your EUI and keys in `platformio.ini`. See the project wiki for more tips.

// Regional choices: EU868, US915, AU915, AS923, IN865, KR920, CN780, CN500
const LoRaWANBand_t Region = US915;
const uint8_t subBand = 2; // For US915, change this to 2; otherwise leave at 0.

// ============================================================================
// Below is to support the sketch - only make changes if the notes say so ...

// create the LoRaWAN node
LoRaWANNode node(&radio, &Region, subBand);

// Helper function to display any issues.
void debug(bool isFail, const __FlashStringHelper* message, int state, bool Freeze) {
  if (isFail) {
    Serial.print(message);
    Serial.print("(");
    Serial.print(state);
    Serial.println(")");
    while (Freeze);
  }
}

// Helper function to display a byte array.
void arrayDump(uint8_t *buffer, uint16_t len) {
  for (uint16_t c = 0; c < len; c++) {
    uint8_t b = buffer[c];
    if (b < 0x10) { Serial.print('0'); }
    Serial.print(b, HEX);
  }
  Serial.println();
}

#endif