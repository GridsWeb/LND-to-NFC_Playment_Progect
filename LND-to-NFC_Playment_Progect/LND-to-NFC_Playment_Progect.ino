#include <Wire.h>
#include <Adafruit_PN532.h>
#include <LiquidCrystal_I2C.h>

// Constants for NFC reader
#define SDA_PIN 10
#define SCL_PIN 11

// Constants for LCD display
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Initialize NFC reader
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

// Initialize LCD display
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(115200);

  // Initialize NFC reader
  nfc.begin();

  // Set up the LCD display
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.print("NFC Payment");
  lcd.setCursor(0, 1);
  lcd.print("Terminal");

  // Wait for NFC reader to be ready
  while (!nfc.SAMConfig()) {
    delay(100);
  }

  // Clear LCD display
  lcd.clear();
  lcd.print("Ready for");
  lcd.setCursor(0, 1);
  lcd.print("Payment");
}

void loop() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  // Check if an NFC card/tag is present
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {
    // Card detected, process payment
    processPayment(uid, uidLength);
  }
}

void processPayment(uint8_t *uid, uint8_t uidLength) {
  // Perform payment processing steps here
  // This is where you can communicate with a payment gateway or service

  // Convert UID to a string for display
  String uidString = "";
  for (uint8_t i = 0; i < uidLength; i++) {
    uidString += String(uid[i], HEX);
  }

  // Display payment processing message on LCD
  lcd.clear();
  lcd.print("Processing...");
  lcd.setCursor(0, 1);
  lcd.print("Card: " + uidString);

  // Simulate payment processing delay
  delay(3000);

  // Simulate payment success
  bool paymentSuccess = true;

  if (paymentSuccess) {
    // Display payment success message on LCD
    lcd.clear();
    lcd.print("Payment");
    lcd.setCursor(0, 1);
    lcd.print("Successful");

    // Delay for a few seconds to display the success message
    delay(5000);
  } else {
    // Display payment failure message on LCD
    lcd.clear();
    lcd.print("Payment");
    lcd.setCursor(0, 1);
    lcd.print("Failed");

    // Delay for a few seconds to display the failure message
    delay(5000);
  }

  // Clear LCD display and go back to the ready state
  lcd.clear();
  lcd.print("Ready for");
  lcd.setCursor(0, 1);
  lcd.print("Payment");
}
