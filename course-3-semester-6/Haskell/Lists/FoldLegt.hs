-- Реализуйте функцию meanList, которая находит среднее значение
-- элементов списка, используя однократный вызов функции свертки.

-- GHCi> meanList [1,2,3,4]
-- 2.5

-- Постобработка считается допустимой, то есть предполагаемая реализация
-- функции meanList имеет вид

-- meanList = someFun . foldr someFoldingFun someIni

meanList :: [Double] -> Double
meanList = avrg . foldr (\x (s,l) -> (x + s, l + 1)) (0,0)
avrg (s,l) = s / l


-- Используя однократный вызов свертки, реализуйте функцию evenOnly,
-- которая выбрасывает из списка элементы, стоящие на нечетных местах,
-- оставляя только четные.

-- GHCi> evenOnly [1..10]
-- [2,4,6,8,10]
-- GHCi> evenOnly ['a'..'z']
-- "bdfhjlnprtvxz"

evenOnly :: [a] -> [a]
evenOnly = reverse . snd . foldl f ([],[]) where
  f (odds,evens) x | length odds == length evens = (x:odds,evens)
                   | otherwise                   = (odds,x:evens)


-- Попробуйте добиться того, чтобы реализованная вами в прошлом задании
-- функция evenOnly позволяла работать и с бесконечными списками.

-- То есть, например, запрос на первые три элемента бесконечного списка,
-- возвращаемого этой функцией, примененной к списку всех натуральных чисел,
-- должен завершаться:

-- GHCi> take 3 (evenOnly [1..])
-- [2,4,6]

evenOnly' :: [a] -> [a]
evenOnly' lst = evens False lst where
  evens _      []                 = []
  evens isEven (x:xs) | isEven    = x : evens False xs
                      | otherwise = evens True xs
