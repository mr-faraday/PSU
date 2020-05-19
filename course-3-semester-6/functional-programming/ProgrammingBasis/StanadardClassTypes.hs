-- Пусть существуют два класса типов KnownToGork и KnownToMork, которые предоставляют методы
-- stomp (stab) и doesEnrageGork (doesEnrageMork) соответственно

-- Класса типов KnownToGorkAndMork является расширением обоих этих классов, предоставляя дополнительно метод stompOrStab

-- Задайте реализацию по умолчанию метода stompOrStab, которая вызывает метод stomp,
-- если переданное ему значение приводит в ярость Морка; вызывает stab, если оно приводит
-- в ярость Горка и вызывает сначала stab, а потом stomp, если оно приводит в ярость их обоих.
-- Если не происходит ничего из вышеперечисленного, метод должен возвращать переданный ему аргумент.

class KnownToGork a where
  stomp :: a -> a
  doesEnrageGork :: a -> Bool

class KnownToMork a where
  stab :: a -> a
  doesEnrageMork :: a -> Bool

class (KnownToGork a, KnownToMork a) => KnownToGorkAndMork a where
  stompOrStab :: a -> a
  stompOrStab = (\x ->
    if
      doesEnrageMork x || doesEnrageGork x
    then
      if
        doesEnrageMork x && doesEnrageGork x
      then
        stomp (stab x)
      else
        if
          doesEnrageMork x
        then
          stomp x
        else
          stab x
    else
      x
    )


-- Имея функцию ip = show a ++ show b ++ show c ++ show d определите значения
-- a, b, c, d так, чтобы добиться следующего поведения:

-- GHCi> ip
-- "127.224.120.12"

a = 127.2
b = 24.1
c = 20.1
d = 2

ip = show a ++ show b ++ show c ++ show d


-- Реализуйте класс типов

-- class SafeEnum a where
--   ssucc :: a -> a
--   spred :: a -> a

-- обе функции которого ведут себя как succ и pred стандартного класса Enum, однако являются тотальными,
-- то есть не останавливаются с ошибкой на наибольшем и наименьшем значениях типа-перечисления соответственно,
-- а обеспечивают циклическое поведение. Ваш класс должен быть расширением ряда классов типов
-- стандартной библиотеки, так чтобы можно было написать реализацию по умолчанию его методов,
-- позволяющую объявлять его представителей без необходимости писать какой бы то ни было код.
-- Например, для типа Bool должно быть достаточно написать строку

-- instance SafeEnum Bool

-- и получить возможность вызывать

-- GHCi> ssucc False
-- True
-- GHCi> ssucc True
-- False

class (Enum a, Bounded a, Eq a) => SafeEnum a where
  ssucc :: a -> a
  ssucc x
    | maxBound == x = minBound
    | otherwise     = succ x

  spred :: a -> a
  spred x
    | minBound == x = maxBound
    | otherwise     = pred x


-- Напишите функцию с сигнатурой:

-- avg :: Int -> Int -> Int -> Double

-- вычисляющую среднее значение переданных в нее аргументов:

-- GHCi> avg 3 4 8
-- 5.0

avg :: Int -> Int -> Int -> Double
avg a b c = average where
  toNum = fromInteger . toInteger
  sum = toNum a + toNum b + toNum c

  average = sum / 3
