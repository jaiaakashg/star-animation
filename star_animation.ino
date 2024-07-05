#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct Star {
  int x;
  int y;
  int size;
  int brightness;
  int pulse;
};

Star stars[] = {
  {10, 20, 2, 0, random(5, 10)},
  {50, 30, 3, 0, random(5, 10)},
  {90, 40, 4, 0, random(5, 10)}
};

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(10, 10);
  display.println("Realistic Star Animation");

  display.display();
  delay(2000);
}

void loop() {
  display.clearDisplay();

  updateStars();
  drawStars();

  display.display();
  delay(100); 
}

void updateStars() {
  for (int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++) {
    stars[i].brightness = random(10);

    stars[i].pulse = (stars[i].pulse + 1) % 5;

    stars[i].x = (stars[i].x + random(-1, 2)) % SCREEN_WIDTH;
    stars[i].y = (stars[i].y + random(-1, 2)) % SCREEN_HEIGHT;
  }
}

void drawStars() {
  for (int i = 0; i < sizeof(stars) / sizeof(stars[0]); i++) {
    int halfSize = stars[i].size * 5; // Half size in pixels
    int brightness = stars[i].brightness * (stars[i].pulse + 1) / 5; // Pulsating effect
    display.drawLine(stars[i].x, stars[i].y - halfSize, stars[i].x, stars[i].y + halfSize, brightness); // Vertical line
    display.drawLine(stars[i].x - halfSize, stars[i].y, stars[i].x + halfSize, stars[i].y, brightness); // Horizontal line
    display.drawLine(stars[i].x - stars[i].size * 3, stars[i].y - stars[i].size * 3, stars[i].x + stars[i].size * 3, stars[i].y + stars[i].size * 3, brightness); // Diagonal lines
  }
}

