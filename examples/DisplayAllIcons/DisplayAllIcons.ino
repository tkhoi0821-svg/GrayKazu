/*
  GrayKazu Library - KazuOS_StatusBar
  Demo thiết kế thanh trạng thái hệ thống cập nhật động bằng Icon ID.
  
  Version 1.2.0 (2026)
  Phát triển bởi GRAY KAZU (KazuOS)
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <GrayKazu.h>

TFT_eSPI tft = TFT_eSPI();

// Định nghĩa vị trí ID cụ thể của một số Icon mẫu trong mảng tổng của ní
#define ICON_ID_BLUETOOTH 36
#define ICON_ID_WIFI_FULL 181
#define ICON_ID_BATTERY_FULL 31
#define ICON_ID_BATTERY_LOW 29
#define ICON_ID_ALARM_ON 10

unsigned long lastUpdate = 0;
bool isBatteryLow = false;

void drawIconByID(int x, int y, int icon_id, uint16_t color) {
  if (icon_id >= 0 && icon_id < epd_bitmap_allArray_LEN) {
    const unsigned char* icon_ptr = (const unsigned char*)pgm_read_ptr(&(epd_bitmap_allArray[icon_id]));
    tft.drawBitmap(x, y, icon_ptr, 24, 24, color, TFT_BLACK);
  }
}

void drawStatusBar() {
  // Vẽ nền thanh trạng thái (Dày 30px ở trên cùng màn hình)
  tft.fillRect(0, 0, tft.width(), 30, TFT_BLACK);
  tft.drawFastHLine(0, 30, tft.width(), TFT_DARKGREY); // Đường kẻ phân cách

  // 1. Vẽ Icon Sóng Wifi (Bên trái)
  drawIconByID(5, 3, ICON_ID_WIFI_FULL, TFT_CYAN);

  // 2. Vẽ Icon Bluetooth & Báo thức (Giữa)
  drawIconByID(40, 3, ICON_ID_BLUETOOTH, TFT_BLUE);
  drawIconByID(70, 3, ICON_ID_ALARM_ON, TFT_ORANGE);

  // 3. Vẽ Icon Trạng thái Pin động (Bên phải màn hình)
  int batteryX = tft.width() - 30;
  if (isBatteryLow) {
    drawIconByID(batteryX, 3, ICON_ID_BATTERY_LOW, TFT_RED); // Pin yếu màu đỏ
  } else {
    drawIconByID(batteryX, 3, ICON_ID_BATTERY_FULL, TFT_GREEN); // Pin đầy màu xanh
  }

  // 4. In đồng hồ thời gian giả định
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("13:19", tft.width() / 2 - 15, 8, 2);
}

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  // Vẽ giao diện Status Bar lần đầu
  drawStatusBar();
}

void loop() {
  // Giả lập cứ sau 4 giây trạng thái pin thay đổi để test giao diện cập nhật động
  if (millis() - lastUpdate > 4000) {
    isBatteryLow = !isBatteryLow;
    drawStatusBar(); // Cập nhật lại thanh trạng thái
    lastUpdate = millis();
  }
}