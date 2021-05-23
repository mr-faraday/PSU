import React, { useState } from 'react'

import './style.scss'

export default function LoginForm () {
    const [userName, setUserName] = useState('')
    const [password, setPassword] = useState('')

    const onSubmitHandler = (e) => {
        e.preventDefault()

        console.log('asdf')
    }

    return (
        <form className="login-form" onSubmit={onSubmitHandler}>
            <h2>Login</h2>

            <div className="input">
                <input type="text" placeholder="Username" />
            </div>

            <div className="input">
                <input type="password" placeholder="Password" />
            </div>

            <input type="submit" value="Login" />
        </form>
    )
}
