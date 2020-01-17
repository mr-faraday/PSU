#!/bin/bash

# Копирование группы файлов удовлетворяющих маске из одного
# каталога в два других (копировать подкаталоги). Маска и два
# других каталога передаются как параметры пакетного файла.

dest=$(realpath "$2") &&
find -name "$1" -print0 |
xargs -0r cp --parents -t "${dest}" --

dest=$(realpath "$3") &&
find -name "$1" -print0 |
xargs -0r cp --parents -t "${dest}" --
