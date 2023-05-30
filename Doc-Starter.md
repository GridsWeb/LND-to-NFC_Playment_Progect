# Starter

1. การเตรียมอุปกรณ์ :

    - Arduino board : สามารถใช้ Arduino Uno, Arduino Mega, หรือบอร์ดอื่นๆ ที่สนับสนุนการเชื่อมต่ออุปกรณ์เสริม
    - NFC reader module : เลือกโมดูลที่สามารถอ่านข้อมูลจากแท็ก NFC และสื่อสารกับ Arduino ได้ เช่น PN532 NFC module
    - LCD display : ใช้เพื่อแสดงข้อมูลการชำระเงินและข้อความอื่น ๆ เช่นจอ LCD 16x2
    - Payment processing module : เช่นโมดูลเพิ่มเติมหรือบริการฝั่งเซิร์ฟเวอร์สำหรับการตรวจสอบและการดำเนินการการชำระเงิน

2. การติดตั้งและการเชื่อมต่อ :

    - ติดตั้งไลบรารี NFC สำหรับ Arduino เช่น PN532 library
    - เชื่อมต่อโมดูล NFC reader กับ Arduino ผ่านสายสัญญาณที่เหมาะสม (เช่น I2C, SPI)
    - เชื่อมต่อจอ LCD กับ Arduino โดยเชื่อมต่อขาและทำการตั้งค่าตามคำแนะนำของจอ LCD ที่ใช้งาน

3. การเขียนโค้ด Arduino :

    - ตัวอย่างเริ่มต้น และ คำอธิบาย Code :

~~~cpp
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
  while (!nfc.ready()) {
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
~~~

    - อธิบายโค้ดเริ่มต้นของโครงการ "LND-to-NFC_Playment_Progect" ดังนี้ :

        1. นำเข้าไลบรารีที่จำเป็น :

            - **Wire** (`Wire.h`) : เพื่อใช้งาน I2C (สำหรับการเชื่อมต่อกับจอ LCD)
            - **Adafruit_PN532** (`Adafruit_PN532.h`) : เพื่อใช้งานโมดูล NFC reader
            - **LiquidCrystal_I2C.h** (`LiquidCrystal_I2C.h`) : เพื่อใช้งานจอ LCD ผ่าน I2C

        2. กำหนดค่าคงที่สำหรับ**โมดูล NFC reader** :

            - `SDA_PIN` : ขา `SDA` (ขาข้อมูลใน I2C) ที่เชื่อมต่อกับโมดูล NFC reader
            - `SCL_PIN` : ขา `SCL` (ขานาฬิกาใน I2C) ที่เชื่อมต่อกับโมดูล NFC reader

        3. กำหนดค่าคงที่สำหรับจอ LCD :

            - `LCD_ADDRESS`: ที่อยู่ I2C ของจอ LCD
            - `LCD_COLUMNS`: จำนวนคอลัมน์ของจอ LCD
            - `LCD_ROWS`: จำนวนแถวของจอ LCD

        4. กำหนดตัวแปรสำหรับอ็อบเจ็กต์ของ NFC reader และจอ LCD :

            - `nfc` : อ็อบเจ็กต์สำหรับ NFC reader
            - `lcd` : อ็อบเจ็กต์สำหรับจอ LCD

        5. ขั้นตอนการทำงานของฟังก์ชัน `setup()`:

            - เริ่มต้นการสื่อสารทาง Serial
            - เริ่มต้นการทำงานของ NFC reader
            - กำหนดค่าเริ่มต้นของจอ LCD
            - รอให้ NFC reader เตรียมพร้อม
            - ล้างจอ LCD และแสดงข้อความ "Ready for Payment"

        6. ขั้นตอนการทำงานของฟังก์ชัน `loop()` :

            - ประกาศตัวแปร `success`, `uid`, และ `uidLength` สำหรับการอ่านข้อมูลจาก NFC reader
            - ตรวจสอบว่ามีการ์ด NFC หรือแท็กที่วางบนเครื่องหรือไม่
            - หากมีการ์ด/แท็กถูกวาง จะเรียกใช้ฟังก์ชัน `processPayment()` เพื่อดำเนินการการชำระเงิน

        7. ขั้นตอนการทำงานของฟังก์ชัน `processPayment()` :

            - ดำเนินการขั้นตอนการชำระเงิน ซึ่งคุณสามารถปรับแต่งเพื่อเข้ากับการตรวจสอบและการดำเนินการการชำระเงินของคุณ
            - แสดงข้อความ "Processing..." และแสดงหมายเลขบัตรที่อ่านจากการ์ด NFC บนจอ LCD
            - จำลองความล่าช้าในการประมวลผลการชำระเงินด้วยการหน่วงเวลา 3 วินาที
            - จำลองความสำเร็จในการชำระเงิน ในตัวอย่างนี้จะถือว่าการชำระเงินสำเร็จ
            - แสดงข้อความ "Payment Successful" หรือ "Payment Failed" บนจอ LCD ตามผลการชำระเงิน
            - ล้างจอ LCD และกลับไปสู่สถานะพร้อมสำหรับการชำระเงินถัดไป

  โค้ดดังกล่าวจะเป็นตัวอย่างเบื้องต้นที่ใช้ในการอ่านการ์ด NFC และแสดงผลการชำระเงินบนจอ LCD คุณสามารถปรับแต่งโค้ดเพื่อตรวจสอบและดำเนินการการชำระเงินอื่นๆ ตามความต้องการของโครงการของคุณได้

4. การปรับแต่งและการทดสอบ :

  - ปรับแต่งโค้ดเพื่อตรวจสอบความถูกต้องและความปลอดภัยของการชำระเงิน
  - ทดสอบโครงการโดยใช้แท็ก NFC หรืออุปกรณ์มือถือที่รองรับ NFC และตรวจสอบผลลัพธ์ที่จอ LCD
  - แก้ไขปัญหาหากเกิดข้อผิดพลาดหรือข้อบกพร่องในการทำงาน

หากต้องการข้อมูลเพิ่มเติม, หรือ มีความคิดเห็นใดๆเพิ่มเติม หรือ ต้องการแก้ไขส่วนใด อย่ารังเลใจที่จะติดต่อฉัน 
สามารถติดต่อฉันได้ที่ email : grids@microtronic.biz
