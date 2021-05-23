import React from 'react'
import { BrowserRouter as Router } from 'react-router-dom'

import AppNavigation from './navigation/AppNavigation'

import './App.scss'

function App () {
    return (
        <div className="App">
            <Router>
                <AppNavigation />
            </Router>
        </div>
    )
}

export default App
