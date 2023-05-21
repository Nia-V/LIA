#include "master.h"


#define OUTPUT 0x1
#define INPUT 0x0

static void turnOffPWM(uint8_t timer) {
  switch (timer) {
#if defined(TCCR1A) && defined(COM1A1)
    case TIMER1A: cbi(TCCR1A, COM1A1); break;
#endif
#if defined(TCCR1A) && defined(COM1B1)
    case TIMER1B: cbi(TCCR1A, COM1B1); break;
#endif
#if defined(TCCR1A) && defined(COM1C1)
    case TIMER1C: cbi(TCCR1A, COM1C1); break;
#endif

#if defined(TCCR2) && defined(COM21)
    case TIMER2: cbi(TCCR2, COM21); break;
#endif

#if defined(TCCR0A) && defined(COM0A1)
    case TIMER0A: cbi(TCCR0A, COM0A1); break;
#endif

#if defined(TCCR0A) && defined(COM0B1)
    case TIMER0B: cbi(TCCR0A, COM0B1); break;
#endif
#if defined(TCCR2A) && defined(COM2A1)
    case TIMER2A: cbi(TCCR2A, COM2A1); break;
#endif
#if defined(TCCR2A) && defined(COM2B1)
    case TIMER2B: cbi(TCCR2A, COM2B1); break;
#endif

#if defined(TCCR3A) && defined(COM3A1)
    case TIMER3A: cbi(TCCR3A, COM3A1); break;
#endif
#if defined(TCCR3A) && defined(COM3B1)
    case TIMER3B: cbi(TCCR3A, COM3B1); break;
#endif
#if defined(TCCR3A) && defined(COM3C1)
    case TIMER3C: cbi(TCCR3A, COM3C1); break;
#endif

#if defined(TCCR4A) && defined(COM4A1)
    case TIMER4A: cbi(TCCR4A, COM4A1); break;
#endif
#if defined(TCCR4A) && defined(COM4B1)
    case TIMER4B: cbi(TCCR4A, COM4B1); break;
#endif
#if defined(TCCR4A) && defined(COM4C1)
    case TIMER4C: cbi(TCCR4A, COM4C1); break;
#endif
#if defined(TCCR4C) && defined(COM4D1)
    case TIMER4D: cbi(TCCR4C, COM4D1); break;
#endif

#if defined(TCCR5A)
    case TIMER5A: cbi(TCCR5A, COM5A1); break;
    case TIMER5B: cbi(TCCR5A, COM5B1); break;
    case TIMER5C: cbi(TCCR5A, COM5C1); break;
#endif
  }
}
void digitalWrite(int pin, bool value) {
  if (pin > 19) {
    Wire.beginTransmission(0x08);  // informs the bus that we will be sending data to slave device 8 (0x08)
    Wire.write(1);
    Wire.write(pin);
    Wire.write(value);  // send value_pot
    Wire.endTransmission();
  } else if (pin <= 19) {
    uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;

    if (port == NOT_A_PIN) return;

    // If the pin that support PWM output, we need to turn it off
    // before doing a digital write.
    if (timer != NOT_ON_TIMER) turnOffPWM(timer);

    out = portOutputRegister(port);

    uint8_t oldSREG = SREG;
    cli();

    if (value == LOW) {
      *out &= ~bit;
    } else {
      *out |= bit;
    }

    SREG = oldSREG;
  }
}

void pinMode(int pin, int MODE) {

  if (pin > 19) {
    Wire.beginTransmission(0x08);  // informs the bus that we will be sending data to slave device 8 (0x08)
    Wire.write(0);
    Wire.write(pin);
    Wire.write(MODE);  // send value_pot
    Wire.endTransmission();
  } else if (pin <= 19) {
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *reg, *out;

    if (port == NOT_A_PIN) return;

    // JWS: can I let the optimizer do this?
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (MODE == INPUT) {
      uint8_t oldSREG = SREG;
      cli();
      *reg &= ~bit;
      *out &= ~bit;
      SREG = oldSREG;
    } else if (MODE == INPUT_PULLUP) {
      uint8_t oldSREG = SREG;
      cli();
      *reg &= ~bit;
      *out |= bit;
      SREG = oldSREG;
    } else {
      uint8_t oldSREG = SREG;
      cli();
      *reg |= bit;
      SREG = oldSREG;
    }
  }
}


