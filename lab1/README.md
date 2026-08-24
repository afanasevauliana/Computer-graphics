# Лабораторная работа № 1

Проект использует установленный `C:\MinGW` и приложенную 32-битную
`glut32.dll`. GLEW для листинга 2 не нужен.

## Сборка и запуск из терминала

```powershell
cmake --preset mingw-debug
cmake --build --preset mingw-debug
.\build\list2.exe
.\build\list3_4.exe
.\build\list5.exe
```

При сборке `glut32.dll` автоматически копируется рядом с программой.
