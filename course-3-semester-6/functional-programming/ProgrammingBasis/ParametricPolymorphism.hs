import Data.Function

-- getSecondFrom :: t -> t2 -> t1 -> t2
-- getSecondFrom a b c = b

-- multSecond = g `on` h
-- g = (*)
-- h = snd

-- on3 :: (b -> b -> b -> c) -> (a -> b) -> a -> a -> a -> c
-- on3 op f x y z = op (f x) (f y) (f z)

doItYourself = f . g . h
f = (logBase 2)
g = (^3)
h = (\x -> if x > 42 then x else 42)
