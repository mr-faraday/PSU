'use strict'

const { Pool } = require('pg')
const {
    POSTGRES_USER,
    POSTGRES_PASSWORD,
    POSTGRES_DB,
    POSTGRES_HOST
} = require('../config')

const pool = new Pool({
    host: POSTGRES_HOST,
    port: 5432,
    user: POSTGRES_USER,
    password: POSTGRES_PASSWORD,
    database: POSTGRES_DB
})

module.exports = {
    async query (text, params) {
        const start = Date.now()
        const res = await pool.query(text, params)
        const duration = Date.now() - start
        console.log('executed query', { text, duration, rows: res.rowCount })
        return res
    },
    async getClient () {
        const client = await pool.connect()
        const query = client.query
        const release = client.release
        const timeout = setTimeout(() => {
            console.error(
                'A client has been checked out for more than 5 seconds!'
            )
            console.error(
                `The last executed query on this client was: ${client.lastQuery}`
            )
        }, 5000)
        client.query = (...args) => {
            client.lastQuery = args
            return query.apply(client, args)
        }
        client.release = () => {
            clearTimeout(timeout)
            client.query = query
            client.release = release
            return release.apply(client)
        }
        return client
    }
}
