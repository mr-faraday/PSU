/**
 * Разработка кросс-платформенных приложений
 * Лабараторная работа №1
 * <p>
 * Ляхович Д.А.
 * 17-ИТд
 * 9 вариант
 * <p>
 * Задание 1
 * Задается массив. Узнать, какие элементы встречаются в массиве больше
 * одного раза.
 */

package com.cpad_lab1;

import java.util.Arrays;

public class Task1 {

    public static void main(String[] args) {
        int[] arr = {3, 10, 25, 3, 5, 15, 4, 5, 6, 2, 1, 10};

        Arrays.sort(arr);
        for (int i = 0; i < arr.length - 1; i++) {
            if (arr[i] == arr[i + 1]) {
                System.out.println("\t" + arr[i] + "\t");
            }
        }
    }
}
