'use strict'

const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')

const headerRegExp = /^Bearer (.*)$/

/**
 * @type {import('express').RequestHandler}
 */
module.exports = function authenticationMiddleware (req, res, next) {
    if (!req.cookies || !req.cookies.token) {
        return res.sendStatus(401)
    }

    const [, token] = headerRegExp.exec(req.headers.authorization)

    try {
        const payload = jwt.verify(token, JWT_SECRET)

        res.locals.userId = payload.userId

        next()
    } catch (error) {
        res.sendStatus(401)
    }
}
