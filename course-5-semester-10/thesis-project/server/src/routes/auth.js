'use strict'

const { query } = require('../db')
const bcrypt = require('bcrypt')
const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')

const router = require('express').Router()

router.post('/login', async (req, res) => {
    const { username, password } = req.body

    if (!username || !password) {
        return res.sendStatus(400)
    }

    const existingUser = await query(
        'SELECT user_password FROM user WHERE user_name = $1',
        [username]
    )

    const user = existingUser.rows[0]

    if (!user) {
        return res.sendStatus(404)
    }

    const hash = user.user_password

    if (!(await bcrypt.compare(password, hash))) {
        return res.sendStatus(401)
    }

    const token = jwt.sign({ userId: user.user_id }, JWT_SECRET)

    res.cookie('token', token, {
        maxAge: 1000 * 60 * 60 * 24 * 7, // 7 days
        path: '/'
    })

    res.json({ success: true })
})

module.exports = router
