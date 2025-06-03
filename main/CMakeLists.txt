file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c"  "ui/*.cpp")

idf_component_register(SRCS ${SRC_UI} "main.cpp"
            "DataList.cpp"
            "ModbusControls.cpp"
            "Display.cpp"
            "ModbusSlave/ModbusSlave.cpp"
                       INCLUDE_DIRS "." "ui")

set(image ../data)
#fatfs_create_rawflash_image(ffat ${image})
fatfs_create_spiflash_image(ffat ${image} FLASH_IN_PROJECT)