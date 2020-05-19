doubleFact :: Integer -> Integer
doubleFact n =
  if n <= 0
    then 1
    else n * doubleFact (n - 2)

fibonacci :: Integer -> Integer
fibonacci n | n == 0                = 0
            | (n == 1 || n == (-1)) = 1
            | n < 0                 = fibonacci (n + 2) - fibonacci (n + 1)
            | n > 0                 = fibonacci (n - 1) + fibonacci (n - 2)

-- |
-- | tail recursion

fibonacci' :: Integer -> Integer
fibonacci' n | n < 0 && even n                  = fibonacciAcc (-n + 1) (-1) 0
             | n > 0 || (n < 0 && not (even n)) = fibonacciAcc (abs n) 0 1
             | otherwise                        = 0

fibonacciAcc :: Integer -> Integer -> Integer -> Integer
fibonacciAcc n prev curr | n == 1    = curr
                         | otherwise = fibonacciAcc (n - 1) curr (prev + curr)
