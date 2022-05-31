'use strict'

const asyncHandler = require('express-async-handler')
const { Cargo } = require('../db/models/cargo')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await Cargo.findAll()
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
