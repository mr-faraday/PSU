-- Напишите функцию readDigits, принимающую строку и возвращающую пару строк.
-- Первый элемент пары содержит цифровой префикс исходной строки, а второй - ее оставшуюся часть.

-- GHCi> readDigits "365ads"
-- ("365","ads")
-- GHCi> readDigits "365"
-- ("365","")

-- В решении вам поможет функция isDigit из модуля Data.Char.

import Data.Char

readDigits :: String -> (String, String)
readDigits str = span isDigit str


-- Реализуйте функцию filterDisj, принимающую два унарных предиката и список,
-- и возвращающую список элементов, удовлетворяющих хотя бы одному из предикатов.

-- GHCi> filterDisj (< 10) odd [7,8,10,11,12]
-- [7,8,11]

filterDisj :: (a -> Bool) -> (a -> Bool) -> [a] -> [a]
filterDisj _  _  []     = []
filterDisj p1 p2 (x:xs) = if (p1 x || p2 x) then x : filterDisj p1 p2 xs else filterDisj p1 p2 xs


-- Напишите реализацию функции qsort. Функция qsort должная принимать на вход список
-- элементов и сортировать его в порядке возрастания с помощью сортировки Хоара:
-- для какого-то элемента x изначального списка (обычно выбирают первый) делить список
-- на элементы меньше и не меньше x, и потом запускаться рекурсивно на обеих частях.

-- GHCi> qsort [1,3,2,5]
-- [1,2,3,5]

-- Разрешается использовать только функции, доступные из библиотеки Prelude.

qsort :: Ord a => [a] -> [a]
qsort []    = []
qsort list  =
  qsort [x | x <- list, x < (head list)] ++
  [x | x <- list, x == (head list)]      ++
  qsort [x | x <- list, x > (head list)]


-- Напишите функцию squares'n'cubes, принимающую список чисел,
-- и возвращающую список квадратов и кубов элементов исходного списка.

-- GHCi> squares'n'cubes [3,4,5]
-- [9,27,16,64,25,125]

squares'n'cubes :: Num a => [a] -> [a]
squares'n'cubes l = concatMap (\x -> [x ^ 2, x ^ 3]) l


-- Воспользовавшись функциями map и concatMap, определите функцию perms,
-- которая возвращает все перестановки, которые можно получить из данного
-- списка, в любом порядке.

-- GHCi> perms [1,2,3]
-- [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

-- Считайте, что все элементы в списке уникальны, и что для пустого списка
-- имеется одна перестановка.

perms :: [a] -> [[a]]
perms []              = [[]]
perms [x]             = [[x]]
perms list@(x:xs:xss) = getOther list ++ swap x xs [] xss where
  swap init els mid []            = getOther ((els : mid) ++ [init]) ++ []
  swap init els mid rest@(rx:rxs) = getOther ((els : mid) ++ (init : rest)) ++ swap init rx (mid ++ [els]) rxs

  getOther []                    = []
  getOther [a]                   = [[a]]
  getOther [a,b]                 = [[a,b]]
  getOther [a,b,c]               = map (a:) [[b,c],[c,b]]
  getOther tList@(t:ts:tss:tsss) = map (t:) (getOther (ts:tss:tsss) ++ swap ts tss [] tsss)

-- Верное:

-- perms :: [a] -> [[a]]
-- perms [] = [[]]
-- perms [x] = [[x]]
-- perms (x:xs) = concatMap (insertElem x) (perms xs) where
-- 			insertElem x [] = [[x]]
-- 			insertElem x yss@(y:ys) = (x:yss) : map (y:) (insertElem x ys)


-- Реализуйте функцию delAllUpper, удаляющую из текста все слова,
-- целиком состоящие из символов в верхнем регистре. Предполагается,
-- что текст состоит только из символов алфавита и пробелов, знаки пунктуации,
-- цифры и т.п. отсутствуют.

-- GHCi> delAllUpper "Abc IS not ABC"
-- "Abc not"

-- Постарайтесь реализовать эту функцию как цепочку композиций, аналогично revWords
-- из предыдущего видео.

delAllUpper :: String -> String
delAllUpper = unwords . filter (\s -> map toUpper s /= s) . words


-- Напишите функцию max3, которой передаются три списка одинаковой длины
-- и которая возвращает список той же длины, содержащий на k-ой позиции наибольшее
-- значение из величин на этой позиции в списках-аргументах.

-- GHCi> max3 [7,2,9] [3,6,8] [1,8,10]
-- [7,8,10]
-- GHCi> max3 "AXZ" "YDW" "MLK"
-- "YXZ"

max3 :: Ord a => [a] -> [a] -> [a] -> [a]
max3 = zipWith3 (\a b c -> max a (max b c))
