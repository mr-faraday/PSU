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

router.post(
    '/change-password',
    asyncHandler(async (req, res) => {
        const { oldPassword, newPassword } = req.body

        if (!oldPassword || !newPassword) {
            return res.sendStatus(400)
        }

        const user = await User.findOne({ where: { id: res.locals.userId } })

        if (!(await user.comparePasword(oldPassword))) {
            return res.sendStatus(401)
        }

        await user.setPassword(newPassword)
        await user.save()

        res.json({ success: true })
    })
)

module.exports = router
