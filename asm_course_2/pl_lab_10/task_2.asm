; Ляхович Д.А.
; 17-ИТд
; Вариант 9
;
; Языки программирования
; Лабораторная №10
; Задание 2
; Разработать программу вычисления арифметического выражения. Результат вывести в левом верхнем углу экрана в текстовом режиме. Все значения целые знаковые числа разрядностью 16 бит. Это задание выполняется в текстовом режиме.
; (2*C-D/3)/(B-A/4)

.486                                      ;Указание набора команд
.model small                              ;small - модель памяти EXE-программы
Data SEGMENT use16
  ASSUME ds:Data
  ValA dw -100                            ;Значение A
  ValB dw 25                              ;Значение B
  ValC dw 200                             ;Значение C
  ValD dw -150                            ;Значение D
  Sign db 0                               ;Признак отрицательного значения
  Strk db 7 dup(0), 0                     ;Резервирование памяти под строку
Data ENDS
Stk SEGMENT use16 STACK
  ASSUME ss:Stk
  dw 256 dup(0)
Stk ENDS
Code SEGMENT use16
ASSUME cs:Code
start:

  mov ax, seg ValB                        ;Запись в AX сегмента Data
  mov ds, ax                              ;Запись в DS AX
  mov ax, ValC                            ;Запись в AX значение C
  mov cx, 2                               ;Запись в CX значение 2
  imul cx                                 ;Умножение AX*CX -> DX:AX
  
  push dx                                 ;Заносим в стек верхнюю часть результата С*2
  push ax                                 ;Заносим в стек нижнюю часть результата С*2
  
  xor dx, dx                              ;Очищаем DX
  mov ax, ValD                            ;Запись в AX значение D
;//===================//  Если
  or ax, ax                               ;Проверка AX на ноль
  jns next0                               ;Если число > 0, то переход на next0
;//===================//  То
  not dx                                  ;Преобразуем DX как верхнюю часть отрицательного числа DX:AX
;//===================//
next0:
  mov cx, 3                               ;Заносим в CX делитель 3
  idiv cx                                 ;Делим DX:AX на CX
  mov bx, ax                              ;Помещаем разультат деления в BX
  
  pop ax
  pop dx                                  ;Достаём прошлое умножение 2*C
  
  sub ax, bx
  
  push dx
  push ax                                 ;Заносим в стек результат 2*C-D/3
 
  xor dx, dx
  mov ax, ValA
;//===================//  Если
  or ax, ax                               ;Проверка AX на ноль
  jns next1                               ;Если число > 0, то переход на next0
;//===================//  То
  not dx                                  ;Преобразуем DX как верхнюю часть отрицательного числа DX:AX
;//===================//
next1:
  mov cx, 4
  idiv cx                                 ;Делим на 4
  
  mov bx, ValB                            ;Вычитаемое в AX
  sub bx, ax                              ;Вычитаем A/4 из B
  
  pop ax
  pop dx                                  ;Достаём 2*C-D/3
  
  idiv bx                                 ;Делим 2*C-D/3[DX:AX] на B-A/4[BX]
  
;//==================   Вывод результата
  
  or ax, ax                               ;Проверка AX на ноль
  jns next6                               ;Если число > 0, то переход на next6
  neg ax                                  ;Преобразуем в положительное число
  mov byte ptr Sign, 1                    ;Сохраняем в Sign признак отрицательного результата
next6:
  lea si, Strk                            ;Загружаем в SI смещение Strk
  add si, 6                               ;Переходим в конец строки
  mov cx, 10                              ;Заносим в CX значение 10
  next7:
    xor dx, dx                            ;Очистка DX
    div cx                                ;Деление DX:AX / CX
    add dl, 48                            ;Суммируем остаток с кодом ‘0’
    mov ds:[si], dl                       ;Записываем в строку
    or ax, ax                             ;Проверка AX на ноль
    jz next8                              ;Если ноль, то переходим на next8
    dec si                                ;Уменьшаем SI на 1
    jmp next7                             ;Переход на next7
next8:
  mov ax, 0b800h                          ;Заносим в AX адрес сегмента видеобуфера
  mov es, ax                              ;Устанавливаем ES на видеобуфер
  xor di, di                              ;Очистка DI
  mov ah, 0Fh                             ;В AH записываем код цвета
  cmp byte ptr Sign, 1                    ;Если результат был положительным, то
  jnz next9                               ;переход на next9
  mov al, '-'                             ;Записываем в AL код ‘-’
  stosw                                   ;Запись AX в ES:[DI]
  next9:
    lodsb                                 ;Загрузка в AL из DS:[SI]
    or al, al                             ;Проверка AL на ноль
    jz nextA                              ;Если ноль, то переход на nextA
    stosw                                 ;Запись AX в ES:[DI]
    jmp next9                             ;Переход на next9
  nextA:
    in al, 60h                            ;Чтение в AL из порта 60h
    cmp al, 1                             ;Сравнение с 1 (ESC)
    jnz nextA                             ;Если не равно, то переход на nextA
    
  mov ax, 4c00h                           ;Запись в AX номер функции выхода
  int 21h                                 ;Завершение программы
  
Code ENDS
end start
