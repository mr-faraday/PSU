'use strict'

const asyncHandler = require('express-async-handler')
const { UserRoleId } = require('../constants')
const { Client } = require('../db/models/client')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))
router.use((req, res, next) => {
    if (
        ![UserRoleId.ADMIN, UserRoleId.MANAGER].includes(res.locals.user.roleId)
    ) {
        return res.sendStatus(403)
    }

    next()
})

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await Client.findAll()
        })
    })
)

router.post(
    '/',
    asyncHandler(async (req, res) => {
        const { firstName, lastName, phone } = req.body

        if (!firstName || !lastName || !phone) {
            return res.sendStatus(400)
        }

        const client = await Client.create({ firstName, lastName, phone })

        res.json({
            success: true,
            result: client
        })
    })
)

module.exports = router
