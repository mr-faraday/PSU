import React, { useState } from 'react'
import authApi from '../../api/auth-api'

import './style.scss'

export default function LoginForm () {
    const [username, setUsername] = useState('')
    const [password, setPassword] = useState('')

    const onSubmitHandler = async (e) => {
        e.preventDefault()

        try {
            const res = await authApi.login(username, password)
            console.log(res)
        } catch (error) {
            alert('Error')
        }
    }

    return (
        <form className="login-form" onSubmit={onSubmitHandler}>
            <h2>Login</h2>

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

            <input type="submit" value="Login" />
        </form>
    )
}
