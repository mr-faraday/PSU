'use strict'

const { Sequelize } = require('sequelize')
const {
    POSTGRES_USER,
    POSTGRES_PASSWORD,
    POSTGRES_DB,
    POSTGRES_HOST
} = require('../config')

const db = new Sequelize({
    host: POSTGRES_HOST,
    port: 5432,
    dialect: 'postgres',
    username: POSTGRES_USER,
    password: POSTGRES_PASSWORD,
    database: POSTGRES_DB,
    define: {
        timestamps: false
    }
})

module.exports.db = db
