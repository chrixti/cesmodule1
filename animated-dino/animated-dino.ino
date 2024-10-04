#include <TFT_eSPI.h>  
#include <SPI.h>
#include "bitmaps.h"

TFT_eSPI tft = TFT_eSPI();  

#define BLACK 0x0000
#define WHITE 0xFFFF

// variables
int dinoScale = 3;
int treeScale = 3;
int displayWidth;
int displayHeight;
int groundY;
int dinoWidth = 25 * dinoScale;
int dinoHeight = 26 * dinoScale;
int dinoX;
int dinoY;
int jumpHeight = 60; 
int jumpSpeed = 5;   
int fallSpeed = 5;   
bool isJumping = false;
int jumpProgress = 0;
const int numTrees = 3;
int treeX[numTrees];
int treeY[numTrees];
int treeSpeed = 5; 
const unsigned char* treeBitmaps[numTrees];
int treeTypes[numTrees]; 
int treeWidth[numTrees];
int treeHeight[numTrees];

void setup() {
  tft.init();                
  tft.setRotation(1);        
  tft.fillScreen(BLACK);     

  displayWidth = tft.width();
  displayHeight = tft.height();

  groundY = displayHeight - 10; 

  dinoX = 30;
  dinoY = groundY - dinoHeight; 

  randomSeed(analogRead(0));

  for (int i = 0; i < numTrees; i++) {
    resetTree(i);
  }

  drawBackground(); 
}

void loop() {
  // erase dino
  eraseDinosaur(dinoX, dinoY, dinoWidth, dinoHeight);

  // erase and update trees
  for (int i = 0; i < numTrees; i++) {
    eraseTree(i);
    treeX[i] -= treeSpeed;
    
    if (treeX[i] + treeWidth[i] < 0) {
      resetTree(i);
    }

  }

  // dino jump
  if (isJumping) {
    dinoY -= jumpSpeed;
    jumpProgress += jumpSpeed;
    if (jumpProgress >= jumpHeight) {
      isJumping = false;
    }
  } else if (dinoY < groundY - dinoHeight) {
    dinoY += fallSpeed;
    
    if (dinoY >= groundY - dinoHeight) {
      dinoY = groundY - dinoHeight; 
      jumpProgress = 0;
    }

  } else {
    for (int i = 0; i < numTrees; i++) {
      
      if (checkCollision(i)) {
        isJumping = true; 
        break;
      }

    }
  }

  drawGround();
  drawScaledBitmap(dino, dinoX, dinoY, 25, 26, dinoScale);

  // draw trees
  for (int i = 0; i < numTrees; i++) {
    int bitmapWidth = (treeTypes[i] == 0) ? 11 : 22;
    drawScaledBitmap(treeBitmaps[i], treeX[i], treeY[i], bitmapWidth, 23, treeScale);
  }

  delay(30);
}

void drawBackground() {
  tft.fillScreen(BLACK);
  drawGround();
}

void drawGround() {
  tft.drawLine(0, groundY, tft.width(), groundY, WHITE);
}

void eraseDinosaur(int x, int y, int width, int height) {
  tft.fillRect(x, y, width, height, BLACK);
}

void eraseTree(int index) {
  tft.fillRect(treeX[index], treeY[index], treeWidth[index], treeHeight[index], BLACK);
}

void resetTree(int index) {
  treeTypes[index] = random(0, 2); 
  
  if (treeTypes[index] == 0) {
    treeBitmaps[index] = tree1;
    treeWidth[index] = 11 * treeScale;
  } else {
    treeBitmaps[index] = tree2;
    treeWidth[index] = 22 * treeScale;
  }
  
  treeHeight[index] = 23 * treeScale;

  int minSpacing = 200;
  int maxSpacing = 300;

  if (index == 1) {
    treeX[index] = treeX[0] + random(minSpacing + 100, maxSpacing + 200);
  }

  int maxX = displayWidth;
  
  for (int i = 0; i < numTrees; i++) {
   
    if (i != index && treeX[i] > maxX - displayWidth / 2) {
      maxX = treeX[i];
    }

  }

  treeX[index] = maxX + random(minSpacing, maxSpacing);
  treeY[index] = groundY - treeHeight[index];
}

bool checkCollision(int treeIndex) {
  
  int treeLeft = treeX[treeIndex];
  int treeRight = treeX[treeIndex] + treeWidth[treeIndex];
  int dinoRight = dinoX + dinoWidth;

  return dinoY + dinoHeight >= groundY && dinoRight > treeLeft && dinoX < treeRight;
}

void drawScaledBitmap(const unsigned char* bitmap, int x, int y, int width, int height, int scale) {
  
  for (int i = 0; i < width; i++) {
    
    for (int j = 0; j < height; j++) {   
      int byteWidth = (width + 7) / 8;
      byte byteData = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      bool pixel = byteData & (128 >> (i % 8));

      if (pixel) {
        tft.fillRect(x + i * scale, y + j * scale, scale, scale, WHITE);
      }

    }
  }
}
