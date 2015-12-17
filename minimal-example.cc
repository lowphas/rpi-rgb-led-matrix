// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)

#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define dist(a, b, c, d) sqrt(double((a - c) * (a - c) + (b - d) * (b - d)))

using rgb_matrix::GPIO;
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

static void DrawOnCanvas(Canvas *canvas) {
  /*
   * Let's create a simple animation. We use the canvas to draw
   * pixels. We wait between each step to have a slower animation.
   */
  canvas->Fill(0, 0, 255);

  int asd=0;
  srand(time(NULL));
  int i,j,color;
  int time=0;



  while(asd==0){
          time++;
          if(time>=6000)time=0;

          for (i=0;i<32;i++) {
                  for (j=0;j<32;j++) {

                        double value = sin(dist(i+time , j, 128.0, 128.0) / 4.0)
                                 + sin(dist(i, j, 64.0, 64.0) / 4.0)
                                 + sin(dist(i, j, 192.0, 64) / 4.0)
                                 + sin(dist(i, j+time, 192.0, 100.0) / 4.0);
                        color = int((4 + value)) * 32;

                        canvas->SetPixel(i, j, color, color*2, 255 - color);
                  }
          }

      usleep(1 * 50000);
  }
}

int main(int argc, char *argv[]) {
  /*
   * Set up GPIO pins. This fails when not running as root.
   */
  GPIO io;
  if (!io.Init())
    return 1;
    
  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
  int rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
  int chain = 1;    // Number of boards chained together.
  int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
  Canvas *canvas = new RGBMatrix(&io, rows, chain, parallel);

  DrawOnCanvas(canvas);    // Using the canvas.

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;

  return 0;
}
