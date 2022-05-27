'use strict'

const { Employee } = require('../db/models/employees')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get('/', async (req, res) => {
    const user = await Employee.findOne({ where: { id: res.locals.userId } })

    res.json({ success: true, result: user })
})

module.exports = router
