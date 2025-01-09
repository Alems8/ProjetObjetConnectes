#include <Servo.h>
#include "nfc_utils.h"
#include "rfal_nfc.h"
#include "rfal_rfst25r3911.h"
#include "ndef_class.h"

/* Servo setup */
Servo myServo;
const int servoPin = D8;

// UART Communication
HardwareSerial Serial1(D2, D10); // RX, TX for Arduino

/* NFC configuration */
#define SPI_MOSI D11
#define SPI_MISO D12
#define SPI_SCK D13
#define CS_PIN D10
#define IRQ_PIN A0

/* NFC State Definitions */
#define DEMO_ST_NOTINIT          0  /*!< Demo State: Not initialized */
#define DEMO_ST_START_DISCOVERY  1  /*!< Demo State: Start Discovery */
#define DEMO_ST_DISCOVERY        2  /*!< Demo State: Discovery */

SPIClass dev_spi(SPI_MOSI, SPI_MISO, SPI_SCK);
RfalRfST25R3911BClass rfst25r3911b(&dev_spi, CS_PIN, IRQ_PIN);
RfalNfcClass rfal_nfc(&rfst25r3911b);
NdefClass ndef(&rfal_nfc);

static rfalNfcDiscoverParam discParam;
static uint8_t state = DEMO_ST_NOTINIT;

/* Replace with your tag's UID */
const uint8_t validUID[] = {0x27, 0x59, 0xAF, 0x1C};

void setup() {
  Serial1.begin(9600); // Communication with Arduino
  dev_spi.begin();

  myServo.attach(servoPin);
  myServo.write(0); // Lock door by default

  if (rfal_nfc.rfalNfcInitialize() == ERR_NONE) {
    discParam.compMode = RFAL_COMPLIANCE_MODE_NFC;
    discParam.devLimit = 1U;
    discParam.nfcfBR = RFAL_BR_212;
    discParam.ap2pBR = RFAL_BR_424;
    discParam.techs2Find = (RFAL_NFC_POLL_TECH_A | RFAL_NFC_POLL_TECH_B);
    state = DEMO_ST_START_DISCOVERY;
    Serial1.println("#NFC_INITIALIZED#");
  } else {
    Serial1.println("#NFC_FAILED#");
  }
}

void loop() {
  static rfalNfcDevice *nfcDevice;

  rfal_nfc.rfalNfcWorker();

  switch (state) {
    case DEMO_ST_START_DISCOVERY:
      rfal_nfc.rfalNfcDeactivate(false);
      rfal_nfc.rfalNfcDiscover(&discParam);
      state = DEMO_ST_DISCOVERY;
      break;

    case DEMO_ST_DISCOVERY:
      if (rfalNfcIsDevActivated(rfal_nfc.rfalNfcGetState())) {
        rfal_nfc.rfalNfcGetActiveDevice(&nfcDevice);
        if (isValidTag(nfcDevice)) {
          Serial1.println("#VALID_NFC_TAG#");
          unlockDoor();
        } else {
          Serial1.println("#INVALID_NFC_TAG#");
        }
        rfal_nfc.rfalNfcDeactivate(false);
        state = DEMO_ST_START_DISCOVERY;
      }
      break;

    default:
      break;
  }

  if (Serial1.available()) {
    String command = Serial1.readStringUntil('\n');
    handleCommand(command);
  }
}

bool isValidTag(rfalNfcDevice *device) {
  return (memcmp(device->nfcid, validUID, sizeof(validUID)) == 0);
}

void unlockDoor() {
  myServo.write(90); // Unlock position
  Serial1.println("#DOOR_UNLOCKED#");
}

void lockDoor() {
  myServo.write(0); // Lock position
  Serial1.println("#DOOR_LOCKED#");
}

void handleCommand(String command) {
  if (command == "LOCK_DOOR") {
    lockDoor();
  } else if (command == "UNLOCK_DOOR") {
    unlockDoor();
  } else {
    Serial1.println("#UNKNOWN_COMMAND#");
  }
}


// HardwareSerial Serial1(D2,D10);

// void setup() {
//   Serial1.begin(115200);
// }

// void loop() {
//   Serial1.println("Test from Nucleo");
//   delay(1000);
// }


