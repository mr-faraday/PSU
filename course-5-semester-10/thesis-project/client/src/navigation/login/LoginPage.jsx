import React from 'react'
import { useHistory } from 'react-router'
import LoginForm from '../../components/authentication/LoginForm'
import RegistrationForm from '../../components/authentication/RegistrationForm'
import { useAppContext } from '../../context'
import Cookies from 'universal-cookie'

import './style.scss'

const cookies = new Cookies()

export default function LoginPage () {
    const history = useHistory()
    const appContext = useAppContext()

    const onLogin = (jwt) => {
        appContext.token = jwt
        cookies.set('jwt_token', jwt, { maxAge: 3600 * 24 * 30, path: '/' })
        history.push('/dashboard/')
    }

    return (
        <div className="login-page">
            <div className="login-form-container">
                <LoginForm onLogin={onLogin} />
            </div>
            <div className="registration-form-container">
                <RegistrationForm onLogin={onLogin} />
            </div>
        </div>
    )
}
