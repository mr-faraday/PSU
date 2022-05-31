'use strict'

const asyncHandler = require('express-async-handler')
const { UserRoleId } = require('../constants')
const { Task } = require('../db/models/task')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await Task.findAll()
        })
    })
)

router.post(
    '/',
    asyncHandler(async (req, res) => {
        //
    })
)

module.exports = router
