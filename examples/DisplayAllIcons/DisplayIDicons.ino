/*
  KazuOS_StatusBar_Demo.ino
  Ví dụ nâng cao: Thiết kế giao diện (GFX) Thanh trạng thái hệ thống cho KazuOS
  Sử dụng linh hoạt bộ icon từ thư viện GrayKazu phối hợp với các hàm vẽ của TFT_eSPI.
  
  Created by GRAY KAZU
  Version 1.0.0 (2026)
*/

#include <SPI.h>
#include <TFT_eSPI.h> 
#include <GrayKazu.h> // Triệu hồi bộ icon chính chủ

TFT_eSPI tft = TFT_eSPI();

// Định nghĩa các ID Icon dựa theo thứ tự trong mảng tổng epd_bitmap_allArray
#define ID_ALARM    0
#define ID_BATTERY  3  // Giả định loại pin vạch 2
#define ID_MIC      22
#define ID_WIFI     29 // Giả định icon Wifi căng vạch

void setup() {
  tft.init();
  tft.setRotation(1); // Xoay ngang màn hình
  tft.fillScreen(TFT_BLACK);
  
  // Vẽ nền cho toàn bộ màn hình OS (Ví dụ màn hình chính màu xám đậm hoặc đen)
  tft.fillRect(0, 0, 240, 320, TFT_BLACK);
  
  Serial.begin(115200);
}

void loop() {
  // Chạy cập nhật giao diện liên tục
  drawKazuStatusBar("12:45", true, 85); // Giả lập: Giờ là 12:45, có bật Báo thức, Pin 85%
  
  delay(1000); // Cập nhật GFX mỗi giây
}

/* =========================================================================
  HÀM GFX: VẼ THANH TRẠNG THÁI CHUYÊN NGHIỆP (STATUS BAR)
  =========================================================================
  - timeStr: Chuỗi hiển thị đồng hồ (VD: "12:45")
  - alarmOn: Trạng thái báo thức (true/false)
  - batteryPercent: Phần trăm pin thực tế để tự nhảy icon pin tương ứng
*/
void drawKazuStatusBar(String timeStr, bool alarmOn, int batteryPercent) {
  // 1. Vẽ thanh nền Status Bar (Rộng 240px, Cao 30px, Màu nền xám tối thanh lịch)
  // Giúp tách biệt thanh trạng thái với không gian ứng dụng bên dưới
  tft.fillRect(0, 0, 240, 30, tft.color565(30, 30, 30)); 
  tft.drawFastHLine(0, 29, 240, tft.color565(80, 80, 80)); // Đường kẻ chỉ mảnh bên dưới
  
  // 2. VẼ BÊN TRÁI: Đồng hồ hiển thị thời gian
  tft.setTextColor(TFT_WHITE, tft.color565(30, 30, 30));
  tft.setTextSize(1);
  // Định vị chữ ở tọa độ (X=8, Y=8)
  tft.drawString(timeStr, 8, 8, 2); // Dùng font số 2 của TFT_eSPI nhìn rất gọn
  
  // 3. VẼ BÊN PHẢI: Các Icon hệ thống (Dàn trận từ phải qua trái)
  int current_x = 240 - 24 - 6; // Bắt đầu từ rìa phải màn hình trừ đi kích thước icon và lề
  
  // Lấy Icon Pin dựa theo % dung lượng thực tế
  int target_battery_id = ID_BATTERY;
  if (batteryPercent < 20) {
    target_battery_id = 5; // ID icon battery_alert
  } else if (batteryPercent < 50) {
    target_battery_id = 3; // ID icon battery_android_2
  } else {
    target_battery_id = 4; // ID icon battery_android_4 (Pin đầy)
  }
  
  // Vẽ Icon Pin
  drawIcon(current_x, 3, target_battery_id);
  
  // Dịch sang trái 28px để vẽ icon tiếp theo: Icon Wifi
  current_x -= 28;
  drawIcon(current_x, 3, ID_WIFI);
  
  // Nếu có bật báo thức thì dịch tiếp sang trái vẽ Icon Báo thức
  if (alarmOn) {
    current_x -= 28;
    drawIcon(current_x, 3, ID_ALARM);
  }
}

// Hàm bổ trợ gọi nhanh icon từ bộ nhớ Flash ra vẽ theo tọa độ
void drawIcon(int x, int y, int icon_id) {
  if (icon_id >= 0 && icon_id < epd_bitmap_allArray_LEN) {
    const unsigned char* icon_ptr = (const unsigned char*)pgm_read_ptr(&(epd_bitmap_allArray[icon_id]));
    // Vẽ đè lên thanh trạng thái với màu icon là TRẮNG và nền là màu xám tối của Status Bar
    tft.drawBitmap(x, y, icon_ptr, 24, 24, TFT_WHITE, tft.color565(30, 30, 30));
  }
}