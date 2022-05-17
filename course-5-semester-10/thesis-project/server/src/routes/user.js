'use strict'

const UserController = require('../controllers/user-controller')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get('/', async (req, res) => {
    const user = await UserController.getUser(res.locals.userId)

    res.json({ success: true, result: user })
})

module.exports = router
