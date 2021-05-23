import React, { useEffect, useState } from 'react'
import Cookies from 'universal-cookie'
import archiveApi from '../api/archive-api'
import { Switch, Route, Link, Redirect, useLocation } from 'react-router-dom'

import LoginPage from './login/LoginPage'
import DashboardPage from './dashboard/DashboardPage'
import classNames from 'classnames'
import { AppContextProvider } from '../context'

const cookies = new Cookies()
const extractToken = () => cookies.get('jwt_token')

export default function AppNavigation () {
    const location = useLocation()
    const [token, setToken] = useState(null)

    useEffect(() => {
        archiveApi.setToken(token)
    }, [token])

    useEffect(() => {
        const token = extractToken()

        if (token) {
            setToken(token)
        }
    }, [document])

    const redirectRoute = token ? '/dashboard/' : '/login/'
    const isActiveRoute = (route) => location.pathname.includes(route)

    const contextValue = {
        get token () {
            return token
        },
        set token (token) {
            setToken(token)
        }
    }

    return (
        <AppContextProvider value={contextValue}>
            <div className="App">
                <header>
                    <h1>DOCUMENTS ARCHIVE</h1>

                    <Link
                        to="/dashboard/"
                        className={classNames({
                            active: isActiveRoute('/dashboard/'),
                            disabled: !token
                        })}
                    >
                        Dashboard
                    </Link>
                    <Link
                        to="/login/"
                        className={classNames({
                            active: isActiveRoute('/login/')
                        })}
                    >
                        Login
                    </Link>
                </header>

                <Switch>
                    <Route exact path="/login/">
                        <LoginPage />
                    </Route>
                    <Route path="/dashboard/">
                        {!token && <Redirect to="/login/" />}

                        <DashboardPage />
                    </Route>
                    <Route exact path="/">
                        <Redirect to={redirectRoute} />
                    </Route>
                </Switch>
            </div>
        </AppContextProvider>
    )
}
