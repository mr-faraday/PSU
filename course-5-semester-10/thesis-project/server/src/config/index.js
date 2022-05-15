'use strict'

module.exports.PORT = 3000

if (process.env.NODE_ENV === 'development') {
    require('dotenv').config()
}

module.exports.POSTGRES_HOST = process.env.POSTGRES_HOST
module.exports.POSTGRES_USER = process.env.POSTGRES_USER
module.exports.POSTGRES_PASSWORD = process.env.POSTGRES_PASSWORD
module.exports.POSTGRES_DB = process.env.POSTGRES_DB
module.exports.JWT_SECRET = process.env.JWT_SECRET
