#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    100

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Clear all LEDs to white
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(1000);

  // Effect 1: Alternating red and white stripes
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = (i % 2 == 0) ? CRGB::Red : CRGB::White;
  }
  FastLED.show();
  delay(1000);

  // Effect 2: Red and white blinking
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(500);
  fill_solid(leds, NUM_LEDS, CRGB::White);
  FastLED.show();
  delay(500);

  // Effect 3: Red and white random sparkle
  for (int i = 0; i < 50; i++) {
    int randomLED = random(NUM_LEDS);
    leds[randomLED] = CRGB::Red;
    FastLED.show();
    delay(50);
    leds[randomLED] = CRGB::White;
    FastLED.show();
    delay(50);
  }

  // Effect 4: Red wipe to white
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(50);
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(50);
  }

  // Waving flag effect
  for (int i = 0; i < NUM_LEDS; i++) {
    // Paint the i-th stripe red
    for (int j = i; j < NUM_LEDS; j += 5) {
      leds[j] = CRGB::Red;
    }
    FastLED.show();
    delay(100);
    // Clear the stripe
    for (int j = i; j < NUM_LEDS; j += 5) {
      leds[j] = CRGB::White;
    }
  }

  // Delay to simulate flag waving motion
  delay(500);

  // Repeat the waving flag effect in the opposite direction
  for (int i = NUM_LEDS - 1; i >= 0; i--) {
    // Paint the i-th stripe red
    for (int j = i; j >= 0; j -= 5) {
      leds[j] = CRGB::Red;
    }
    FastLED.show();
    delay(100);
    // Clear the stripe
    for (int j = i; j >= 0; j -= 5) {
      leds[j] = CRGB::White;
    }
  }

  // Delay to simulate flag waving motion
  delay(500);
}
