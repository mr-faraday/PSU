'use strict'

const db = require('../db')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get('/', async (req, res) => {
    //
    res.json({ success: true, user: 'user' })
})

module.exports = router
