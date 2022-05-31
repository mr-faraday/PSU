'use strict'

const asyncHandler = require('express-async-handler')
const { UserRoleId } = require('../constants')
const { User } = require('../db/models/user')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))
router.use((req, res, next) => {
    if (res.locals.user.roleId !== UserRoleId.ADMIN) {
        return res.sendStatus(403)
    }

    next()
})

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await User.findAll({
                attributes: { exclude: ['password'] }
            })
        })
    })
)

router.post(
    '/',
    asyncHandler(async (req, res) => {
        const { login, roleId, firstName, lastName } = req.body

        if (!login || !roleId || !firstName || !lastName) {
            return res.sendStatus(400)
        }

        const user = new User({
            login,
            roleId,
            firstName,
            lastName
        })

        const password = Math.random().toString(36).slice(-8)
        await user.setPassword(password)
        await user.save()

        res.json({
            success: true,
            result: {
                login: user.login,
                password
            }
        })
    })
)

router.post(
    '/:id/deactivate',
    asyncHandler(async (req, res) => {
        const { id } = req.params

        if (!id) {
            return res.sendStatus(400)
        }

        const user = await User.findOne({ where: { id } })

        if (!user) {
            return res.sendStatus(404)
        }

        user.active = false
        await user.save()

        res.json({ success: true })
    })
)

router.post(
    '/:id/activate',
    asyncHandler(async (req, res) => {
        const { id } = req.params
        if (!id) {
            return res.sendStatus(400)
        }

        const user = await User.findOne({ where: { id } })

        if (!user) {
            return res.sendStatus(404)
        }

        user.active = true
        await user.save()

        res.json({ success: true })
    })
)

module.exports = router
