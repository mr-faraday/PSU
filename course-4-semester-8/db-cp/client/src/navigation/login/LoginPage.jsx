import React from 'react'
import LoginForm from '../../components/authentication/LoginForm'
import RegistrationForm from '../../components/authentication/RegistrationForm'

import './style.scss'

export default function LoginPage () {
    return <div className="login-page">
        <div className="login-form-container">
            <LoginForm />
        </div>
        <div className="registration-form-container">
            <RegistrationForm />
        </div>
    </div>
}
