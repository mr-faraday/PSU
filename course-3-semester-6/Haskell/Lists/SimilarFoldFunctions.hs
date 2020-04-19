import Data.List

-- Напишите реализацию функции, возвращающей последний
-- элемент списка, через foldl1.

lastElem :: [a] -> a
lastElem = foldl1 (\x y -> y)


-- Используя unfoldr, реализуйте функцию, которая возвращает в
-- обратном алфавитном порядке список символов, попадающих в
-- заданный парой диапазон. Попадание символа x в диапазон пары
-- (a,b) означает, что x >= a и x <= b.

-- GHCi> revRange ('a','z')
-- "zyxwvutsrqponmlkjihgfedcba"

revRange :: (Char,Char) -> [Char]
revRange (f,t) = if t < f then "" else reverse . unfoldr g $ (f,t)
  where g (f,t) | f == succ t = Nothing
                | otherwise   = Just (f, (succ f,t))
