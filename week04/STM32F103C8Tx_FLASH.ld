/* Entry Point */
ENTRY(Reset_Handler)

/* Vị trí đỉnh của Stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Cấu hình kích thước bộ nhớ cho chip STM32F103C8T6 */
MEMORY
{
  RAM (xrw)      : ORIGIN = 0x20000000, LENGTH = 20K
  FLASH (rx)     : ORIGIN = 0x08000000, LENGTH = 64K
}

/* Phân bổ các phần vùng bộ nhớ (Sections) */
SECTIONS
{
  /* Bảng vector ngắt */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))
    . = ALIGN(4);
  } >FLASH

  /* Vùng chứa mã lệnh (Code) */
  .text :
  {
    . = ALIGN(4);
    *(.text)
    *(.text*)
    . = ALIGN(4);
    _etext = .;
  } >FLASH

  /* Biến _sidata lưu địa chỉ bắt đầu của vùng .data trong FLASH */
  _sidata = LOADADDR(.data);

  /* Vùng chứa các biến toàn cục được khởi tạo giá trị khác 0 */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* Biến _sdata báo hiệu điểm đầu vùng .data trong RAM */
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;        /* Biến _edata báo hiệu điểm cuối vùng .data trong RAM */
  } >RAM AT> FLASH

  /* Vùng chứa các biến toàn cục chưa được khởi tạo (mặc định bằng 0) */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;         
    __bss_start__ = _sbss; /* Biến __bss_start__ dùng cho thư viện C chuẩn */
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;   /* Biến __bss_end__ dùng cho thư viện C chuẩn */
  } >RAM

  /* Các biến cung cấp cho thư viện cấp phát bộ nhớ động (malloc) */
  PROVIDE ( end = _ebss );
  PROVIDE ( _end = _ebss );
}