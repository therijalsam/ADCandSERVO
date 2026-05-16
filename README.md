# XADC Servo Control with 7-Segment Display

This project reads analog input data from the XADC module, displays the ADC value on a 4-digit 7-segment display, and uses the ADC reading to control a servo motor through TTC0 timer PWM output.

The program is written in C using memory-mapped I/O registers on a Zynq-based embedded system.

---

# Features

- Reads analog sensor input using XADC
- Displays ADC value on a 4-digit 7-segment display
- Controls servo motor position based on ADC value
- Uses TTC0 timer registers for PWM signal generation
- Uses direct register-level programming
- Runs continuously in an embedded loop

---

# Hardware Used

- Zynq-based development board
- XADC analog input
- 4-digit 7-segment display
- Servo motor
- TTC0 timer peripheral

---

# Technologies Used

- C
- Embedded C
- Memory-Mapped I/O
- XADC
- TTC Timer
- PWM
- 7-Segment Display
- Register-Level Programming

---

# How It Works

The program reads an analog value from the XADC data register.

```c
adc_val = (XADC_DATA >> 4) & 0xFF80;
```

The ADC value is displayed on the 7-segment display using the `Disp_BCD()` function.

```c
Disp_BCD(adc_val);
```

The same ADC value is mapped to a servo PWM match value.

```c
servo_val = 50 + ((adc_val * (275 - 50)) / 4095);
```

This converts the ADC reading into a servo control range between `50` and `275`.

The servo position is updated by writing the calculated value to the TTC0 match register.

```c
TTC0_Match_0 = servo_val;
```

---

# Register Map

| Peripheral | Register | Address |
|---|---|---|
| 7-Segment Control | `SEG_CTL` | `0x43C10000` |
| 7-Segment Data | `SEG_DATA` | `0x43C10004` |
| XADC Data | `XADC_DATA` | `0x43C5020C` |
| XADC Config | `XADC_CFG` | `0x43C50300` |
| TTC0 Clock Control | `TTC0_ClkCntl_0` | `0xF8001000` |
| TTC0 Operation Mode | `TTC0_OpMode_0` | `0xF800100C` |
| TTC0 Interval | `TTC0_Interval_0` | `0xF8001024` |
| TTC0 Match | `TTC0_Match_0` | `0xF8001030` |

---

# Code Overview

## `Disp_BCD()`

Converts a numeric value into BCD-style digits and sends it to the 7-segment display.

```c
void Disp_BCD(uint16_t value)
```

## `main()`

Initializes the TTC0 timer, reads XADC data, displays the ADC value, maps the value to a servo PWM range, and updates the servo position.

---

# Main Control Loop

```c
while (1)
{
    XADC_CFG = 0x3803;

    adc_val = (XADC_DATA >> 4) & 0xFF80;

    Disp_BCD(adc_val);

    servo_val = 50 + ((adc_val * (275 - 50)) / 4095);

    TTC0_Match_0 = servo_val;

    usleep(10000);
}
```

---

# Expected Output

- The 7-segment display shows the current ADC reading.
- The servo motor changes position as the analog input changes.
- The system updates every 10 milliseconds.

---

# Project Purpose

This project demonstrates how analog sensor input can be used to control physical hardware in real time. It connects ADC input, digital display output, and PWM-based servo control using low-level embedded C programming.

---

# Possible Improvements

- Add comments for each TTC0 configuration value
- Calibrate the ADC-to-servo mapping range
- Add limit checking for servo values
- Display voltage instead of raw ADC value
- Add UART debugging output
- Use named constants for servo minimum and maximum values

---

