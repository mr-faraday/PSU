import React, { useState } from 'react'
import authApi from '../../api/auth-api'

import './style.scss'

export default function RegistrationForm ({ onLogin }) {
    const [username, setUsername] = useState('')
    const [password, setPassword] = useState('')
    const [rPassword, setRPassword] = useState('')

    const onSubmitHandler = async (e) => {
        e.preventDefault()

        if (password !== rPassword) {
            return alert('Passwords are different')
        }

        try {
            const res = await authApi.register(username, password)
            onLogin(res.jwt)
        } catch (error) {
            alert('Error')
        }
    }

    return (
        <form className="login-form" onSubmit={onSubmitHandler}>
            <h2>Registration</h2>

            <div className="input">
                <input
                    value={username}
                    type="text"
                    placeholder="Username"
                    onChange={(e) => setUsername(e.target.value)}
                />
            </div>

            <div className="input">
                <input
                    value={password}
                    type="password"
                    placeholder="Password"
                    onChange={(e) => setPassword(e.target.value)}
                />
            </div>

            <div className="input">
                <input
                    value={rPassword}
                    type="password"
                    placeholder="Repeat Password"
                    onChange={(e) => setRPassword(e.target.value)}
                />
            </div>

            <input type="submit" value="Submit" />
        </form>
    )
}
