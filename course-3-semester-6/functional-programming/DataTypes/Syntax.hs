-- Определите тип записи, который хранит элементы лога.
-- Имя конструктора должно совпадать с именем типа,
-- и запись должна содержать три поля:

--   timestamp — время, когда произошло событие (типа UTCTime);
--   logLevel — уровень события (типа LogLevel);
--   message — сообщение об ошибке (типа String).

-- Определите функцию logLevelToString, возвращающую текстуальное
-- представление типа LogLevel, и функцию logEntryToString,
-- возвращающую текстуальное представление записи в виде:

-- <время>: <уровень>: <сообщение>

-- Для преобразование типа UTCTime в строку используйте функцию timeToString.

import Data.Time.Clock
import Data.Time.Format
import System.Locale

timeToString :: UTCTime -> String
timeToString = formatTime defaultTimeLocale "%a %d %T"

data LogLevel = Error | Warning | Info

data LogEntry = LogEntry { 
  timestamp :: UTCTime,
  logLevel :: LogLevel,
  message :: String
  }

logLevelToString :: LogLevel -> String
logLevelToString Error = "Error"
logLevelToString Warning = "Warning"
logLevelToString Info = "Info"

logEntryToString :: LogEntry -> String
logEntryToString (LogEntry time lvl msg) = (timeToString time) ++ ": " ++ (logLevelToString lvl) ++ ": " ++ msg


-- Определить функцию abbrFirstName, которая сокращает имя до первой буквы с точкой,
-- то есть, если имя было "Ivan", то после применения этой функции оно превратится в
-- "I.". Однако, если имя было короче двух символов, то оно не меняется.

data Person = Person { firstName :: String, lastName :: String, age :: Int }

abbrFirstName :: Person -> Person
abbrFirstName p = p { firstName = (abbrName . firstName $ p) } where
  abbrName name@(f:l) | length name < 2 = name
                      | otherwise       = f : "."
  abbrName _                            = ""
