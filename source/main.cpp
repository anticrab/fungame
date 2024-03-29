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
  constexpr int delay2 = 1000;

  uint64_t currentTime = current_timestamp();
  uint64_t startTime = currentTime;
  uint64_t updateTime1 = currentTime + delay1;
  uint64_t updateTime2 = currentTime + delay2;
  uint64_t endTime = currentTime + activeDuration;

  HANDLE hStdin;
  const short bufferSize = 128;
  INPUT_RECORD irInBuf[bufferSize];

  hStdin = GetStdHandle(STD_INPUT_HANDLE); // получаем ссылку на стандартный
                                           // поток ввода (input handle)
  if (hStdin == INVALID_HANDLE_VALUE) {
    ErrorExit("GetStdHandle");
  }

  // float  x = 10;
  // float  y = 10;
  // float x1 = 0;
  // float y1 = 30*8/2;
  // float s = 0;

  // DrawArray cyrcles;
  // auto pnt4 = new Cyrcle{240, 30*8/2, 60, 7};
  // auto pnt5 = new Cyrcle{240, 30*8/2, 4, 7};
  // auto rect1 = new DrawRect{8,8,8,8, 7};
  // cyrcles.add(pnt4, rect1);
  // cyrcles.add(pnt5);

  std::chrono::milliseconds timespan(1);

  while (true) {

    currentTime = current_timestamp();
    startTime = currentTime;
    updateTime1 = currentTime + delay1;
    updateTime2 = currentTime + delay2;
    endTime = currentTime + activeDuration;


    auto snake = new Snake(30, 30, 10, 5);
    // snake->mag(20);

    auto apple = new Apple(100, 100, 12, 7);
    apple->rand_coords();

    console.clear_symbols();
    console.set_symbol(0, 1, "SCORE: ");
    int score = 0;
    console.set_symbol(7, 1, '0');


    Vector2 moveVector{10, 0};

    console.render_display();
    console.print();

    while (snake->is_alive_border() && snake->is_alive_body()) {
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
        moveVector = moveVector.rotate(-M_PI / 200);
      }
      if (GetKeyState('D') & 0x8000) {
        moveVector = moveVector.rotate(+M_PI / 200);
      }

      if (snake->is_eat_apple(apple)) {
        snake->mag();
        apple->rand_coords();
        ++score;
        console.set_symbol(7, 1, std::to_string(score));
      }

      currentTime = current_timestamp();
      if (updateTime1 <= currentTime) {
        snake->move(moveVector.x, moveVector.y);

        updateTime1 += delay1;
      }

      if(updateTime2 <= currentTime) {
        // snake->mag();
        updateTime2 += delay2;
      }

      snake->draw(console);
      apple->draw(console);

      console.render_display();
      console.print();

      currentTime = current_timestamp();
      while (currentTime - startTime < 2) {

        std::this_thread::sleep_for(timespan);
        currentTime = current_timestamp();
      }
    }
    while (!(GetKeyState('R') & 0x8000)) {
      std::this_thread::sleep_for(timespan * 10);
    }
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
