import Data.Char

twoDigits2Int :: Char -> Char -> Int
twoDigits2Int x y = if (isDigit x && isDigit y) then digitToInt x * 10 + digitToInt y else 100

dist :: (Double, Double) -> (Double, Double) -> Double
dist p1 p2 = sqrt $ (fst p2 - fst p1) ^ 2 + (snd p2 - snd p1) ^ 2
