'use strict'

const { User } = require('../db/models/user')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get('/', async (req, res) => {
    const user = await User.findOne({ where: { id: res.locals.userId } })

    res.json({ success: true, result: user })
})

module.exports = router
