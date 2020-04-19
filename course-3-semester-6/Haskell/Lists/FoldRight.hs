-- Напишите реализацию функции concatList через foldr

-- GHCi> concatList [[1,2],[],[3]]
-- [1,2,3]

concatList :: [[a]] -> [a]
concatList = foldr (++) []


-- Используя функцию foldr, напишите реализацию функции lengthList,
-- вычисляющей количество элементов в списке.

-- GHCi> lengthList [7,6,5]
-- 3

lengthList :: [a] -> Int
lengthList = foldr f 0 where
  f l s = 1 + s


-- Реализуйте функцию sumOdd, которая суммирует элементы
-- списка целых чисел, имеющие нечетные значения:

-- GHCi> sumOdd [2,5,30,37]
-- 42

sumOdd :: [Integer] -> Integer
sumOdd = foldr (\x s -> if odd x then x + s else s) 0
