
# PDU Display


![alt](/icons/data.png)![alt](/icons/setting.png) <br>
![alt](/icons/notation.png)![alt](/icons/system.png) <br>
![alt](/icons/control_left.png)![alt](/icons/control_right.png)![alt](/icons/control_down.png) <br>

First

## Структура проекта

[Шрифты](/fonts/)
[Картинки](/icons/)
[Проект ezz](/ezz/)

[Иходники](/main/)
[Компоненты](/components/)
[FAT file system](/data/)




## Переферия

```
       ESP Board                      ST7796 Panel + GT911 TOUCH
┌──────────────────────┐              ┌────────────────────┐
│                      ├─────────────►│       ST7796       │
│             GND      ├─────────────►│ GND                │
│             3V3      ├─────────────►│ VCC                │
│             PCLK     ├─────────────►│ SCL                │
│             MOSI     ├─────────────►│ MOSI               │
│             MISO     |◄─────────────┤ MISO               │
│             RST      ├─────────────►│ RES                │
│             DC       ├─────────────►│ DC                 │
│             LCD CS   ├─────────────►│ LCD CS             │
│             BK_LIGHT ├─────────────►│ BLK                │
│                      │              │     GT911          │
│             SCL      ├─────────────►│ TP SCL             │
│             SDA      ├─────────────►│ TP SDA             │
└──────────────────────┘              └────────────────────┘
```
