/*
  GrayKazu v1.4.0 - SSD1306 0.96" I2C Test
  SDA: GPIO42, SCL: GPIO47
  Hiển thị 513 icon Material 24x24, auto lật trang
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <GrayKazu.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SDA_PIN 42
#define SCL_PIN 47

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


extern const int epd_bitmap_allArray_LEN;
extern const unsigned char* epd_bitmap_allArray[513];

#define ICON_W 24
#define ICON_H 24
#define GAP_X 2
#define GAP_Y 2
#define HEADER_H 10

int currentPage = 0;
uint32_t lastPageTime = 0;
const uint16_t PAGE_DELAY_MS = 2000; // 2s đổi trang vì màn nhỏ

void setup() {
  Serial.begin(115200);

  // Init I2C với chân custom
  Wire.begin(SDA_PIN, SCL_PIN);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed");
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  drawPage(0);
  lastPageTime = millis();
}

void loop() {
  if (millis() - lastPageTime > PAGE_DELAY_MS) {
    currentPage++;
    int cols = SCREEN_WIDTH / (ICON_W + GAP_X);
    int rows = (SCREEN_HEIGHT - HEADER_H) / (ICON_H + GAP_Y);
    int iconsPerPage = cols * rows;
    int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage;

    if (currentPage >= totalPages) currentPage = 0;
    drawPage(currentPage);
    lastPageTime = millis();
  }
}

void drawPage(int page) {
  int cols = SCREEN_WIDTH / (ICON_W + GAP_X); // 128/(24+2) = 4 icon/hàng
  int rows = (SCREEN_HEIGHT - HEADER_H) / (ICON_H + GAP_Y); // (64-10)/(24+2) = 2 hàng
  int iconsPerPage = cols * rows; // 8 icon/trang
  int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage; // 513/8 = 65 trang
  int startIdx = page * iconsPerPage;

  display.clearDisplay();

  // Header
  display.setCursor(0, 0);
  display.printf("P%d/%d ID:%d", page + 1, totalPages, startIdx);
  display.drawLine(0, HEADER_H - 2, 127, HEADER_H - 2, SSD1306_WHITE);

  // Vẽ icon
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int idx = startIdx + r * cols + c;
      if (idx >= epd_bitmap_allArray_LEN) {
        display.display();
        return;
      }

      int x = c * (ICON_W + GAP_X);
      int y = HEADER_H + r * (ICON_H + GAP_Y);

      // Lấy bitmap từ PROGMEM
      const unsigned char* icon_ptr = (const unsigned char*)pgm_read_ptr(&epd_bitmap_allArray[idx]);

      // SSD1306 chỉ có trắng/đen
      display.drawBitmap(x, y, icon_ptr, ICON_W, ICON_H, SSD1306_WHITE);
    }
  }
  display.display();
}