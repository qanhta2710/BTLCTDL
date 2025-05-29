# BTLCTDL

## Hướng dẫn Build

### Yêu cầu:
- Đã cài đặt [CMake](https://cmake.org/download/)
- Đã cài MinGW [Hướng dẫn](https://codecute.com/c/huong-dan-cai-dat-trinh-bien-dich-c-c-mingw-gcc.html) và cài đặt Make. Thêm thư mục `bin` của MinGW và thư mục có chứa `Make` vào biến môi trường `PATH` 

### Các bước build (Sử dụng Terminal Powershell):

```bash
git clone https://github.com/qanhta2710/BTLCTDL.git
cd BTLCTDL
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```
File thực thi program.exe nằm trong folder build
