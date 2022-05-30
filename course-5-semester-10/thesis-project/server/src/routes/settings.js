'use strict'

const asyncHandler = require('express-async-handler')
const { TaskStatus } = require('../db/models/task-status')
const { UserRole } = require('../db/models/user-role')
const router = require('express').Router()

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: {
                userRoles: await UserRole.findAll(),
                taskStatuses: await TaskStatus.findAll()
            }
        })
    })
)

module.exports = router
