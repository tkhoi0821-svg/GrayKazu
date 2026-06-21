# 🚀 GrayKazu Resource Library v1.4.1

Hệ sinh thái lưu trữ asset dữ liệu, ma trận hình ảnh RGB565 và bộ điều khiển Meme Center dành riêng cho dự án **KazuOS**. Tối ưu hóa dung lượng cao cấu hình cho chip điều khiển (ESP32-S3, RP2040-Zero, STM32) kết hợp với thư viện đồ họa `TFT_eSPI`.

---

## 📂 Cấu trúc tài nguyên & Từ khóa (Keywords)

### 1. Thư mục `src/` (Dữ liệu nguồn mảng code)
* **`GrayKazu_mini_meme.h`**: Chứa siêu mảng **78 ảnh mini-meme (50x50px)** hệ màu RGB565.
* **`GrayKazu_pnd.h`  ** chứa các ảnh có kích thước lớn 320x240 .
 `GrayKazu_meme.h`**: chứa các meme nặng hơn với kích thước 250x250 pixel.
* **`GrayKazu_Color.h`**: chứa các icon màu 25x25.

### 2. các tệp ảnh 
* Chứa các linh vật UI phẳng, icon , Moon, Shark, Cá voi (`orca`)... phục vụ cho thanh tác vụ và màn hình chính


### 4. Thư mục `examples/` (Các bản Code Test mẫu)
* `DisplayAllIcons`: Code test lưới quét toàn bộ icon hệ thống.
* `meme` / `memez`: 2 loại test dành cho các phần cứng yếu/mạnh
* `pndTest`: test các ảnh kích thước lớn 320x240

---

---


## 🛠️ Hướng dẫn tích hợp nhanh vào Code chính
```cpp
#include <TFT_eSPI.h>
#include <GrayKazu_mini_meme.h> // Gọi thư viện tài nguyên

// Truy xuất tổng số lượng ảnh trong siêu mảng công bố tại phiên bản 1.4.1
int totalMeme = epd_bitmap_allArray_LEN;
 --- end ---