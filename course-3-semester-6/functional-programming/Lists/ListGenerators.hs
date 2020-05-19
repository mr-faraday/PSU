-- Реализуйте c использованием функции zipWith функцию fibStream,
-- возвращающую бесконечный список чисел Фибоначчи.

-- GHCi> take 10 $ fibStream
-- [0,1,1,2,3,5,8,13,21,34]

fibStream :: [Integer]
fibStream = 0 : 1 : zipWith (+) fibStream (tail fibStream)


-- Предположим, что функция repeat, была бы определена следующим образом:

-- repeat = iterate repeatHelper

-- определите, как должна выглядеть функция repeatHelper.

repeatHelper x = x


-- Пусть задан тип Odd нечетных чисел следующим образом:

-- data Odd = Odd Integer 
--   deriving (Eq, Show)

-- Сделайте этот тип представителем класса типов Enum.

-- GHCi> succ $ Odd (-100000000000003)
-- Odd (-100000000000001)

-- Конструкции с четным аргументом, типа Odd 2, считаются
-- недопустимыми и не тестируются.

-- Примечание. Мы еще не знакомились с объявлениями пользовательских типов данных,
-- однако, скорее всего, приведенное объявление не вызовет сложностей. Здесь
-- объявляется тип данных Odd с конструктором Odd. Фактически это простая упаковка
-- для типа Integer. Часть deriving (Eq, Show) указывает компилятору, чтобы он
-- автоматически сгенерировал представителей соответствующих классов типов для нашего 
-- типа (такая возможность имеется для ряда стандартных классов типов). Значения типа
-- Odd можно конструировать следующим образом:

-- GHCi> let x = Odd 33
-- GHCi> x
-- Odd 33

-- и использовать конструктор данных Odd в сопоставлении с образцом:

-- addEven :: Odd -> Integer -> Odd
-- addEven (Odd n) m | m `mod` 2 == 0 = Odd (n + m)
--                   | otherwise      = error "addEven: second parameter cannot be odd"

data Odd = Odd Integer deriving (Eq,Show)

instance Ord Odd where
  (>)  a b = unOdd a >  unOdd b
  (<=) a b = unOdd a <= unOdd b

unOdd :: Odd -> Integer
unOdd (Odd n) = n

enumDeltaToOdd x delta lim
  | delta >= 0 = up_list x delta lim
  | otherwise  = dn_list x delta lim

up_list :: Odd -> Integer -> Odd -> [Odd]
up_list x0 delta lim = go (x0 :: Odd) where
  go x | x > lim   = []
       | otherwise = x : go (Odd (unOdd x + delta))

dn_list :: Odd -> Integer -> Odd -> [Odd]
dn_list x0 delta lim = go (x0 :: Odd) where
  go x | x < lim   = []
       | otherwise = x : go (Odd (unOdd x + delta))

instance Enum Odd where
  succ x = Odd (unOdd x + 2)
  pred x = Odd (unOdd x - 2)
  toEnum = Odd . toInteger
  fromEnum = fromInteger . unOdd

  enumFrom x = x : enumFrom (Odd (unOdd x + 2))

  enumFromThen x y = enumDeltaOdd (unOdd x) (unOdd y - unOdd x) where
    enumDeltaOdd x d = x `seq` (Odd x : (enumDeltaOdd (x + d) d))
  
  enumFromTo x lim = enumDeltaToOdd x 2 lim

  enumFromThenTo x y lim = enumDeltaToOdd x (unOdd y - unOdd x) lim


-- Пусть есть список положительных достоинств монет coins, отсортированный
-- по возрастанию. Воспользовавшись механизмом генераторов списков, напишите
-- функцию change, которая разбивает переданную ей положительную сумму денег
-- на монеты достоинств из списка coins всеми возможными способами. Например,
-- если coins = [2, 3, 7]:

-- GHCi> change 7
-- [[2,2,3],[2,3,2],[3,2,2],[7]]

-- Примечание. Порядок монет в каждом разбиении имеет значение, то есть наборы
-- [2,2,3] и [2,3,2] — различаются.
-- Список coins определять не надо.

coins :: (Ord a, Num a) => [a]
coins = [2, 3, 7]

change :: (Ord a, Num a) => a -> [[a]]
change s = filter (\c -> sum c == s) (calc s)

calc :: (Ord a, Num a) => a -> [[a]]
calc rest = if rest <= 0 then [[]] else [c : bag | c <- coins, bag <- calc (rest - c)]
