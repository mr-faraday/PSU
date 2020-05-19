-- main' :: IO ()
-- main' = do
--   putStrLn "What is your name?"
--   putStr "Name: "
--   name <- getLine
--   if name == "" then main' else putStrLn $ "Hi, " ++ name ++ "!"


import System.Directory
import Data.List

main' :: IO ()
main' = do
  putStr "Substring: "
  tpl <- getLine
  if tpl == "" then do
    putStrLn "Canceled"
    return ()
  else do
    dirList <- getDirectoryContents "."
    mapM_ (print'n'del tpl) dirList


print'n'del:: String -> FilePath -> IO ()
print'n'del pattern path =
  if isInfixOf pattern path
    then do
      removeFile path
      putStrLn $ "Removing file: " ++ path
    else return ()
