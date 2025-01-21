// Import of the libraries
#include <Servo.h>
#include "nfc_utils.h"
#include "rfal_nfc.h"
#include "rfal_rfst25r3911.h"
#include "ndef_class.h"

/* Servo setup */
Servo myServo;
const int servoPin = D8;



/* NFC configuration */
#define SPI_MOSI D11
#define SPI_MISO D12
#define SPI_SCK D13
#define CS_PIN D10
#define LED_A_PIN A3
#define LED_B_PIN A2
#define LED_F_PIN A1
#define LED_V_PIN D5
#define LED_AP2P_PIN D4
#define LED_FIELD_PIN D7
#define IRQ_PIN A0

/* Definition of possible states the demo state machine could have */
#define DEMO_ST_NOTINIT               0  /*!< Demo State:  Not initialized */
#define DEMO_ST_START_DISCOVERY       1  /*!< Demo State:  Start Discovery */
#define DEMO_ST_DISCOVERY             2  /*!< Demo State:  Discovery       */

#define NDEF_DEMO_READ              0U   /*!< NDEF menu read               */
#define NDEF_DEMO_WRITE_MSG1        1U   /*!< NDEF menu write 1 record     */
#define NDEF_DEMO_WRITE_MSG2        2U   /*!< NDEF menu write 2 records    */
#define NDEF_DEMO_FORMAT_TAG        3U   /*!< NDEF menu format tag         */

#define NDEF_DEMO_MAX_FEATURES      4U   /*!< Number of menu items         */

#define NDEF_WRITE_FORMAT_TIMEOUT   10000U /*!< When write or format mode is selected, demo returns back to read mode after a timeout */
#define NDEF_LED_BLINK_DURATION       250U /*!< Led blink duration         */

#define DEMO_RAW_MESSAGE_BUF_LEN      8192 /*!< Raw message buffer len     */

#define DEMO_ST_MANUFACTURER_ID      0x02U /*!< ST Manufacturer ID         */

SPIClass dev_spi(SPI_MOSI, SPI_MISO, SPI_SCK);
RfalRfST25R3911BClass rfst25r3911b(&dev_spi, CS_PIN, IRQ_PIN);
RfalNfcClass rfal_nfc(&rfst25r3911b);
NdefClass ndef(&rfal_nfc);

static rfalNfcDiscoverParam discParam;
static uint8_t state = DEMO_ST_NOTINIT;

/* Valid tag UID for detection */
const uint8_t validUID[] = {0x27, 0x59, 0xAF, 0x1C};

void setup() {
  Serial.begin(115200);
  dev_spi.begin();

  /* Initialize servo */
  myServo.attach(servoPin);
  myServo.write(0); 
  delay(1000);

  /* Initialize NFC */
  Serial.println("Initializing NFC and Servo...");
  if (rfal_nfc.rfalNfcInitialize() == ERR_NONE) {
    discParam.compMode      = RFAL_COMPLIANCE_MODE_NFC;
    discParam.devLimit      = 1U;
    discParam.nfcfBR        = RFAL_BR_212;
    discParam.ap2pBR        = RFAL_BR_424;

    discParam.notifyCb             = NULL;
    discParam.totalDuration        = 1000U;
    discParam.wakeupEnabled        = false;
    discParam.wakeupConfigDefault  = true;
    discParam.techs2Find           = (RFAL_NFC_POLL_TECH_A | RFAL_NFC_POLL_TECH_B | RFAL_NFC_POLL_TECH_F | RFAL_NFC_POLL_TECH_V | RFAL_NFC_POLL_TECH_ST25TB);
    discParam.techs2Find   |= RFAL_NFC_POLL_TECH_AP2P;

    state = DEMO_ST_START_DISCOVERY;
    Serial.println("NFC Initialized.");
  } else {
    Serial.println("NFC Initialization Failed!");
  }
}

void loop() {
  static rfalNfcDevice *nfcDevice;

  rfal_nfc.rfalNfcWorker(); // Run NFC worker periodically

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
          Serial.println("Valid NFC Tag Detected. Unlocking Door...");
          unlockDoor();
          delay(10000); // Keep door unlocked for 10 seconds
          lockDoor();
          Serial.println("Door Locked.");
        } else {
          Serial.println("Invalid NFC Tag Detected.");
        }

        rfal_nfc.rfalNfcDeactivate(false);
        state = DEMO_ST_START_DISCOVERY;
      }
      break;

    default:
      break;
  }

      // Manual Command Handling used for testing
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "UNLOCK_DOOR") {
      unlockDoor();
    } else if (command == "LOCK_DOOR") {
      lockDoor();
    } else {
      Serial.println("Unknown command: " + command);
    }
  }
}

/* Function to validate the detected NFC tag */
bool isValidTag(rfalNfcDevice *device) {
  return (memcmp(device->nfcid, validUID, sizeof(validUID)) == 0);
}

/* Unlock door function */
void unlockDoor() {
  myServo.write(180);  
  Serial.println("Unlocking door");
}

/* Lock door function */
void lockDoor() {
  myServo.write(0);
  Serial.println("Locking door");
}



