/*
  GrayKazu Library - IconGridTest v1.4.0
  Hiển thị toàn bộ 513 bitmap trong epd_bitmap_allArray
  Tác giả: graykazu
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <GrayKazu.h>

TFT_eSPI tft = TFT_eSPI();

// Paste nguyên mảng 513 icon của ní vào đây
extern const int epd_bitmap_allArray_LEN;
extern const unsigned char* epd_bitmap_allArray[513];

#define ICON_W 24
#define ICON_H 24
#define GAP 3
#define TEXT_H 8
#define HEADER_H 16

int currentPage = 0;
uint32_t lastPageTime = 0;
const uint16_t PAGE_DELAY_MS = 2500; // 2.5s đổi trang

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1); // 320x240 thì để ngang cho được nhiều
  tft.fillScreen(TFT_BLACK);
  tft.setTextFont(1);
  drawPage(0);
  lastPageTime = millis();
}

void loop() {
  if (millis() - lastPageTime > PAGE_DELAY_MS) {
    currentPage++;
    int cols = tft.width() / (ICON_W + GAP);
    int rows = (tft.height() - HEADER_H) / (ICON_H + TEXT_H + GAP);
    int iconsPerPage = cols * rows;
    int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage;

    if (currentPage >= totalPages) currentPage = 0;
    drawPage(currentPage);
    lastPageTime = millis();
  }
}

void drawPage(int page) {
  int cols = tft.width() / (ICON_W + GAP);
  int rows = (tft.height() - HEADER_H) / (ICON_H + TEXT_H + GAP);
  int iconsPerPage = cols * rows;
  int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage;
  int startIdx = page * iconsPerPage;

  tft.fillScreen(TFT_BLACK);

  // Header
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setCursor(2, 2);
  tft.printf("GrayKazu v1.3.9 | Page %d/%d | Icons: %d", page + 1, totalPages, epd_bitmap_allArray_LEN);
  tft.drawFastHLine(0, HEADER_H - 2, tft.width(), TFT_DARKGREY);

  // Vẽ icon
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int idx = startIdx + r * cols + c;
      if (idx >= epd_bitmap_allArray_LEN) return;

      int x = 2 + c * (ICON_W + GAP);
      int y = HEADER_H + r * (ICON_H + TEXT_H + GAP);

      // Lấy bitmap từ PROGMEM
      const unsigned char* icon_ptr = (const unsigned char*)pgm_read_ptr(&epd_bitmap_allArray[idx]);

      // Vẽ icon trắng, nền đen. Đổi TFT_GREEN nếu muốn test màu
      tft.drawBitmap(x, y, icon_ptr, ICON_W, ICON_H, TFT_WHITE, TFT_BLACK);

      // In ID nhỏ bên dưới
      tft.setTextColor(TFT_ORANGE, TFT_BLACK);
      tft.setCursor(x, y + ICON_H + 1);
      tft.print(idx);
    }
  }
}