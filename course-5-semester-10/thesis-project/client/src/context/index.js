import { createContext, useContext } from 'react'

const context = createContext(null)

export const AppContextProvider = context.Provider

export const useAppContext = () => useContext(context)
