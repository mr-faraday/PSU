'use strict'

const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')

const headerRegExp = /^Bearer (.*)$/

module.exports = function authenticationMiddleware (req, res, next) {
    if (!req.headers.authorization) {
        return res.sendStatus(401)
    }

    const [, token] = headerRegExp.exec(req.headers.authorization)

    try {
        jwt.verify(token, JWT_SECRET)
        next()
    } catch (error) {
        res.sendStatus(401)
    }
}
