# Simple Arkanoid game on OpenGL + ImGui

## Описание
Реализация классической игры [Арканоид](https://ru.wikipedia.org/wiki/Arkanoid) на C++, OpenGL и [ImGui](https://github.com/ocornut/imgui).
Вам нужно управлять ракеткой и выбивать шариком кирпичи. Основная цель: набрать наибольшее количество очков за выбитые кирпичи.
Будьте осторожны! При попадании в нижнюю границу экрана, у шарика отнимается прочность. Если шарик лопнет, вам придётся начинать сначала.

## Roadmap

- Геймплей [5/6]
  - [x] Основной
  - [x] Минимальные требования (classes Arkanoid, ArkanoidDebugData)
  - [x] Очки
  - [ ] Бонусы и магазин
  - [x] Музыка и звуки
  - [x] Gfx (sprites ?)
- Архитектура [1/3]
  - [x] Основная
  - [ ] Рефакторинг
  - [ ] Более структурированная

## Снимки экрана

### Windows
![Windows screenshot](https://github.com/Krol-X/Arkanoid/raw/main/doc/screenshots/windows.jpg)

### Linux
![Linux screenshot](https://github.com/Krol-X/Arkanoid/raw/main/doc/screenshots/linux.jpg)

## Управление (клавиатура)

- [A][B] или [<-][->] управляют платформой
- [Tab] Окна "читов"
- [Space] Пошаговый режим
- [+] Шаг

## Установка зависимостей для компиляции (Void linux)
```
sudo xbps-install libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel libglvnd-devel
```

## Известные баги

- [Linux] Не находится ikpMP3.so во время связывания
- [Linux] Некорректное воспроизведение звуков
