-- Тип LogLevel описывает различные уровни логирования.

data LogLevel = Error | Warning | Info 

-- Определите функцию cmp, сравнивающую элементы типа LogLevel так,
-- чтобы было верно, что Error > Warning > Info.

-- GHCi> cmp Error Warning
-- GT
-- GHCi> cmp Info Warning
-- LT
-- GHCi> cmp Warning Warning
-- EQ

cmp :: LogLevel -> LogLevel -> Ordering
cmp Error   Error   = EQ
cmp Error   _       = GT
cmp _       Error   = LT
cmp Warning Warning = EQ
cmp Warning _       = GT
cmp _       Warning = LT
cmp Info    Info    = EQ


-- Пусть объявлен следующий тип данных:

data Result = Fail | Success

-- И допустим определен некоторый тип данных SomeData
-- и некоторая функция

doSomeWork :: SomeData -> (Result,Int)

-- возвращающая результат своей работы и либо код ошибки
-- в случае неудачи, либо 0 в случае успеха.

-- Определите функцию processData, которая вызывает doSomeWork
-- и возвращает строку "Success" в случае ее успешного завершения,
-- либо строку "Fail: N" в случае неудачи, где N — код ошибки.

processData :: SomeData -> String
processData d =
  case doSomeWork d of
    (Fail,code) -> "Fail: " ++ show code
    _           -> "Success"
