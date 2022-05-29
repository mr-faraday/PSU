'use strict'

const { User } = require('../db/models/user')
const asyncHandler = require('express-async-handler')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/',
    asyncHandler(async (req, res) => {
        const user = await User.findOne({ where: { id: res.locals.userId } })

        res.json({ success: true, result: user })
    })
)

module.exports = router
