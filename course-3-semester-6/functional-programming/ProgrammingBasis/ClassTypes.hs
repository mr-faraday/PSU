-- Реализуйте класс типов Printable, предоставляющий один метод toString — функцию одной переменной,
-- которая преобразует значение типа, являющегося представителем Printable, в строковое представление.

class Printable a where
  toString :: a -> String

instance Printable Bool where
  toString True = "true"
  toString False = "false"

instance Printable () where
  toString () = "unit type"

-- Сделайте тип пары представителем класса типов Printable, реализованного вами в предыдущей задаче.

instance (Printable a, Printable b) => Printable (a, b) where
  toString (x, y) = "(" ++ toString x ++ "," ++ toString y ++ ")"
