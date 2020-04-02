-- Реализуйте функцию addTwoElements, которая бы добавляла два переданных ей значения в голову переданного списка.

-- GHCi> addTwoElements 2 12 [85,0,6]
-- [2,12,85,0,6]

addTwoElements :: a -> a -> [a] -> [a]
addTwoElements a b l = a : b : l


-- Реализуйте функцию nTimes, которая возвращает список, состоящий из повторяющихся значений ее первого аргумента.
-- Количество повторов определяется значением второго аргумента этой функции.

-- GHCi> nTimes 42 3
-- [42,42,42]
-- GHCi> nTimes 'z' 5
-- "zzzzz"

nTimes:: a -> Int -> [a]
nTimes i n = list where
  addI times newL = if times == 0 then newL else addI (times - 1) (i : newL)
  list = addI n []
