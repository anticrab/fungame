#include "windows.h"
#include <chrono>
#include <cinttypes>
#include <iostream>
#include <thread>

#include "console.h"
#include "draw.h"

void ErrorExit(LPCSTR);

uint64_t current_timestamp();


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

  const int activeDuration = 100 * 1000; // длительность работы программы в миллисекундах
  const int delay_300 = 3000;
  const int delay_200 = 2000;

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

  console Console(30, 120);
  Console.print();

  Console.set(10,10, 'q');

  Console.print();

  while (index < 1000000) {
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
    // printf("iteration %d total %d current %d\n", index, eventsCount, cNumRead);

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
    Console.set(x,y, 'q');
    Console.print();

    std::chrono::milliseconds timespan(100); // or whatever
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