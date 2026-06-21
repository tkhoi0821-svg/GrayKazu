/*
  GrayKazu - KazuOS Big Meme Test Demo
  Test hiển thị danh sách ảnh MÀU THẬT (RGB565) - Kích thước lớn 250x250 px.
  
  Phát triển bởi: GRAY KAZU
  Version: 1.4.1 (Big Meme Edition - 2026)
  Màn hình: 320x240 (Rotation = 1)
*/

#include <SPI.h>
#include <TFT_eSPI.h> 
#include "GrayKazu_meme.h" // Nhúng file chứa mảng ảnh 250x250 của ní

TFT_eSPI tft = TFT_eSPI();

// Khởi tạo Sprite để vẽ ngầm, chống giật xé hình khi load ảnh lớn
TFT_eSprite clk = TFT_eSprite(&tft); 

#define IMG_W 250      // Kích thước ảnh 250x250 như ní yêu cầu
#define IMG_H 250
const uint16_t PAGE_DELAY_MS = 3000; // 3 giây chuyển meme một lần

const int screenWidth = 320;
const int screenHeight = 240;

int currentMeme = 0;
uint32_t lastMemeTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Bat dau test meme 250x250 cho KazuOS...");
  
  tft.init();
  tft.setRotation(1); // Khổ ngang 320x240
  tft.fillScreen(TFT_BLACK);

  // Tạo bộ đệm Sprite bằng đúng kích thước màn hình thật
  clk.createSprite(screenWidth, screenHeight);
  
  // Sửa lỗi lật ngược màu phim cho ảnh RGB565
  clk.setSwapBytes(true); 
  clk.setTextFont(1);

  // Render luôn tấm đầu tiên
  drawBigMeme(0);
  lastMemeTime = millis();
}

void loop() {
  // Tự động chuyển ảnh tiếp theo sau khi hết delay
  if (millis() - lastMemeTime > PAGE_DELAY_MS) {
    currentMeme++;
    
    // epd_bitmap_allArray_LEN lấy từ file GrayKazu_meme.h của ní
    if (currentMeme >= epd_bitmap_allArray_LEN) currentMeme = 0;
    
    drawBigMeme(currentMeme);
    lastMemeTime = millis();
  }
}

void drawBigMeme(int idx) {
  // 1. Xóa nền toàn màn hình trên bộ đệm ngầm
  clk.fillSprite(TFT_BLACK);

  // 2. Tính toán tọa độ để ảnh 250x250 nằm CHÍNH GIỮA màn hình 320x240
  // Vì chiều cao ảnh (250) lớn hơn chiều cao màn hình (240) một chút, 
  // ảnh sẽ bị ép dịch lên y = -5 để tận dụng tối đa không gian hiển thị (chỉ mất 5px viền trên/dưới không đáng kể).
  int posX = (screenWidth - IMG_W) / 2;  // (320 - 250) / 2 = 35 px (Căn giữa chiều ngang)
  int posY = (screenHeight - IMG_H) / 2; // (240 - 250) / 2 = -5 px

  // 3. Lấy con trỏ ảnh từ PROGMEM
  const uint16_t* imageData = (const uint16_t*)pgm_read_ptr(&epd_bitmap_allArray[idx]);

  // 4. Đẩy ảnh lên Sprite
  clk.pushImage(posX, posY, IMG_W, IMG_H, imageData);

  // 5. Trang trí thêm giao diện (UI) KazuOS ở vùng khoảng trống bên trái/phải ảnh (Rộng 35px mỗi bên)
  // Vẽ chỉ số ID bên góc trái
  clk.setTextColor(TFT_MAGENTA, TFT_BLACK);
  clk.drawString("KazuOS", 2, 10, 1);
  clk.setTextColor(TFT_GREEN, TFT_BLACK);
  clk.setCursor(2, 25);
  clk.printf("#%02d", idx);

  // Vẽ số trang tổng quát bên góc phải
  clk.setTextColor(TFT_CYAN, TFT_BLACK);
  char infoStr[16];
  sprintf(infoStr, "%d/%d", idx + 1, epd_bitmap_allArray_LEN);
  clk.drawRightString(infoStr, screenWidth - 2, 10, 1);

  // 6. Đẩy nguyên khung hình hoàn chỉnh lên màn hình thật
  clk.pushSprite(0, 0);
  
  Serial.print("Da load xong meme index: ");
  Serial.println(idx);
}