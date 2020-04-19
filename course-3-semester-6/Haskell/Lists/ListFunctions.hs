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


-- Сформируйте список целых чисел, содержащий только те элементы исходного списка, значение которых нечетно.

-- GHCi> oddsOnly [2,5,7,10,11,12]
-- [5,7,11]

-- Для анализа четности можно использовать функции odd и even стандартной библиотеки.

oddsOnly :: Integral a => [a] -> [a]
oddsOnly list = newList where
  add acc (el:tail)
    | length tail == 0 = if odd el then reverse (el: acc) else reverse acc
    | odd el           = add (el : acc) tail
    | otherwise        = add acc tail

  newList = if length list == 0 then [] else add [] list


-- Реализуйте функцию isPalindrome, которая определяет, является ли переданный ей список палиндромом.

-- GHCi> isPalindrome "saippuakivikauppias"
-- True
-- GHCi> isPalindrome [1]
-- True
-- GHCi> isPalindrome [1, 2]
-- False

isPalindrome :: Eq a => [a] -> Bool
isPalindrome l = if l == (reverse l) then True else False


-- Составьте список сумм соответствующих элементов трех заданных списков.
-- Длина результирующего списка должна быть равна длине самого длинного из заданных списков,
-- при этом «закончившиеся» списки не должны давать вклада в суммы.

-- GHCi> sum3 [1,2,3] [4,5] [6]
-- [11,7,3]

sum3 :: Num a => [a] -> [a] -> [a] -> [a]
sum3 l1 l2 l3 = sum2 l1 (sum2 l2 l3)

sum2 :: Num a => [a] -> [a] -> [a]
sum2 t1 [] = t1
sum2 [] t2 = t2
sum2 (x1:xs1) (x2:xs2) = (x1 + x2) : sum2 xs1 xs2


-- Напишите функцию groupElems которая группирует одинаковые элементы в списке
-- (если они идут подряд) и возвращает список таких групп.

-- GHCi> groupElems []
-- []
-- GHCi> groupElems [1,2]
-- [[1],[2]]
-- GHCi> groupElems [1,2,2,2,4]
-- [[1],[2,2,2],[4]]
-- GHCi> groupElems [1,2,3,2,4]
-- [[1],[2],[3],[2],[4]]

-- Разрешается использовать только функции, доступные из библиотеки Prelude.

groupElems :: Eq a => [a] -> [[a]]
groupElems [] = []
groupElems l  = group where
  add [] = []
  add xl =
    let
      (fstPart, restPart) = span (== (head xl)) xl
    in
      fstPart : add restPart

  group = add l
