/**
 * Разработка кросс-платформенных приложений
 * Лабараторная работа №2
 * <p>
 * Ляхович Д.А.
 * 17-ИТд
 * 9 вариант
 * <p>
 * Страна, 2 поля
 */

package com.cpad_lab2;

public class Main {

    public static void main(String[] args) {
        Country b = new Country("Belarus", "BY");

        System.out.println("Country name: " + b.getName() + "#" + b.getCountryCode());
    }
}
