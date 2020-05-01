import Data.Char
import Data.List

data Token = Number Int | Plus | Minus | LeftBrace | RightBrace     
  deriving (Eq, Show)
-- Тип Token уже объявлен, его писать не нужно

asToken :: String -> Maybe Token
asToken str
  | str == "("      = Just LeftBrace
  | str == ")"      = Just RightBrace
  | str == "+"      = Just Plus
  | str == "-"      = Just Minus
 -- | all isDigit str = Just (Number str)
  | otherwise        = Nothing

tokenize :: String -> Maybe [Token]
tokenize input = undefined


pythagoreanTriple :: Int -> [(Int, Int, Int)]
pythagoreanTriple x = do undefined
