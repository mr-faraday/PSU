'use strict'

const jwt = require('jsonwebtoken')
const { JWT_SECRET } = require('../config')

module.exports = function authncticationMiddleware (req, res, next) {
    if (!req.headers.authorization) {
        res.sendStatus(401)
    }

    const [, token] = /^Bearer (.*)$/.exec(req.headers.authorization)

    try {
        jwt.verify(token, JWT_SECRET)
        next()
    } catch (error) {
        res.sendStatus(401)
    }
}
