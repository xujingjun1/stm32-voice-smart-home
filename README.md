# stm32-voice-smart-home

> **语音识别智能家居控制**。
> STM32F103C8T6 + 标准外设库 V3.5.0，语音识别模块指令控制 LED/RGB 灯，
> USB 虚拟串口透传调试，ADC 采集雨滴传感器。Keil MDK 工程开箱可编译，
> `release/SmartHome.hex` 为已编译固件。

**MCU**：STM32F103C8T6（72 MHz） ｜ **工程**：Keil MDK 5（`.uvprojx`） ｜ **库**：STM32F10x StdPeriph V3.5.0

---

## 一、功能与实现要点

| 模块 | 实现 |
|---|---|
| 语音指令控制 | 语音识别模块挂 **USART3**（PB10/PB11，9600bps）；**接收中断逐字节收 + 空闲中断收尾**，单字节指令帧解析 |
| LED 开关 | 3 路 LED 联动开关 |
| WS2812 RGB | GPIO + NOP **位带编码**手工凑单总线时序，高位先发 24bit（0 码/1 码不同时宽），红/绿/蓝/灭四色 |
| USB 虚拟串口 | ST USB-FS-Device 库（USB/），语音数据透传 PC 调试 |
| ADC 雨滴传感 | ADC2 通道 9 软件触发，含上电校准流程，**5 次采样均值滤波**转百分比 |
| 按键 | 消抖状态机；**长按 KEY1 进入语音固件下载模式** |
| 呼吸灯 | `delay_us` 改变 PWM 等效占空比 |

## 二、语音指令表

| 指令字节 | 动作 |
|---|---|
| `0xAA` | LED1/2/3 全开 |
| `0xAB` | LED1/2/3 全关 |
| `0xAC` | RGB 变红 (255,0,0) |
| `0xAD` | RGB 变绿 (0,255,0) |
| `0xAE` | RGB 变蓝 (0,0,255) |
| `0xAF` | RGB 熄灭 (0,0,0) |

## 三、目录结构

```
stm32-voice-smart-home/
├── STM32F103C8.uvprojx        Keil 工程
├── user/                      用户代码（main / voice / rgb / rain / led / key / delay）
├── USB/                       ST USB-FS-Device 虚拟串口
├── STM32F10x_StdPeriph_Lib_V3.5.0/   标准外设库
└── release/
    └── SmartHome.hex          预编译固件
```

## 四、编译与烧录

1. Keil MDK 5 打开 `STM32F103C8.uvprojx`，直接 Build（工程内已配好库路径）
2. 或直接烧录 `release/SmartHome.hex`（STM32CubeProgrammer / ST-Link / FlyMcu 均可）

## 五、技术点备忘（面试常问）

- **为什么 WS2812 用 NOP 手调时序**：单总线 0 码/1 码靠脉宽区分（约 0.4μs/0.8μs 级），72 MHz 下 NOP 级凑时序最直接；代价是时序对编译器优化敏感，需要 `volatile`/精确延时保护
- **接收中断 + 空闲中断怎么配合**：RXNE 中断逐字节存缓冲，IDLE 中断判定一帧结束再整帧解析——避免逐字节中断长期占用 CPU，也天然切分变长帧
- **ADC 为什么要均值滤波**：MQ/雨滴类传感器输出噪声大，单次采样不可信；5 次均值是成本最低的降噪手段

---

仅供学习与展示使用。
