/*
  GrayKazu Library - KazuOS Color Icon Test Demo
  Test hiển thị danh sách 7 icon MÀU THẬT (RGB565) - Chuẩn 24x24 px.
  
  Version 1.3.0 (Color Edition - 2026)
  Phát triển bởi GRAY KAZU
*/

#include <SPI.h>
#include <TFT_eSPI.h>       // Thư viện đồ họa màn hình màu
#include <GrayKazu_Color.h> // Gọi file header màu (Đã có sẵn mảng tổng bên trong)

TFT_eSPI tft = TFT_eSPI();

// Sử dụng luôn kích thước ICON_W và ICON_H đã được định nghĩa trong thư viện
// Không cần khai báo lại epd_bitmap_allArray_LEN và epd_bitmap_allArray[7] ở đây nữa!

void setup() {
  Serial.begin(115200);
  
  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // SỬA LỖI ĐẢO MÀU: Bật tính năng hoán đổi byte cho ảnh 16-bit màu
  tft.setSwapBytes(true); 

  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.drawString("KazuOS Color UI System", 10, 10, 2);
  delay(1500);
}

void loop() {
  tft.fillScreen(TFT_BLACK);
  
  int x = 20;
  int y = 60;
  int padding = 15; 

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("Hien thi danh sach Icon Mau:", 10, 10, 2);

  for (int i = 0; i < epd_bitmap_allArray_LEN; i++) {
    // Đọc chính xác con trỏ từ mảng pgm
    uint16_t* iconColorData = (uint16_t*)pgm_read_ptr(&(epd_bitmap_allArray[i]));
    
    // Đẩy ảnh lên màn hình
    tft.pushImage(x, y, ICON_W, ICON_H, iconColorData);
    
    x += ICON_W + padding;
    if (x > tft.width() - ICON_W) {
      x = 20;
      y += ICON_H + padding;
    }
  }

  delay(5000); 
}