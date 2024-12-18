cmake_minimum_required(VERSION 3.22)

project(stm32cubemx)
add_library(stm32cubemx INTERFACE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

target_compile_definitions(stm32cubemx INTERFACE 
	USE_HAL_DRIVER 
	STM32G474xx
    $<$<CONFIG:Debug>:DEBUG>
)

target_include_directories(stm32cubemx INTERFACE
    ../../Core/Inc
    ../../USB_Device/App
    ../../USB_Device/Target
    ../../Drivers/STM32G4xx_HAL_Driver/Inc
    ../../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy
    ../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc
    ../../Drivers/CMSIS/Device/ST/STM32G4xx/Include
    ../../Drivers/CMSIS/Include
)

target_sources(stm32cubemx INTERFACE
    ../../Core/Src/main.c
    ../../Core/Src/rc522.c
    ../../Core/Src/FatFs/diskio_ram_glue.c
    ../../Core/Src/FatFs/ff_glue.c
    ../../Core/Src/FatFs/diskio.c
    ../../Core/Src/FatFs/ff.c
    ../../Core/Src/FatFs/ffsystem.c
    ../../Core/Src/FatFs/ffunicode.c
    ../../Core/Src/gpio.c
    ../../Core/Src/usart.c
    ../../Core/Src/spi.c
    ../../Core/Src/stm32g4xx_it.c
    ../../Core/Src/stm32g4xx_hal_msp.c
    ../../USB_Device/Target/usbd_conf.c
    ../../USB_Device/App/usb_device.c
    ../../USB_Device/App/usbd_desc.c
    ../../USB_Device/App/usbd_storage_if.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pcd_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_ll_usb.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_rcc_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_flash_ramfunc.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_gpio.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_exti.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_dma_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_cortex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_uart_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_spi_ex.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim.c
    ../../Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_tim_ex.c
    ../../Core/Src/system_stm32g4xx.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_bot.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_data.c
    ../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Src/usbd_msc_scsi.c
    ../../Core/Src/sysmem.c
    ../../Core/Src/syscalls.c
    ../../startup_stm32g474xx.s
)

target_link_directories(stm32cubemx INTERFACE
)

target_link_libraries(stm32cubemx INTERFACE
)

# Validate that STM32CubeMX code is compatible with C standard
if(CMAKE_C_STANDARD LESS 11)
    message(ERROR "Generated code requires C11 or higher")
endif()


