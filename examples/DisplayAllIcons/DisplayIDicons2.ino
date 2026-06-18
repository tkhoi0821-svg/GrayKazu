/*
  GrayKazu Library - IconAnimateDemo
  Tạo hiệu ứng hoạt họa (Animation) tăng giảm vạch sóng Wifi và Pin.
  
  Version 1.2.0 (2026)
  Phát triển bởi GRAY KAZU (KazuOS)
*/

#include <SPI.h>
#include <TFT_eSPI.h>
#include <GrayKazu.h>

TFT_eSPI tft = TFT_eSPI();

// Gom các ID Wifi tăng dần vào một mảng nhỏ để làm hiệu ứng chạy vạch
int wifiAnimFrames[] = {180, 182, 181}; // Thay đổi tương ứng với ID wifi_1_bar, wifi_2_bar, wifi_full trong file của ní
int currentFrame = 0;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.drawString("Testing UI Animation...", 20, 20, 2);
}

void loop() {
  // Lấy con trỏ của khung hình Wifi hiện tại
  int iconID = wifiAnimFrames[currentFrame];
  const unsigned char* icon_ptr = (const unsigned char*)pgm_read_ptr(&(epd_bitmap_allArray[iconID]));

  // Vẽ icon phóng to hoặc đặt ở trung tâm màn hình làm hiệu ứng kết nối
  tft.drawString("Connecting Wifi...", 20, 60, 2);
  tft.drawBitmap(60, 90, icon_ptr, 24, 24, TFT_GREEN, TFT_BLACK);

  // Chuyển sang khung hình tiếp theo
  currentFrame++;
  if (currentFrame >= 3) {
    currentFrame = 0; // Quay lại vạch 1
  }

  delay(6000); // Cứ 600ms đổi vạch một lần nhìn cho mượt
}