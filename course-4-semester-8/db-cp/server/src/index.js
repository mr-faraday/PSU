'use strict'

const express = require('express')
const { PORT } = require('./config')
const { query } = require('./db')

// константы
const host = '0.0.0.0'

// приложение
const app = express()
app.get('/', async (req, res) => {
    try {
        console.log((await query('SELECT * FROM rack')).rows)
        res.send('Hello World!')
    } catch (error) {
        console.log(error.message)
        res.sendStatus(500)
    }
})

app.listen(PORT, host)
console.log(`running on http://${host}:${PORT}`)
