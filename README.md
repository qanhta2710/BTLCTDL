# BTLCTDL

## Hướng dẫn Build

### Yêu cầu:
- Đã cài đặt [CMake](https://cmake.org/download/)
- Đã cài [MinGW](http://www.mingw.org/) hoặc cài đặt bằng cách nào đó có Make và thêm thư mục `bin` của MinGW và thư mục có chứa Make vào biến môi trường `PATH` 

### Các bước build:

```bash
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