void analogWrite(int pin, int value) {
  if (pin > 19) {
    Wire.beginTransmission(0x08);  // informs the bus that we will be sending data to slave device 8 (0x08)
    Wire.write(2);
    Wire.write(pin);
    Wire.write(value);  // send value_pot
    Wire.endTransmission();
  } else if (pin <= 19) {
    if (value == 0) {
      digitalWrite(pin, LOW);
    } else if (value == 255) {
      digitalWrite(pin, HIGH);
    } else {
      switch (digitalPinToTimer(pin)) {
        case TIMER0A:
          // connect pwm to pin on timer 0, channel A
          sbi(TCCR0A, COM0A1);
          OCR0A = value;  // set pwm duty
          break;

        case TIMER0B:
          // connect pwm to pin on timer 0, channel B
          sbi(TCCR0A, COM0B1);
          OCR0B = value;  // set pwm duty
          break;

        case TIMER1A:
          // connect pwm to pin on timer 1, channel A
          sbi(TCCR1A, COM1A1);
          OCR1A = value;  // set pwm duty
          break;

        case TIMER1B:
          // connect pwm to pin on timer 1, channel B
          sbi(TCCR1A, COM1B1);
          OCR1B = value;  // set pwm duty
          break;

        case TIMER2A:
          // connect pwm to pin on timer 2, channel A
          sbi(TCCR2A, COM2A1);
          OCR2A = value;  // set pwm duty
          break;

        case TIMER2B:
          // connect pwm to pin on timer 2, channel B
          sbi(TCCR2A, COM2B1);
          OCR2B = value;  // set pwm duty
          break;

        case NOT_ON_TIMER:
        default:
          if (value < 128) {
            digitalWrite(pin, LOW);
          } else {
            digitalWrite(pin, HIGH);
          }
      }
    }
  }
}



int digitalRead(int pin) {
  if (pin > 19) {
    Wire.beginTransmission(0x08);  // informs the bus that we will be sending data to slave device 8 (0x08)
    Wire.write(4);
    Wire.write(pin);
    Wire.write(0);
    Wire.endTransmission();
    Wire.requestFrom(0x08, 1);
    return Wire.read();
  }
  if (pin <= 19) {
    {
      uint8_t timer = digitalPinToTimer(pin);
      uint8_t bit = digitalPinToBitMask(pin);
      uint8_t port = digitalPinToPort(pin);

      if (port == NOT_A_PIN) return LOW;

      // If the pin that support PWM output, we need to turn it off
      // before getting a digital reading.
      if (timer != NOT_ON_TIMER) turnOffPWM(timer);

      if (*portInputRegister(port) & bit) return HIGH;
      return LOW;
    }
  }
}






int analogRead(int pin) {
  if (pin > 19) {
    Wire.beginTransmission(0x08);  // informs the bus that we will be sending data to slave device 8 (0x08)
    Wire.write(3);
    Wire.write(pin);
    Wire.endTransmission();
    Wire.requestFrom(0x08, 1);
    return Wire.read();
  }
  if (pin <= 19) {

    uint8_t analog_reference = DEFAULT;
#if defined(analogPinToChannel)
#if defined(__AVR_ATmega32U4__)
    if (pin >= 18) pin -= 18;  // allow for channel or pin numbers
#endif
    pin = analogPinToChannel(pin);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    if (pin >= 54) pin -= 54;  // allow for channel or pin numbers
#elif defined(__AVR_ATmega32U4__)
    if (pin >= 18) pin -= 18;  // allow for channel or pin numbers
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
    if (pin >= 24) pin -= 24;  // allow for channel or pin numbers
#else
    if (pin >= 14) pin -= 14;  // allow for channel or pin numbers
#endif

#if defined(ADCSRB) && defined(MUX5)
    // the MUX5 bit of ADCSRB selects whether we're reading from channels
    // 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
    ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif

    // set the analog reference (high two bits of ADMUX) and select the
    // channel (low 4 bits).  this also sets ADLAR (left-adjust result)
    // to 0 (the default).
#if defined(ADMUX)
#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = (analog_reference << 4) | (pin & 0x07);
#else
    ADMUX = (analog_reference << 6) | (pin & 0x07);
#endif
#endif

    // without a delay, we seem to read from the wrong channel
    //delay(1);

#if defined(ADCSRA) && defined(ADC)
    // start the conversion
    sbi(ADCSRA, ADSC);

    // ADSC is cleared when the conversion finishes
    while (bit_is_set(ADCSRA, ADSC))
      ;

    // ADC macro takes care of reading ADC register.
    // avr-gcc implements the proper reading order: ADCL is read first.
    return ADC;
#else
    // we dont have an ADC, return 0
    return 0;
#endif
  }
}



