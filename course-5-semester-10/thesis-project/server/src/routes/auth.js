'use strict'

const { query } = require('../db')
const bcrypt = require('bcrypt')
const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')
const { Employee } = require('../db/models/employees')

const router = require('express').Router()

router.post('/login', async (req, res) => {
    try {
        const { username, password } = req.body

        if (!username || !password) {
            return res.sendStatus(400)
        }

        const user = await Employee.findOne({
            where: { username }
        })

        if (!user) {
            return res.sendStatus(401)
        }

        const hash = user.password

        if (!(await bcrypt.compare(password, hash))) {
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
