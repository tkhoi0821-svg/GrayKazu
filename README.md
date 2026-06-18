# GrayKazu Library v1.2.0

🎨 **Bộ thư viện Icon 1-bit đơn sắc (Monochrome) tối ưu bộ nhớ dành cho hệ điều hành KazuOS và các dự án nhúng sử dụng màn hình SPI.**

Thư viện này cung cấp sẵn **184 icon hệ thống tiêu chuẩn** (Pin, Wifi, Bluetooth, Báo thức, Cài đặt,...) được đóng gói sẵn dưới dạng mảng dữ liệu đặt trong bộ nhớ Flash (`PROGMEM`), giúp tiết kiệm RAM tối đa cho vi điều khiển (ESP32, STM32, RP2040, Arduino...).

---

## 🚀 Tính năng nổi bật

* **Tối ưu hóa bộ nhớ:** Icon định dạng 1-bit đơn sắc siêu nhẹ, kích thước chuẩn hệ thống `24x24 pixel`.
* **Quản lý thông minh:** Hỗ trợ mảng tổng quản lý `epd_bitmap_allArray` giúp gọi icon động qua số thứ tự (ID) cực kỳ tiện lợi khi làm menu/UI.
* **Tương thích hoàn hảo:** Hoạt động mượt mà với thư viện đồ họa quốc dân `TFT_eSPI` (sử dụng hàm `tft.drawBitmap`).
* **Đổi màu linh hoạt:** Dễ dàng tùy biến màu sắc hiển thị của icon và màu nền trực tiếp trong code.
# demo bản color GrayKazu-color.h
---

## 📁 Cấu trúc thư viện

```text
GrayKazu/
├── src/
│   └── GrayKazu-color.h
|    └──GrayKazu.h          # File chứa 31 mảng dữ liệu icon PROGMEM
├── examples/
│   ├── DisplayAllIcons     # Code mẫu quét và hiển thị toàn bộ icon
│   └── ...
├── library.properties      # Cấu hình thông tin thư viện cho Arduino IDE
├── keywords.txt            # Định dạng highlight đổi màu từ khóa trong IDE
└── README.md               # Hướng dẫn sử dụng này
/*
  ...
  Version 1.2.0 (2026)
*/