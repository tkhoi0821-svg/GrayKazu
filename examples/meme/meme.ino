/*
  GrayKazu - KazuOS Meme Grid Test Demo
  Test hiển thị danh sách ảnh MÀU THẬT (RGB565) dạng lưới 50x50px.
  
  Phát triển bởi: GRAY KAZU
  Version: 1.4.1 (Mini Meme Grid - 2026)
  Màn hình: 320x240 (Rotation = 1)
*/

#include <SPI.h>
#include <TFT_eSPI.h> 
#include "GrayKazu_mini_meme.h" // Nhúng file chứa mảng 43 ảnh meme của ní

TFT_eSPI tft = TFT_eSPI();

// Khởi tạo Sprite để gom khung hình vẽ ngầm rồi đẩy lên một lần, chống chớp màn hình
TFT_eSprite clk = TFT_eSprite(&tft); 

#define ICON_W 50      // Đúng kích thước 50x50 như ní yêu cầu
#define ICON_H 50
#define GAP 10         // Khoảng cách giữa các ảnh meme
#define TEXT_H 10      // Chiều cao vùng hiển thị ID ảnh
#define HEADER_H 20    // Chiều cao thanh trạng thái trên cùng

int currentPage = 0;
uint32_t lastPageTime = 0;
const uint16_t PAGE_DELAY_MS = 3500; // 3.5 giây đổi trang một lần

const int screenWidth = 320;
const int screenHeight = 240;

void setup() {
  Serial.begin(115200);
  Serial.println("Bat dau test grid meme 50x50 cho KazuOS...");
  
  tft.init();
  tft.setRotation(1); // Khổ ngang 320x240
  tft.fillScreen(TFT_BLACK);

  // Khởi tạo bộ đệm Sprite toàn màn hình
  clk.createSprite(screenWidth, screenHeight);
  
  // Sửa lỗi lật ngược màu phim cho ảnh RGB565 trên Sprite
  clk.setSwapBytes(true); 
  clk.setTextFont(1);

  // Vẽ trang đầu tiên luôn
  drawMemePage(0);
  lastPageTime = millis();
}

void loop() {
  // Tính toán số cột và số hàng có thể chứa trên màn hình 320x240
  int cols = screenWidth / (ICON_W + GAP);                                 // 320 / 60 = 5 cột
  int rows = (screenHeight - HEADER_H) / (ICON_H + TEXT_H + GAP);          // (240 - 20) / 70 = 3 hàng
  int iconsPerPage = cols * rows;                                          // tối đa 15 meme/trang
  int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage;

  // Tự động chuyển trang sau mỗi khoảng thời gian delay
  if (millis() - lastPageTime > PAGE_DELAY_MS) {
    currentPage++;
    if (currentPage >= totalPages) currentPage = 0;
    
    drawMemePage(currentPage);
    lastPageTime = millis();
  }
}

void drawMemePage(int page) {
  int cols = screenWidth / (ICON_W + GAP);
  int rows = (screenHeight - HEADER_H) / (ICON_H + TEXT_H + GAP);
  int iconsPerPage = cols * rows;
  int totalPages = (epd_bitmap_allArray_LEN + iconsPerPage - 1) / iconsPerPage;
  int startIdx = page * iconsPerPage;

  // Xóa nền Sprite ngầm
  clk.fillSprite(TFT_BLACK);

  // Vẽ Header của KazuOS
  clk.setTextColor(TFT_MAGENTA, TFT_BLACK);
  clk.drawString("KazuOS Mini Meme v1.4.0", 8, 4, 1);
  
  // Ghi chú số trang
  clk.setTextColor(TFT_CYAN, TFT_BLACK);
  char pageStr[32];
  sprintf(pageStr, "Page %d/%d | Total: %d", page + 1, totalPages, epd_bitmap_allArray_LEN);
  clk.drawRightString(pageStr, screenWidth - 8, 4, 1);
  
  // Vẽ đường phân cách nét mảnh màu xám
  clk.drawFastHLine(0, HEADER_H - 2, screenWidth, TFT_DARKGREY);

  // Tính toán độ dôi (margin) để căn lưới nằm chính giữa màn hình theo chiều ngang
  int totalGridWidth = (cols * ICON_W) + ((cols - 1) * GAP);
  int startX = (screenWidth - totalGridWidth) / 2;

  // Vòng lặp vẽ lưới ảnh
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      int idx = startIdx + r * cols + c;
      
      // Nếu vượt quá số lượng 43 ảnh trong mảng thì ngắt vòng lặp
      if (idx >= epd_bitmap_allArray_LEN) break;

      int x = startX + c * (ICON_W + GAP);
      int y = HEADER_H + 6 + r * (ICON_H + TEXT_H + GAP);

      // Lấy con trỏ ảnh từ mảng (Mảng định nghĩa trong PROGMEM)
      const uint16_t* imageData = (const uint16_t*)pgm_read_ptr(&epd_bitmap_allArray[idx]);

      // Đẩy ảnh màu 50x50 lên Sprite ngầm bằng hàm pushImage
      clk.pushImage(x, y, ICON_W, ICON_H, imageData);

      // In số ID index của meme ngay dưới ảnh để ní dễ quản lý
      clk.setTextColor(TFT_GREEN, TFT_BLACK);
      
      // Thuật toán căn chữ nằm giữa ảnh 50px
      int textX = x + (ICON_W - clk.textWidth(String(idx))) / 2;
      clk.setCursor(textX, y + ICON_H + 2);
      clk.print(idx);
    }
  }

  // Đẩy nguyên khối đệm Sprite lên màn hình thật 320x240
  clk.pushSprite(0, 0);
}