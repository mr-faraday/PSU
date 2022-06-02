'use strict'

const asyncHandler = require('express-async-handler')
const { ShelfOcupation } = require('../db/queries/shelf-ocupation')
const router = require('express').Router()

router.use(require('../middleware/authentication-middleware'))

router.get(
    '/shelf-ocupations',
    asyncHandler(async (req, res) => {
        res.json({
            success: true,
            result: await ShelfOcupation.getAll()
        })
    })
)

module.exports = router
