-- Реализуйте функции distance, считающую расстояние между двумя
-- точками с вещественными координатами, и manhDistance, считающую
-- манхэттенское расстояние между двумя точками с целочисленными
-- координатами.

data Coord a = Coord a a

distance :: Coord Double -> Coord Double -> Double
distance (Coord x1 y1) (Coord x2 y2) = sqrt $ (x2 - x1)^2 + (y2 - y1)^2

manhDistance :: Coord Int -> Coord Int -> Int
manhDistance (Coord x1 y1) (Coord x2 y2) = abs (x2 - x1) + abs (y2 - y1)
