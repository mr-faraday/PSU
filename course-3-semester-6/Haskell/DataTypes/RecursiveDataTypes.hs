-- Тип List, определенный ниже, эквивалентен определению списков
-- из стандартной библиотеки в том смысле, что существуют взаимно
-- обратные функции, преобразующие List a в [a] и обратно.
-- Реализуйте эти функции.

data List a = Nil | Cons a (List a)

fromList :: List a -> [a]
fromList Nil      = []
fromList (Cons a tail) = a : fromList tail

toList :: [a] -> List a
toList []     = Nil
toList (x:xs) = Cons x (toList xs)


-- Рассмотрим еще один пример рекурсивного типа данных:

-- data Nat = Zero | Suc Nat

-- Элементы этого типа имеют следующий вид:
-- Zero, Suc Zero, Suc (Suc Zero), Suc (Suc (Suc Zero)), и так далее.
-- Таким образом мы можем считать, что элементы этого типа -
-- это натуральные числа в унарной системе счисления.

-- Мы можем написать функцию, которая преобразует Nat в Integer следующим образом:

fromNat :: Nat -> Integer
fromNat Zero = 0
fromNat (Suc n) = fromNat n + 1

-- Реализуйте функции сложения и умножения этих чисел, а
-- также функцию, вычисляющую факториал.

data Nat = Zero | Suc Nat

toNat :: Integer -> Nat
toNat n | n < 0     = error "toNat: number must be positive"
        | n == 0    = Zero
        | otherwise = Suc (toNat (n - 1))

add :: Nat -> Nat -> Nat
add a b = toNat $ (fromNat a) + (fromNat b)

mul :: Nat -> Nat -> Nat
mul a b = toNat $ (fromNat a) * (fromNat b)

fac :: Nat -> Nat
fac n = toNat . fact $ fromNat n where
  fact n | n == 0    = 1
         | otherwise = n * fact (n - 1)


-- Тип бинарных деревьев можно описать следующим образом:

data Tree a = Leaf a | Node (Tree a) (Tree a)

-- Реализуйте функцию height, возвращающую высоту дерева,
-- и функцию size, возвращающую количество узлов в дереве
-- (и внутренних, и листьев). Считается, что дерево, состоящее
-- из одного листа, имеет высоту 0.

height :: Tree a -> Int
height (Leaf _)   = 0
height (Node l r) = 1 + max (height l) (height r)

size :: Tree a -> Int
size (Leaf _)   = 1
size (Node l r) = 1 + size l + size r


-- Теперь нам нужно написать функцию avg, которая считает
-- среднее арифметическое всех значений в дереве. И мы хотим,
-- чтобы эта функция осуществляла только один проход по дереву.
-- Это можно сделать при помощи вспомогательной функции, возвращающей
-- количество листьев и сумму значений в них. Реализуйте эту функцию.

avg :: Tree Int -> Int
avg t =
    let (c,s) = go t
    in s `div` c
  where
    go :: Tree Int -> (Int,Int)
    go (Leaf n)   = (1, n)
    go (Node l r) = sumOfPairs (go l) (go r)

sumOfPairs :: (Int,Int) -> (Int,Int) -> (Int,Int)
sumOfPairs (x1,y1) (x2,y2) = (x1 + x2, y1 + y2)
