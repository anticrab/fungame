//
// Created by lokot_zxe3r on 09.02.2024.
//
#include "windows.h"
#include <chrono>
#include <cinttypes>
#include <iostream>
#include <thread>
#include <winuser.h>

#include "console.h"
#include "draw.h"
#include "my_math.h"
#include "snake.h"

void ErrorExit(LPCSTR);

uint64_t current_timestamp();

Console console(30, 120);

int main() {

  HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD size;
  size.X = 120;
  size.Y = 30;

  BOOL resizeSuccessful = SetConsoleScreenBufferSize(hStdout, size);

  if (!resizeSuccessful) {
    DWORD error = GetLastError();
    printf("SetConsoleScreenBufferSize failed with error %d", error);
    return 1;
  }

  constexpr int activeDuration =
      100 * 1000; // длительность работы программы в миллисекундах
  constexpr int delay1 = 100;
  constexpr int delay2 = 200;

  uint64_t currentTime = current_timestamp();
  uint64_t startTime = currentTime;
  uint64_t updateTime1 = currentTime + delay1;
  uint64_t endTime = currentTime + activeDuration;

  HANDLE hStdin;
  const short bufferSize = 128;
  INPUT_RECORD irInBuf[bufferSize];

  hStdin = GetStdHandle(STD_INPUT_HANDLE); // получаем ссылку на стандартный
                                           // поток ввода (input handle)
  if (hStdin == INVALID_HANDLE_VALUE) {
    ErrorExit("GetStdHandle");
  }

  int index = 0;
  int eventsCount = 0;
  float  x = 10;
  float  y = 10;
  float x1 = 0;
  float y1 = 30*8/2;
  float s = 0;

  DrawArray cyrcles;
  auto pnt4 = new Cyrcle{240, 30*8/2, 60, 7};
  auto pnt5 = new Cyrcle{240, 30*8/2, 4, 7};
  auto rect1 = new DrawRect{8,8,8,8, 7};
  cyrcles.add(pnt4, rect1);
  // cyrcles.add(pnt5);
  auto snake = new Snake(100,100,10,5);
  snake->mag(10);

  Vector2 moveVector{10,0};

  console.print();
  while (true) {


    startTime = current_timestamp();
    DWORD cNumRead = 0;
    BOOL peekSuccessful = PeekConsoleInput(
        hStdin,     // ссылка на поток ввода
        irInBuf,    // буфер, в который будут помещена информация о событиях
        bufferSize, // размер буфера
        &cNumRead);
    if (!peekSuccessful) {
      ErrorExit("PeekConsoleInput");
    }

    if (!FlushConsoleInputBuffer(hStdin)) {
      ErrorExit("FlushConsoleInputBuffer");
    }

    eventsCount += cNumRead;
    // printf("iteration %d total %d current %d\n", index, eventsCount,
    // cNumRead);

    // for (DWORD i = 0; i < cNumRead; i++) {
    //   if (irInBuf[i].EventType == KEY_EVENT) {
    //     KEY_EVENT_RECORD ker = irInBuf[i].Event.KeyEvent;
    //     if (ker.bKeyDown) {
    //       if (ker.wVirtualKeyCode == 38) {
    //         --x;
    //       } else if (ker.wVirtualKeyCode == 40) {
    //         ++x;
    //       } else if (ker.wVirtualKeyCode == 39) {
    //         ++y;
    //       } else if (ker.wVirtualKeyCode == 37) {
    //         --y;
    //       }
    //       // printf("key %d pressed\n", ker.wVirtualKeyCode);
    //     } else {
    //       // printf("key released\n");
    //     }
    //   }
    // }
    if (GetKeyState('A') & 0x8000) {
      y -= 0.1;
      moveVector = moveVector.rotate(-M_PI/300);
    }
    if (GetKeyState('W') & 0x8000) {
      y -= 0.1;
    }
    if (GetKeyState('D') & 0x8000) {
      x += 0.1;
      moveVector = moveVector.rotate(+M_PI/300);
    }
    if (GetKeyState('S') & 0x8000) {
      y += 0.1;
    }

    currentTime = current_timestamp();
    // if (updateTime_200 <= currentTime) {
    //   updateTime_200 += delay_200;
    //   y--;
    //   // printf("Each 200 ms. Player position is (%d, %d)\n", x, y);
    // }
    if (updateTime1 <= currentTime) { //
      // x1 = (x1 + 0.1 > 120 * 2) ? 0 : x1 + 0.1;
      s = (s + 0.01 > M_PI * 2) ? 0 : s + 0.01;

      snake->move(moveVector.x, moveVector.y);

      updateTime1 += delay1;

    }
    // y1 = (y1 + 1 > 30 * 8) ? 0 : y1 + 1;
    pnt4->center( x, y);

    snake->draw(console);
    // pnt4->draw(console);

    console.print();

    currentTime = current_timestamp();
    while (currentTime - startTime < 2) {
      std::chrono::milliseconds timespan(1);
      std::this_thread::sleep_for(timespan);
      currentTime = current_timestamp();
    }
    ++index;
  }

  return 0;
}

void ErrorExit(LPCSTR lpszMessage) {
  fprintf(stderr, "%s\n", lpszMessage);
  ExitProcess(0);
}

uint64_t current_timestamp() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now().time_since_epoch())
      .count();
}
