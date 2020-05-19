-- Реализуйте функции distance, считающую расстояние между двумя
-- точками с вещественными координатами, и manhDistance, считающую
-- манхэттенское расстояние между двумя точками с целочисленными
-- координатами.

import Data.Char(isDigit)

data Coord a = Coord a a

distance :: Coord Double -> Coord Double -> Double
distance (Coord x1 y1) (Coord x2 y2) = sqrt $ (x2 - x1)^2 + (y2 - y1)^2

manhDistance :: Coord Int -> Coord Int -> Int
manhDistance (Coord x1 y1) (Coord x2 y2) = abs (x2 - x1) + abs (y2 - y1)


-- Реализуйте функцию, которая ищет в строке первое вхождение символа,
-- который является цифрой, и возвращает Nothing, если в строке нет цифр.

findDigit :: [Char] -> Maybe Char
findDigit str = proc (filter isDigit str) where
  proc (f:l) = Just f
  proc _     = Nothing


-- Реализуйте функцию findDigitOrX, использующую функцию findDigit
-- (последнюю реализовывать не нужно). findDigitOrX должна находить
-- цифру в строке, а если в строке цифр нет, то она должна возвращать
-- символ 'X'. Используйте конструкцию case.

findDigitOrX :: [Char] -> Char
findDigitOrX str =
  case findDigit str of
    (Just d) -> d
    Nothing  -> 'X'


-- Maybe можно рассматривать как простой контейнер, например,
-- как список длины 0 или 1. Реализовать функции maybeToList и listToMaybe,
-- преобразующие Maybe a в [a] и наоборот (вторая функция отбрасывает все
-- элементы списка, кроме первого).

maybeToList :: Maybe a -> [a]
maybeToList Nothing  = []
maybeToList (Just val) = [val]

listToMaybe :: [a] -> Maybe a
listToMaybe []     = Nothing
listToMaybe (x:xs) = Just x
