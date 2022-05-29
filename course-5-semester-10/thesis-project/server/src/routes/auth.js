'use strict'

const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')
const { Employee } = require('../db/models/employee')

const router = require('express').Router()

router.post('/login', async (req, res) => {
    try {
        const { login, password } = req.body

        if (!login || !password) {
            return res.sendStatus(400)
        }

        const employee = await Employee.findOne({
            where: { login }
        })

        if (!employee) {
            return res.sendStatus(401)
        }

        if (!(await employee.comparePasword(password))) {
            return res.sendStatus(401)
        }
        const token = jwt.sign({ userId: employee.id }, JWT_SECRET)

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
