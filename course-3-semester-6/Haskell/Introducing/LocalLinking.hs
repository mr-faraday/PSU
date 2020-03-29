seqA :: Integer -> Integer
seqA n =
  let
    calc a1 a2 a3 =
      a1 + a2 - 2 * a3

    helper k prev1 prev2 prev3 
      | k == 3    = calc prev1 prev2 prev3
      | otherwise = helper (k - 1) (calc prev1 prev2 prev3) prev1 prev2

    seq k
      | k == 0    = 1
      | k == 1    = 2
      | k == 2    = 3
      | k > 2     = helper k 3 2 1
      | otherwise = error "Number must be >= 0"
  in
    seq n

sum'n'count :: Integer -> (Integer, Integer)
sum'n'count x = result where
  sum = summary (abs x) 0
  summary n acc
    | n == 0    = acc
    | otherwise = summary (n `div` 10) (acc + separatedNum n)

  separatedNum n
    | n < 10    = n
    | otherwise = separatedNum (n `mod` 10)

  count = counter (abs x) 0
  counter n acc
    | n < 10    = acc + 1
    | otherwise = counter (n `div` 10) (acc + 1)

  result = (sum, count)

integration :: (Double -> Double) -> Double -> Double -> Double
integration f a b = area where
  n = 1000
  h = (b - a) / n
  sum i x acc
    | i == n - 1 = acc
    | otherwise  = sum (i + 1) (x + h) (acc + (2 * f x))

  area = h / 2 * (f a + (sum 0 (a + h) 0) + f b)
