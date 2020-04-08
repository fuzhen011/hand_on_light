let g:ale_c_gcc_executable = 'arm-none-eabi-gcc'
let g:ale_cpp_gcc_executable = 'arm-none-eabi-gcc'
let g:ale_c_gcc_options = '-g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 -DENABLE_LOGGING=1 -DMESH_LIB_NATIVE=1 -DNVM3_DEFAULT_NVM_SIZE=24576 -D__HEAP_SIZE=0x1700 -D__STACK_SIZE=0x1000 -DHAL_CONFIG=1 -DNVM3_DEFAULT_MAX_OBJECT_SIZE=512 -DEFR32MG12P332F1024GL125=1 -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/hardware/kit/EFR32MG12_BRD4166A/config -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/Device/SiliconLabs/EFR32MG12P/Include -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/dmadrv/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/hardware/kit/common/drivers -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/Device/SiliconLabs/EFR32MG12P/Source -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emlib/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/hardware/kit/common/bsp/thunderboard -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/bt_mesh/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/gpiointerrupt/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/CMSIS/Include -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/bt_mesh/inc/common -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/Device/SiliconLabs/EFR32MG12P/Source/GCC -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/ble_stack/inc/soc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emlib/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/hardware/kit/common/halconfig -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/bt_mesh/inc/soc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/gpiointerrupt/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/protocol/ble -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/bt_mesh/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/halconfig/inc/hal-config -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/nvm3/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/chip/efr32/efr32xg1x -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/hardware/kit/common/bsp -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/common -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/protocol/bluetooth/ble_stack/src/soc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/dmadrv/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/uartdrv/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/service/sleeptimer/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/common/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/sleep/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/nvm3/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/service/sleeptimer/src -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/plugin/coexistence/hal/efr32 -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/sleep/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/emdrv/common/inc -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/plugin/coexistence/common -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/service/sleeptimer/config -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/protocol/ieee802154 -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/bootloader/api -I$HOME/SimplicityStudio/v4_workspace/hands_on_light -I$HOME/SimplicityStudio/v4_workspace/hands_on_light/platform/radio/rail_lib/plugin -Os -fno-builtin -Wall -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp'
