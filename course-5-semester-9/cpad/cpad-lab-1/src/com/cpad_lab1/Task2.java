/**
 * Разработка кросс-платформенных приложений
 * Лабараторная работа №1
 * <p>
 * Ляхович Д.А.
 * 17-ИТд
 * 9 вариант
 * <p>
 * Задание 2
 * В квадратной матрице определить максимальный и минимальные элементы.
 * Если таких элементов несколько, то максимальный определяется по
 * наибольшей сумме своих индексов, минимальный – по наименьшей.
 */

package com.cpad_lab1;

public class Task2 {

    public static void main(String[] args) {
        int[][] matr = {
                {35, 10, 25, 43, 52, 15, 34, 54, 36, 42, 14, 10},
                {32, 13, 265, 3, 5, 85, 4, 5, 6, 22, 14, 10},
                {3, 130, 25, 35, 56, 15, 74, 5, 65, 27, 41, 10},
                {3, 104, 25, 334, 15, 15, 42, 5, 46, 2, 11, 10},
                {33, 120, 25, 31, 55, 135, 43, 35, 626, 52, 13, 10},
                {13, 10, 245, 34, 53, 15, 43, 51, 46, 24, 13, 106},
                {32, 130, 25, 33, 56, 155, 42, 45, 65, 22, 71, 10},
        };

        int max = matr[0][0], maxSum = 0, min = matr[0][0], minSum = 0;
        for (int i = 0; i < matr.length; i++) {
            int[] row = matr[i];

            for (int j = 0; j < row.length; j++) {
                int sum = i + j;
                int v = row[j];

                if (v > max || (v == max && sum > maxSum)) {
                    max = v;
                    maxSum = sum;
                } else if (v < min || (v == min && sum < minSum)) {
                    min = v;
                    minSum = sum;
                }
            }
        }

        System.out.println("Max value: " + max);
        System.out.println("Min value: " + min);
    }
}
