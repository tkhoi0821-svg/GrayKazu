/*
  GrayKazu - KazuOS Image Test Demo
  Test hiển thị danh sách ảnh MÀU THẬT (RGB565) - Chuẩn 320x240 px.
  
  Phát triển bởi GRAY KAZU
  Version: 1.4.1 (Color Edition - 2026)
*/

#include <SPI.h>
#include <TFT_eSPI.h> // Thư viện đồ họa màn hình màu
#include "GrayKazu_pnd.h" 

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Serial.println("Bat dau test anh 320x240 cho KazuOS...");
  
  tft.init();
  
  // Set màn hình nằm ngang (Rotation 1 hoặc 3) để khớp với khổ ảnh 320x240
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);

  // Bật hoán đổi byte cho ảnh màu 16-bit RGB565
  // Nếu nạp xong màu bị ngược (lật màu phim), đổi true thành false
  tft.setSwapBytes(true); 

  tft.setTextColor(TFT_MAGENTA, TFT_BLACK);
  tft.drawString("KazuOS 320x240 Image Test", 10, 10, 2);
  delay(1500);
}

void loop() {
  // Lặp qua tất cả các ảnh dựa theo epd_bitmap_allArray_LEN (bằng 5) trong file .h
  for (int i = 0; i < epd_bitmap_allArray_LEN; i++) {
    
    Serial.print("Dang render anh so: ");
    Serial.println(i + 1);

    tft.fillScreen(TFT_BLACK);

    // Lấy trực tiếp con trỏ ảnh từ mảng (không qua pgm_read_ptr)
    const uint16_t* imageData = epd_bitmap_allArray[i];
    
    // Đẩy ảnh lên toàn màn hình (320x240)
    // Dùng đúng tọa độ (0,0) và kích thước ICON_W (240), ICON_H (320) nhưng đảo lại theo chiều ngang
    // Hoặc điền thẳng số 320, 240 cho chắc chắn
    tft.pushImage(0, 0, 320, 240, imageData);

    // Chờ 3 giây rồi chuyển sang ảnh tiếp theo
    delay(3000); 
  }
}