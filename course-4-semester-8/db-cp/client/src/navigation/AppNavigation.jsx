import React, { useEffect, useState } from 'react'
import Cookies from 'universal-cookie'
import archiveApi from '../api/archive-api'
import { Switch, Route, Link, Redirect, useLocation } from 'react-router-dom'

import LoginPage from './login/LoginPage'
import DashboardPage from './dashboard/DashboardPage'
import classNames from 'classnames'

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
    const isActiveRoute = (route) => location.pathname === route

    return (
        <div className="App">
            <header>
                <Link
                    to="/login/"
                    className={classNames({
                        active: isActiveRoute('/login/')
                    })}
                >
                    Login
                </Link>
                <Link
                    to="/dashboard/"
                    className={classNames({
                        active: isActiveRoute('/dashboard/')
                    })}
                >
                    Dashboard
                </Link>

                <h1>
                    DOCUMENTS ARCHIVE
                </h1>
            </header>

            <Switch>
                <Route exact path="/login/">
                    <LoginPage />
                </Route>
                <Route exact path="/dashboard/">
                    <DashboardPage />
                </Route>
                <Route exact path="/">
                    <Redirect to={redirectRoute} />
                </Route>
            </Switch>
        </div>
    )
}
