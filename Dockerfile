# Используем базовый образ Ubuntu
FROM ubuntu:24.04

# Устанавливаем переменные для предотвращения зависаний в процессе установки
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Устанавливаем MinGW и необходимые утилиты
RUN apt-get update && apt-get install -y --no-install-recommends \
    mingw-w64 \
    build-essential \
    cmake \
    git \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Устанавливаем переменные окружения для MinGW (по умолчанию 64-bit)
ENV CC=x86_64-w64-mingw32-gcc
ENV CXX=x86_64-w64-mingw32-g++
ENV WINDRES=x86_64-w64-mingw32-windres

# Создаем рабочую директорию в контейнере
WORKDIR /app

# Копируем только скрипты и необходимые файлы для настройки
COPY ./ /app

RUN chmod +x /app/docker_build.sh
CMD ["/app/docker_build.sh"]

