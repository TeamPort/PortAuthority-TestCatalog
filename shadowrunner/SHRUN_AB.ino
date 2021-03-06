/*
  SHADOW RUNNER: http://www.team-arg.org/shrun-manual.html

  Arduboy version 1.6 : http://www.team-arg.org/more-about.html

  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

  2015 - JO3RI - Trodoss

  Special thanks to Dreamer3 for helping with the conversion from Gamby

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 15

#include "globals.h"
#include "runner.h"
#include "menu.h"
#include "game.h"
#include "items.h"
#include "playfield.h"

#include "stdlib.h"

typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGameInitLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
};

void setup () {
  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
}

uint32_t shouldBreak = 32;
void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();
  arduboy.clear();
#ifdef __AVR__
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
#else
  ((FunctionPointer)(mainGameLoop[gameState]))();
#endif
  arduboy.display();
  gameState = STATE_GAME_PLAYING;
  if(shouldBreak-- == 0)
  {
#ifdef __AVR__
      asm("BREAK");
#else
      exit(0);
#endif
  }
}

