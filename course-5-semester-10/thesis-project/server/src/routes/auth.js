'use strict'

const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')
const { User } = require('../db/models/user')

const router = require('express').Router()

router.post('/login', async (req, res) => {
    try {
        const { login, password } = req.body

        if (!login || !password) {
            return res.sendStatus(400)
        }

        const user = await User.findOne({
            where: { login }
        })

        if (!user) {
            return res.sendStatus(401)
        }

        if (!(await user.comparePasword(password))) {
            return res.sendStatus(401)
        }
        const token = jwt.sign({ userId: user.id }, JWT_SECRET)

        res.cookie('token', token, {
            maxAge: 1000 * 60 * 60 * 24 * 7 // 7 days
        })

        res.json({ success: true })
    } catch (error) {
        console.log(error)
        res.sendStatus(500)
    }
})

module.exports = router
