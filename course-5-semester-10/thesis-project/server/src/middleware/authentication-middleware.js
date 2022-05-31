'use strict'

const asyncHandler = require('express-async-handler')
const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')
const { User } = require('../db/models/user')

/**
 * @type {import('express').RequestHandler}
 */
module.exports = asyncHandler(async function authenticationMiddleware (
    req,
    res,
    next
) {
    if (!req.cookies || !req.cookies.token) {
        return res.sendStatus(401)
    }

    const { token } = req.cookies

    try {
        const payload = jwt.verify(token, JWT_SECRET)

        const user = await User.findOne({
            where: { id: payload.userId }
        })

        if (!user || !user.active) {
            return res.sendStatus(401)
        }

        res.locals.user = user

        next()
    } catch (error) {
        console.log(error)
        res.sendStatus(401)
    }
})
