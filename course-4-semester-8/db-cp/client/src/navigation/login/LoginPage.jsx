import React from 'react'
import { useHistory } from 'react-router'
import archiveApi from '../../api/archive-api'
import LoginForm from '../../components/authentication/LoginForm'
import RegistrationForm from '../../components/authentication/RegistrationForm'

import './style.scss'

export default function LoginPage () {
    const history = useHistory()

    const onLogin = (jwt) => {
        archiveApi.setToken(jwt)
        history.push('/dashboard/')
    }

    return <div className="login-page">
        <div className="login-form-container">
            <LoginForm onLogin={onLogin} />
        </div>
        <div className="registration-form-container">
            <RegistrationForm onLogin={onLogin} />
        </div>
    </div>
}
