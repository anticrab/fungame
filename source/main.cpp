//
// Created by lokot_zxe3r on 09.02.2024.
//
#include "windows.h"
#include <chrono>
#include <cinttypes>
#include <iostream>
#include <thread>

#include "console.h"
#include "geometry.h"
#include "my_math.h"

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
  constexpr int delay_300 = 300;
  constexpr int delay_200 = 200;

  uint64_t currentTime = current_timestamp();
  uint64_t endTime = currentTime + activeDuration;
  uint64_t updateTime_300 = currentTime + delay_300;
  uint64_t updateTime_200 = currentTime + delay_200;

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
  int x = 10;
  int y = 10;
  float x1 = 0;
  float y1 = 80;

  console.print();

  Cyrcle pnt4{Vector2{x1, y1}, 60, 7};

  while (true) {
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

    for (DWORD i = 0; i < cNumRead; i++) {
      if (irInBuf[i].EventType == KEY_EVENT) {
        KEY_EVENT_RECORD ker = irInBuf[i].Event.KeyEvent;
        if (ker.bKeyDown) {
          if (ker.wVirtualKeyCode == 38) {
            --x;
          } else if (ker.wVirtualKeyCode == 40) {
            ++x;
          } else if (ker.wVirtualKeyCode == 39) {
            ++y;
          } else if (ker.wVirtualKeyCode == 37) {
            --y;
          }
          // printf("key %d pressed\n", ker.wVirtualKeyCode);
        } else {
          // printf("key released\n");
        }
      }
    }

    currentTime = current_timestamp();
    // if (updateTime_300 <= currentTime) {
    //   updateTime_300 += delay_300;
    //   x--;
    //   // printf("Each 300 ms. Player position is (%d, %d)\n", x, y);
    // }
    // if (updateTime_200 <= currentTime) {
    //   updateTime_200 += delay_200;
    //   y--;
    //   // printf("Each 200 ms. Player position is (%d, %d)\n", x, y);
    // }
    x1 = (x1 + 1 > 120 * 4) ? 0 : x1 + 1;
    // y1 = (y1 + 1 > 30 * 8) ? 0 : y1 + 1;
    // Cyrcle pnt1{Vector2{x1, 100}, 40, 6};
    // Cyrcle pnt2{Vector2{0, 0}, 50, 7};
    // Cyrcle pnt3{Vector2{95 * 4, 15 * 8}, 40, 7};
    pnt4.center(x1, y1);
    // pnt1.draw(console);
    // auto rr = pnt2.center();
    // pnt2.draw(console);
    // pnt3.draw(console);
    pnt4.draw(console);

    console.print();

    std::chrono::milliseconds timespan(100);
    std::this_thread::sleep_for(timespan);

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
