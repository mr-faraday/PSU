#!/bin/bash

# Поиск файлов по маске в указанном каталоге и его подкаталогах.
# Маска и каталог задается параметром пакетного файла.
# Найденные файлы вывести.

find "$1" -type f -name "$2";
